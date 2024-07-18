SOURCES := $(wildcard *.c)
EXES := $(SOURCES:%.c=%8.1.exe)

All: $(EXES)
	@echo "All Done"

%8.1.exe: %.c
	gcc -o $@ $^ -O3 -s

.PHONY: clean
clean:
	rm -rf *.exe
