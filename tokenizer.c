/*
 * tokenizer.c
 */

#include <stdio.h>
#include <string.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
};

typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given set of separator
 * characters (given as a string) and a token stream (given as a string).
 * 
 * TKCreate should copy the two arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate(char *separators, char *ts) {

  return NULL;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy(TokenizerT *tk) {
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken(TokenizerT *tk) {

  return NULL;
}

/*
 * main will have two string arguments (in argv[1] and argv[2]).
 * The first string contains the separator characters.
 * The second string contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

/*
converts a hex string to its hexadecimal string representation
returns "" if it cannot find a match
*/
char * convertEscapeToHex(char * str) {
	if (strcmp(str, "\n") == 0) {
		return "0x0a";
	} else if (strcmp(str, "\t") == 0) {
		return "0x09";
	} else if (strcmp(str, "\v") == 0) {
		return "0x0b";
	} else if (strcmp(str, "\b") == 0) {
		return "0x08";
	} else if (strcmp(str, "\r") == 0) {
		return "0x0d";
	} else if (strcmp(str, "\f") == 0) {
		return "0x0c";
	} else if (strcmp(str, "\a") == 0) {
		return "0x07";
	} else if (strcmp(str, "\\") == 0) {
		return "0x5c";
	} else if (strcmp(str, "\"") == 0) {
		return "0x22";
	} else {
		return "";
	}
}

/*
returns 1 if given string is an escapestring, 
returns 0 if not escape string
*/
int isEscapeString (char * str) {
	if (strcmp(str, "\n") == 0) {
		return 1;
	} else if (strcmp(str, "\t") == 0) {
		return 1;
	} else if (strcmp(str, "\v") == 0) {
		return 1;
	} else if (strcmp(str, "\b") == 0) {
		return 1;
	} else if (strcmp(str, "\r") == 0) {
		return 1;
	} else if (strcmp(str, "\f") == 0) {
		return 1;
	} else if (strcmp(str, "\a") == 0) {
		return 1;
	} else if (strcmp(str, "\\") == 0) {
		return 1;
	} else if (strcmp(str, "\"") == 0) {
		return 1;
	} else {
		return 0;
	}
}



int main(int argc, char **argv) {

  return 0;
}