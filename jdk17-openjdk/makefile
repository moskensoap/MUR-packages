SOURCES := $(wildcard *.c)
EXES := $(SOURCES:%.c=%17.exe)

All: $(EXES)
	@echo "All Done"

%17.exe: %.c
	gcc -o $@ $^ -O3 -s

.PHONY: clean
clean:
	rm -rf *.exe
