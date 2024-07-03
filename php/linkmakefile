SOURCES := $(wildcard *.c)
EXES := $(SOURCES:.c=.exe)

All: $(EXES)
	@echo "All Done"

%.exe: %.c
	gcc -o $@ $^ -O3 -s

.PHONY: clean
clean:
	rm -rf *.exe
