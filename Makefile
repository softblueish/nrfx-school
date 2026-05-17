compile:
	gcc -o program main.c linked-list.c sorting-algorithm.c randomization.c uarte-commands.c -lm
clean:
	rm -f program
run:
	./program
all: compile run clean