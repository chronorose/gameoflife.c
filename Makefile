CC := gcc
src := main.c
obj := main.o
name := main
rm := rm -f

all: $(obj)
	$(CC) $(src) -o $(name)

objclean:
	$(rm) $(obj)

clean: objclean
	$(rm) $(name)
