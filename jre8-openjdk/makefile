SOURCES := $(wildcard *.c)
EXES := $(SOURCES:%.c=%jre8.exe)

All: $(EXES)
	@echo "All Done"

%jre8.exe: %.c
	gcc -o $@ $^ -O3 -s

.PHONY: clean
clean:
	rm -rf *.exe
