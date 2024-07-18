SOURCES := $(wildcard *.c)
EXES := $(SOURCES:%.c=%5.6.exe)

All: $(EXES)
	@echo "All Done"

%5.6.exe: %.c
	gcc -o $@ $^ -O3 -s

.PHONY: clean
clean:
	rm -rf *.exe
