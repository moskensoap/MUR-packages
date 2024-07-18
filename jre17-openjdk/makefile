SOURCES := $(wildcard *.c)
EXES := $(SOURCES:%.c=%jre17.exe)

All: $(EXES)
	@echo "All Done"

%jre17.exe: %.c
	gcc -o $@ $^ -O3 -s

.PHONY: clean
clean:
	rm -rf *.exe
