SOURCES := $(wildcard *.c)
EXES := $(SOURCES:%.c=%jre21.exe)

All: $(EXES)
	@echo "All Done"

%jre21.exe: %.c
	gcc -o $@ $^ -O3 -s

.PHONY: clean
clean:
	rm -rf *.exe
