SOURCES := $(wildcard *.c)
EXES := $(SOURCES:%.c=%38.exe)

All: $(EXES)
	@echo "All Done"

%38.exe: %.c
	gcc -o $@ $^ -O3 -s

.PHONY: clean
clean:
	rm -rf *.exe
