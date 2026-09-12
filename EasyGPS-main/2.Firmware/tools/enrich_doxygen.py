"""Expand the automatically generated Doxygen wording without touching code.

The first annotation pass deliberately covered every project symbol.  Its
wording was too terse for a learning-oriented firmware project, so this pass
adds ownership, lifecycle, and call-contract information to the generated
tags.  Only exact comment lines are replaced; executable source is untouched.
"""

from pathlib import Path
import re


ROOT = Path(__file__).resolve().parents[1]
EXTENSIONS = {".c", ".cc", ".cpp", ".h", ".hpp", ".inc"}


def enrich(path: Path) -> bool:
    original = path.read_text(encoding="utf-8")
    text = original
    text = re.sub(
        r"@brief Implement the (.+?) operation for the owning module\.",
        r"@brief Execute the \1 operation and update the owning module state.\n * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.",
        text,
    )
    text = re.sub(
        r"@brief Store the (.+?) state used by this module\.",
        r"@brief Own and retain the \1 state required by this module.\n * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.",
        text,
    )
    text = re.sub(
        r"@brief Handle an event and forward it to the owning model or view\.",
        "@brief Decode a UI or system event and forward it to the responsible model or view.\n * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.",
        text,
    )
    text = re.sub(
        r"@brief Refresh (.+?) state without blocking the scheduler\.",
        r"@brief Refresh the \1 state without blocking the scheduler.\n * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.",
        text,
    )
    text = re.sub(
        r"@brief Create the LVGL objects or resource group represented by (.+?)\.",
        r"@brief Create and register the LVGL objects owned by \1.\n * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.",
        text,
    )
    text = re.sub(
        r"@param ([A-Za-z_][A-Za-z0-9_]*) Input or output value used by this operation\.",
        r"@param \1 Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.",
        text,
    )
    text = re.sub(
        r"@return Result or status produced by the operation\.",
        "@return Operation result or status; inspect it before using dependent state.",
        text,
    )
    if text != original:
        path.write_text(text, encoding="utf-8", newline="")
        return True
    return False


def main() -> None:
    changed = 0
    for path in ROOT.joinpath("src").rglob("*"):
        if path.is_file() and path.suffix.lower() in EXTENSIONS:
            changed += int(enrich(path))
    print(f"enriched {changed} files")


if __name__ == "__main__":
    main()
