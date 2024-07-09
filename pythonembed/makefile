SOURCES := $(wildcard *.c)
EXES := $(SOURCES:%.c=%latest.exe)

All: $(EXES)
	@echo "All Done"

%latest.exe: %.c
	gcc -o $@ $^ -O3 -s

.PHONY: clean
clean:
	rm -rf *.exe
