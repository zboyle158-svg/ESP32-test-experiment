"""Remove documentation blocks that were inserted inside C preprocessor macros.

Comments inside a macro continuation become part of the replacement list and can
turn otherwise valid X-macros into invalid C++.  This narrowly scoped cleanup
keeps all comments elsewhere and removes only a Doxygen block that immediately
follows a line ending in a continuation backslash.
"""

from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
EXTENSIONS = {".c", ".cc", ".cpp", ".h", ".hpp", ".inc"}


def clean_file(path: Path) -> bool:
    lines = path.read_text(encoding="utf-8").splitlines(keepends=True)
    output = []
    index = 0
    changed = False
    while index < len(lines):
        output.append(lines[index])
        if lines[index].rstrip("\r\n").rstrip().endswith("\\"):
            probe = index + 1
            while probe < len(lines) and not lines[probe].strip():
                probe += 1
            if probe < len(lines) and lines[probe].lstrip().startswith("/**"):
                end = probe
                while end < len(lines):
                    if "*/" in lines[end]:
                        end += 1
                        break
                    end += 1
                del output[-1]
                output.extend(lines[index : index + 1])
                index = end
                changed = True
                continue
        index += 1
    if changed:
        path.write_text("".join(output), encoding="utf-8", newline="")
    return changed


def main() -> None:
    changed = 0
    for path in ROOT.joinpath("src").rglob("*"):
        if path.is_file() and path.suffix.lower() in EXTENSIONS:
            changed += int(clean_file(path))
    print(f"cleaned {changed} files")


if __name__ == "__main__":
    main()
