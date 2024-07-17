SOURCES := $(wildcard *.c)
EXES := $(SOURCES:%.c=%21.exe)

All: $(EXES)
	@echo "All Done"

%21.exe: %.c
	gcc -o $@ $^ -O3 -s

.PHONY: clean
clean:
	rm -rf *.exe
