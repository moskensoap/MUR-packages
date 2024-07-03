SOURCES := $(wildcard *.c)
EXES := $(SOURCES:%.c=%7.4.exe)

All: $(EXES)
	@echo "All Done"

%7.4.exe: %.c
	gcc -o $@ $^ -O3 -s

.PHONY: clean
clean:
	rm -rf *.exe
