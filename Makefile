CC := gcc
src := src/main.c
obj := src/main.o
build := build/
name := $(build)gameoflife
rm := rm -f

all: $(obj)
	$(CC) $(src) -lncurses -o $(name)

objclean:
	$(rm) $(obj)

clean: objclean
	$(rm) $(name)
