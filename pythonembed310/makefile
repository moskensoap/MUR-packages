SOURCES := $(wildcard *.c)
EXES := $(SOURCES:%.c=%310.exe)

All: $(EXES)
	@echo "All Done"

%310.exe: %.c
	gcc -o $@ $^ -O3 -s

.PHONY: clean
clean:
	rm -rf *.exe
