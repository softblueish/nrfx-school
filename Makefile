compile:
	gcc -o program main.c BSTree.c uarte-commands.c
clean:
	rm -f program
run:
	./program
all: compile run clean