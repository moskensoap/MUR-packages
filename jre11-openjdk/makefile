SOURCES := $(wildcard *.c)
EXES := $(SOURCES:%.c=%jre11.exe)

All: $(EXES)
	@echo "All Done"

%jre11.exe: %.c
	gcc -o $@ $^ -O3 -s

.PHONY: clean
clean:
	rm -rf *.exe
