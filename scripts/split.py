#!/usr/bin/env python3
"""Split esp-doxybook API.md into one page per header."""

import re
from pathlib import Path

root = Path(__file__).resolve().parent.parent
src = (root / "API.md").read_text()
out = root / "docs" / "api"
out.mkdir(parents=True, exist_ok=True)

# Drop the "# API Reference" + header-file index. MkDocs nav replaces it.
parts = re.split(r"^## File (.+)$", src, flags=re.M)
# parts[0] = preamble, then pairs: (path, body, path, body, ...)

index_lines = [
    "# API reference",
    "",
    "Header reference generated from Doxygen.",
    "",
]

for location, body in zip(parts[1::2], parts[2::2]):
    stem = Path(location).stem  # basic_id, location, etc
    title = stem.replace("_", " ").title()
    page = out / f"{stem}.md"
    page.write_text(f"# {title}\n\n`{location}`\n" + body.lstrip())
    index_lines.append(f"- [{title}]({stem}.md)")

(out / "index.md").write_text("\n".join(index_lines) + "\n")
