#ifndef TOKENIZER
#define TOKENIZER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"

struct TokenizerT_;
typedef struct TokenizerT_ TokenizerT;

//Tokenizer functions
TokenizerT *TKCreate(char *separators, char *ts);
void TKDestroy(TokenizerT *tk);
int TKNextStringPart(TokenizerT *tk, int index, int lookingForDelim);
int TKNextTokenIndex(TokenizerT *tk);
int TKFirstNonTokenChar(TokenizerT *tk, int index);
char *TKGetNextToken(TokenizerT *tk);
int TKCharIsDelim(TokenizerT *tk, char c);

int charIsInSet(char c, char * set);
int charIsEscapeChar(char c);

//char operation functions
char * convertCharToHex(char str);
char * unescapeString(char * str);
char * escapeStringWithHex(char * str);
char * stingWithoutTrailingBackslash(char * str);

//main function
int main(int argc, char **argv);


#endif

