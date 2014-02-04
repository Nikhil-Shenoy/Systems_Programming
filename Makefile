COMPILER = gcc -Wall -pedantic

all: tokenizer

tokenizer.o: tokenizer.c
	$(COMPILER) -c tokenizer.c

tokenizer: tokenizer.o
	$(COMPILER) tokenizer.o -o tokenizer

clean: tokenizer.o
	rm tokenizer.o
	rm tokenizer
