SOURCES := $(wildcard *.c)
EXES := $(SOURCES:%.c=%311.exe)

All: $(EXES)
	@echo "All Done"

%311.exe: %.c
	gcc -o $@ $^ -O3 -s

.PHONY: clean
clean:
	rm -rf *.exe
