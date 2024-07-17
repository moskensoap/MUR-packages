SOURCES := $(wildcard *.c)
EXES := $(SOURCES:%.c=%11.exe)

All: $(EXES)
	@echo "All Done"

%11.exe: %.c
	gcc -o $@ $^ -O3 -s

.PHONY: clean
clean:
	rm -rf *.exe
