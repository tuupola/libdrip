SUBDIRS = $(patsubst %/Makefile,%,$(wildcard */Makefile))

all:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

run:
	@for dir in $(SUBDIRS); do \
		echo "=== Running $$dir ==="; \
		$(MAKE) -C $$dir run; \
		echo ""; \
	done

clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done

.PHONY: all run clean
