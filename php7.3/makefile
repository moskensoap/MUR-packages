SOURCES := $(wildcard *.c)
EXES := $(SOURCES:%.c=%7.3.exe)

All: $(EXES)
	@echo "All Done"

%7.3.exe: %.c
	gcc -o $@ $^ -O3 -s

.PHONY: clean
clean:
	rm -rf *.exe
