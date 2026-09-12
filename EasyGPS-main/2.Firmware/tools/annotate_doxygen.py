"""Add conservative Doxygen comments to project-owned declarations.

This one-shot maintenance script is intentionally limited to EasyGPS glue
code. It does not touch vendored drivers, LVGL demos, generated resources, or
files carrying an upstream implementation license. The generated text is a
starting point: hardware-specific invariants should be refined when a module
is changed.
"""

from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]

TARGET_ROOTS = (
    ROOT / "src" / "App" / "Pages",
    ROOT / "src" / "App" / "Common" / "HAL",
    ROOT / "src" / "App" / "Common" / "DataProc",
    ROOT / "src" / "App" / "Resource" / "ResourcePool.h",
    ROOT / "src" / "App" / "Resource" / "ResourcePool.cpp",
    ROOT / "src" / "App" / "Utils" / "lv_ext",
    ROOT / "src" / "App" / "Utils" / "lv_poly_line",
    ROOT / "src" / "App" / "Utils" / "MapConv",
    ROOT / "src" / "ChappieCore" / "ChappieCore.cpp",
    ROOT / "src" / "ChappieCore" / "WiFi",
    ROOT / "src" / "ChappieCore" / "SmartAssistantAPI",
)

EXCLUDE_PARTS = {
    "Utility",
    "demos",
    "Speaker",
    "Mic",
    "lv_anim_label",
    "lv_allocator",
    "DataCenter",
    "PageManager",
    "Filters",
    "StorageService",
    "ResourceManager",
    "PointContainer",
    "TileConv",
    "TrackFilter",
    "TonePlayer",
    "GPX",
    "Time",
}

CONTROL_WORDS = {"if", "for", "while", "switch", "catch", "return"}
ACCESS_WORDS = {"public:", "private:", "protected:", "signals:", "slots:"}
CALL_PREFIXES = (
    "xTask", "vTask", "printf", "Serial", "delay", "pinMode", "digital",
    "analog", "gpio_", "lv_", "Wire", "SPI", "SD", "WiFi", "FastLED",
    "mem", "str", "abs", "map", "constrain", "assert",
)


def selected(path: Path) -> bool:
    try:
        rel = path.relative_to(ROOT)
    except ValueError:
        return False
    if not any(path == root or root in path.parents for root in TARGET_ROOTS):
        return False
    if any(part in EXCLUDE_PARTS for part in rel.parts):
        return False
    return path.suffix.lower() in {".h", ".hpp", ".cpp", ".c", ".inc"}


def previous_code_line(lines, index):
    index -= 1
    while index >= 0 and not lines[index].strip():
        index -= 1
    return lines[index].strip() if index >= 0 else ""


def has_nearby_doc(lines, index):
    """Avoid duplicating an existing Doxygen block immediately above a symbol."""
    index -= 1
    blank_count = 0
    while index >= 0 and blank_count < 2:
        text = lines[index].strip()
        if not text:
            blank_count += 1
            index -= 1
            continue
        return text.startswith("/**") or text.startswith("/*!") or text.startswith("///")
    return False


def clean_signature(line):
    return re.sub(r"//.*$", "", line).strip()


def symbol_name(signature):
    before = signature.split("(", 1)[0].strip()
    before = before.rstrip("=~ ")
    token = re.split(r"\s+", before)[-1]
    token = token.replace("*", "").replace("&", "")
    return token


def split_parameters(signature):
    if "(" not in signature or ")" not in signature:
        return []
    text = signature.split("(", 1)[1].rsplit(")", 1)[0]
    if not text.strip() or text.strip() == "void":
        return []
    result = []
    for item in text.split(","):
        item = item.strip()
        item = item.split("=", 1)[0].strip()
        match = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*(?:\[.*\])?$", item)
        if match:
            result.append(match.group(1))
    return result


