SOURCES := $(wildcard *.c)
EXES := $(SOURCES:%.c=%39.exe)

All: $(EXES)
	@echo "All Done"

%39.exe: %.c
	gcc -o $@ $^ -O3 -s

.PHONY: clean
clean:
	rm -rf *.exe
