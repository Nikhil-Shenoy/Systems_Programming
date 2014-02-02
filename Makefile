COMPILER = gcc -Wall -pedantic

tokenizer.o: tokenizer.c
	$(COMPILER) -c tokenizer.c

main: tokenizer.o
	$(COMPILER) tokenizer.o -o main

clean: tokenizer.o
	rm tokenizer.o
	rm main