def brief_for(name, path):
    short = name.split("::")[-1]
    owner = path.stem
    if short in {owner, "~" + owner}:
        return f"Construct or destroy the {owner} object." if not short.startswith("~") else f"Release resources owned by the {owner} object."
    if short in {"Init", "init", "HAL_Init", "DataProc_Init"}:
        return f"Initialize {owner} state and hardware or data resources."
    if short in {"Deinit", "deinit", "end", "stop"}:
        return f"Release or reset resources managed by {owner}."
    if short in {"Create", "create"} or short.endswith("_Create"):
        return f"Create the LVGL objects or resource group represented by {short}."
    if short in {"Delete", "delete"}:
        return f"Delete LVGL objects owned by {owner}."
    if short.startswith("onView"):
        return f"Handle the {short} page lifecycle callback."
    if short in {"Update", "HAL_Update", "WiFi_Update", "GPS_Update", "IMU_Update", "MAG_Update"} or short.endswith("Update"):
        return f"Refresh {owner} state without blocking the scheduler."
    if short.startswith("onTimer") or short in {"onTimer", "task_handler", "task_lv_timer_handler"}:
        return "Process the periodic timer or FreeRTOS task callback."
    if short.startswith("onEvent") or short.endswith("Handler") or short.startswith("AttachEvent"):
        return "Handle an event and forward it to the owning model or view."
    if short.startswith("Get") or short.startswith("read") or short.startswith("is"):
        return f"Read {short[3:] if short.startswith('Get') else short} from the current object state."
    if short.startswith("Set") or short.startswith("enable") or short.startswith("disable"):
        return f"Change the {short[3:] if short.startswith('Set') else short} configuration of the object."
    if short.startswith("Play") or short.startswith("Send"):
        return f"Send or play the payload requested by the application."
    if short.startswith("Convert") or short.startswith("Map"):
        return "Convert map or coordinate data between the supported representations."
    return f"Implement the {short} operation for the owning module."


def function_signature(line):
    text = clean_signature(line)
    if not text or text.startswith(("#", "//", "/*", "*", "typedef", "using ")):
        return False
    if any(text.startswith(word + " ") or text.startswith(word + "(") for word in CONTROL_WORDS):
        return False
    if "(" not in text or ")" not in text:
        return False
    # A declaration/definition must have a method-looking identifier before '('.
    before = text.split("(", 1)[0].strip()
    if not re.search(r"[A-Za-z_~][A-Za-z0-9_:~]*\s*$", before):
        return False
    name = symbol_name(text)
    if not name or name in CONTROL_WORDS:
        # Leave control-flow constructs and malformed signatures untouched.
        return False
    # A lower-case, unqualified identifier with no return type is normally a
    # function call inside a body, not a declaration. Keep common Arduino and
    # RTOS calls out of the generated API comments.
    prefix = before[: before.rfind(name)].strip()
    if not prefix and "::" not in name and not name[:1].isupper():
        return False
    if any(name.startswith(item) for item in CALL_PREFIXES) and "::" not in name:
        return False
    # Declarations end with ';'; definitions have '{' on the same or next line.
    return text.endswith(";") or "{" in text or text.endswith(")")


def variable_declaration(line):
    text = clean_signature(line)
    if not text or "(" in text or not text.endswith(";"):
        return None
    if text.startswith(("#", "//", "/*", "*", "typedef", "using ")):
        return None
    if text in ACCESS_WORDS or text in {"};", "};"}:
        return None
    # Ignore enum labels and pure type terminators. Members and globals have a
    # type followed by a named object, optionally with an initializer.
    body = text[:-1].split("=", 1)[0].strip()
    match = re.match(r"(?:static\s+|const\s+|volatile\s+|constexpr\s+|extern\s+)*(.+?)\s+([A-Za-z_][A-Za-z0-9_]*)(?:\s*\[[^]]*\])?$", body)
    if not match:
        return None
    name = match.group(2)
    if name in {"if", "for", "while", "return"}:
        return None
    return name


def make_doc(brief, signature=None):
    lines = ["/**", f" * @brief {brief}"]
    if signature:
        for param in split_parameters(signature):
            lines.append(f" * @param {param} Input or output value used by this operation.")
        if not re.match(r"\s*(?:void|static\s+void|inline\s+void)", signature):
            lines.append(" * @return Result or status produced by the operation.")
    lines.append(" */")
    return lines


def annotate(path: Path):
    lines = path.read_text(encoding="utf-8").splitlines()
    output = []
    inserted = 0
    for index, line in enumerate(lines):
        stripped = line.strip()
        sig = clean_signature(line)
        is_function = function_signature(line)
        # Only insert for declarations/definitions, never for an invocation.
        if is_function and not has_nearby_doc(lines, index):
            name = symbol_name(sig)
            output.extend(make_doc(brief_for(name, path), sig))
            inserted += 1
        else:
            variable = variable_declaration(line)
            if variable and not has_nearby_doc(lines, index):
                output.extend(make_doc(f"Store the {variable} state used by this module."))
                inserted += 1
        output.append(line)
    if inserted:
        path.write_text("\n".join(output) + "\n", encoding="utf-8")
    return inserted


def main():
    files = []
    for root in TARGET_ROOTS:
        if root.is_file():
            files.append(root)
        elif root.exists():
            files.extend(p for p in root.rglob("*") if p.is_file())
    total = 0
    for path in sorted(set(files)):
        if selected(path):
            count = annotate(path)
            if count:
                print(f"{count:4d} {path.relative_to(ROOT)}")
                total += count
    print(f"Inserted {total} Doxygen blocks")


if __name__ == "__main__":
    main()
