#ifndef TOKENIZER
#define TOKENIZER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"

TokenizerT *TKCreate(char *separators, char *ts);
void TKDestroy(TokenizerT *tk);
char *TKGetNextToken(TokenizerT *tk);
int TKCharIsDelim(TokenizerT *tk, char c);
char * convertEscapeToHex(char str);
char * unescapeString(char * str);


#endif

