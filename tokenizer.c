/*
 * tokenizer.c
 */

//#define DEBUG_ON

//#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"


/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */
struct TokenizerT_ {
	int index;
	char * input;
	char * delim;
};

typedef struct TokenizerT_ TokenizerT;

TokenizerT *TKCreate(char *separators, char *ts);
void TKDestroy(TokenizerT *tk);
char *TKGetNextToken(TokenizerT *tk);
char * convertCharToHex(char str);
char * unescapeString(char * str);
int TKCharIsDelim(TokenizerT *tk, char c);
int TKNextStringPart(TokenizerT *tk, int index, int lookingForDelim);
int TKNextTokenIndex(TokenizerT *tk);
int TKFirstNonTokenChar(TokenizerT *tk, int index);


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
//DONE
TokenizerT *TKCreate(char *separators, char *ts) {
	TokenizerT * tokenizer = malloc(sizeof(TokenizerT));
	tokenizer->index = 0;
	tokenizer->input = unescapeString(ts);
	tokenizer->delim = unescapeString(separators);
	return tokenizer;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */
//DONE
void TKDestroy(TokenizerT *tk) {
	tk->index = 0;
	
	free(tk->input);
	tk->input = 0;
	
	free(tk->delim);
	tk->delim = 0;
	
	free(tk);
	tk = 0;
}


int TKNextStringPart(TokenizerT *tk, int index, int lookingForDelim) {
	char * str = tk->input;
	int len = strlen(str);
	int i;
	for(i=index; i<len; i++) {
		char c = str[i];
		int found;
		if (lookingForDelim) {
			found = TKCharIsDelim(tk, c);
		} else {
			found = !TKCharIsDelim(tk, c);
		}
		if (found) {
			return i;
		}
	}
	return -1;
}
int TKNextTokenIndex(TokenizerT *tk) {
	return TKNextStringPart(tk, tk->index, 1);
}
int TKFirstNonTokenChar(TokenizerT *tk, int index) {
	return TKNextStringPart(tk, index, 0);
}

/*
 * Checks if char is in the set
 */
int charIsInSet(char c, char * set) {
	int len = strlen(set);
	int i;
	for(i=0; i<len; i++) {
		if (c == set[i]) {
			return 1;
		}
	}
	return 0;
}
int TKCharIsDelim(TokenizerT *tk, char c) {
	return charIsInSet(c, tk->delim);
}
int charIsEscapeChar(char c) {
	char * delim = "\n\t\v\b\r\f\a\\\"";
	return charIsInSet(c, delim);
}

/*
 * converts a char to its hexadecimal string representation
 * returns a char * that needs to be freed
 */
//DONE
char * convertCharToHex(char str) {
	//"[0x00]"
	int i = str;
	int len = 6;
	char * hex = calloc(sizeof(char), len+1);
	sprintf(hex, "[0x%02x]", i);
	hex[len] = '\0';
	return hex;
}

char * escapeStringWithHex(char * str) {
	//first, find out the lenghth the new string
	int len = strlen(str);
	int new_len = len;
	int num_delim = 0;
	int extra_per_delim = 6;
	
	int i;
	for (i = 0; i < len; ++i) {
		char c = str[i];
		if (charIsEscapeChar(c)) {
			num_delim++;
		}
	}

	new_len += num_delim * extra_per_delim;

	DEBUG_PRINTLN_F("new length = %d", new_len);

	char * new_str = calloc(sizeof(char), new_len+1);
	new_str[new_len] = '\0';

	int adj_i = 0;
	for (int i = 0; i < len; ++i) {
		char c = str[i];
		DEBUG_PRINTLN_F("i = %d", i);
		if (charIsEscapeChar(c)) {
			char * hex = convertCharToHex(c);
			int hex_len = strlen(hex);
			strncpy(new_str+adj_i, hex, hex_len);
			free(hex);
			adj_i+=hex_len;
			DEBUG_PRINTLN_F("(manual update) i = %d", i);
		} else {
			new_str[adj_i] = c;
			adj_i+=1;
		}
	}
	new_str[new_len] = '\0';
	return new_str;
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
	char * str = tk->input;
	int len = strlen(str);
	
	//updates the index for beginning of function
	//ensures that leading delims will not be printed
	tk->index = TKFirstNonTokenChar(tk, tk->index);
	int start_index = tk->index;

	//provides for the case where index is beyond bounds of the string
	if (start_index < 0 || start_index >= len) {
		return NULL;
	}
	int end_index = TKNextTokenIndex(tk);
	if (end_index == -1) {
		end_index = len;
	}
	//update index for next call
	tk->index = end_index;
	
	int new_len = (end_index - start_index);
	char * token = calloc(sizeof(char), new_len + 1); //+1 for null byte
	DEBUG_PRINTLN_F("%d, %d", start_index, end_index);
	strncpy(token, str + start_index, new_len);
	token[new_len] = '\0';

	char * escaped_token = escapeStringWithHex(token);
	free(token);

	return escaped_token;
}

/*
 * This function converts "\*" to '\*' where the first is a string of 2 char 
 * and the second is 1 character.
 */
//DONE
char * unescapeString(char * str) {
	int new_len = 0;
	int len = strlen(str);
	char * buffer = calloc(sizeof(char), len+1);
	buffer[len]='\0';
	int i;
	for (i=0; i<len; i++) {
		char curr = str[i];
		if (curr == '\\') {
			i++;
			char next = str[i];
			switch(next) {
				case 'n' : 
					curr = '\n';
					break;
				case 't' : 
					curr = '\t';
					break;
				case 'v' : 
					curr = '\v';
					break;
				case 'b' : 
					curr = '\b';
					break;
				case 'r' : 
					curr = '\r';
					break;
				case 'f' : 
					curr = '\f';
					break;
				case 'a' : 
					curr = '\a';
					break;
				case '\\' :
					i--;
					curr = '\\';
					break;
				case '\0':
					curr = '\\';
					break;
				default:
					i--;
					curr = '\\';
					break;
			}

		}
		buffer[new_len] = curr;
		new_len++;
	}
	char * new_buffer = calloc(sizeof(char), new_len+1);
	strncpy ( new_buffer, buffer, new_len );
	free(buffer);
	new_buffer[new_len]='\0';
	return new_buffer;
}


/*
 * main will have two string arguments (in argv[1] and argv[2]).
 * The first string contains the separator characters.
 * The second string contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */
int main(int argc, char **argv) {
	DEBUG_PRINTLN_F("%d", argc);
	if (argc != 3) {
		printf("%s\n", "** Invalid Arguments: `$ prog <delim> <string>`");
		exit(1);
	}
	TokenizerT * tk = TKCreate(argv[1], argv[2]);
	char * token = TKGetNextToken(tk);
	while (token != NULL) {
		printf("%s\n", token);
		free(token);
		token = TKGetNextToken(tk);
	}
	TKDestroy(tk);
}
