#include "include/token.h"
#include <stdlib.h>

token_T* init_token(int type, char* value) {
    token_T* token = calloc(1, sizeof(struct TOKEN_STRUCT));
    token->type = type;
    token->value = value;

    return token;
}

token_T* init_token_with_line(int type, char* value, unsigned int line) 
{
    token_T* token = calloc(1, sizeof(struct TOKEN_STRUCT));
    token->type = type;
    token->value = value;
    token->line = line;

    return token;
}