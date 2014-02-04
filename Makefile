COMPILER = gcc -Wall -g -O

all: tokenizer

tokenizer.o: tokenizer.c
	$(COMPILER) -c tokenizer.c

tokenizer: tokenizer.o
	$(COMPILER) tokenizer.o -o tokenizer

clean:
	rm tokenizer.o
	rm tokenizer
