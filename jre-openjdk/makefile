SOURCES := $(wildcard *.c)
EXES := $(SOURCES:%.c=%jrelatest.exe)

All: $(EXES)
	@echo "All Done"

%jrelatest.exe: %.c
	gcc -o $@ $^ -O3 -s

.PHONY: clean
clean:
	rm -rf *.exe
