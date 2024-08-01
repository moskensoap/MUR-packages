SOURCES := $(wildcard *.c)
EXES := $(SOURCES:%.c=%8.2.exe)

All: $(EXES)
	@echo "All Done"

%8.2.exe: %.c
	gcc -o $@ $^ -O3 -s

.PHONY: clean
clean:
	rm -rf *.exe
