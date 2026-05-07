compile:
	gcc -o program main.c BSTree.c uarte-commands.c -lm
clean:
	rm -f program
run:
	./program
all: compile run clean