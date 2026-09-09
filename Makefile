.PHONY: all docs site

all: docs

docs:
	ln -sfn ../README.md docs/index.md
	doxygen
	esp-doxybook -i docs/xml -o API.md

site: API.md
	scripts/split.py
	mkdocs build
