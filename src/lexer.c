#include "include/lexer.h"
#include "include/token.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>


lexer_T* init_lexer(char* contents) 
{
    lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->contents = contents;
    lexer->i = 0;
    lexer->c = contents[lexer->i];
    lexer->line = 1;

    return lexer;
}

void lexer_advance(lexer_T* lexer) 
{
    if (lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {
        lexer-> i += 1;
        lexer-> c = lexer->contents[lexer->i];
    }
}

void lexer_skip_whitespace(lexer_T* lexer)
{
    while(lexer->c == ' ' || lexer->c == '\n') {

        if (lexer->c == 10) { lexer->line += 1;}

        lexer_advance(lexer);
    }
}

token_T* lexer_get_next_token(lexer_T* lexer)
{
    while(lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {

        if (lexer->c == ' ' || lexer->c == 10) {
            lexer_skip_whitespace(lexer);
        }

        if (isdigit(lexer->c)){
            return lexer_collect_number(lexer);
        }

        if(isalnum(lexer->c)){
            return lexer_collect_id(lexer);
        }

        if (lexer->c == '"'){
            return lexer_collect_string(lexer);
        }

        if (lexer->c == '#') {
            return lexer_collect_line_comment(lexer);
        }

        switch(lexer->c) {
            case '=': return lexer_advance_with_token(lexer, init_token_with_line(TOKEN_EQUALS, lexer_get_current_char_as_string(lexer), lexer->line)); break;
            case ';': return lexer_advance_with_token(lexer, init_token_with_line(TOKEN_SEMICOLON, lexer_get_current_char_as_string(lexer), lexer->line)); break;
            case '(': return lexer_advance_with_token(lexer, init_token_with_line(TOKEN_LPARENTHESIS, lexer_get_current_char_as_string(lexer), lexer->line)); break;
            case ')': return lexer_advance_with_token(lexer, init_token_with_line(TOKEN_RPARENTHESIS, lexer_get_current_char_as_string(lexer), lexer->line)); break;
            case '{': return lexer_advance_with_token(lexer, init_token_with_line(TOKEN_LBRACE, lexer_get_current_char_as_string(lexer), lexer->line)); break;
            case '}': return lexer_advance_with_token(lexer, init_token_with_line(TOKEN_RBRACE, lexer_get_current_char_as_string(lexer), lexer->line)); break;
            case ',': return lexer_advance_with_token(lexer, init_token_with_line(TOKEN_COMMA, lexer_get_current_char_as_string(lexer), lexer->line)); break;
            case '+': return lexer_advance_with_token(lexer, init_token_with_line(TOKEN_PLUS, lexer_get_current_char_as_string(lexer), lexer->line)); break;
            case '-': return lexer_advance_with_token(lexer, init_token_with_line(TOKEN_MINUS, lexer_get_current_char_as_string(lexer), lexer->line)); break;
            case '/': return lexer_advance_with_token(lexer, init_token_with_line(TOKEN_DIVIDE, lexer_get_current_char_as_string(lexer), lexer->line)); break;
            case '*': return lexer_advance_with_token(lexer, init_token_with_line(TOKEN_MULTIPLY, lexer_get_current_char_as_string(lexer), lexer->line)); break;
        }
    }

    return init_token(TOKEN_EOF, "\0");
}

token_T* lexer_collect_string(lexer_T* lexer)
{
    lexer_advance(lexer);
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while (lexer->c != '"') {
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);
        lexer_advance(lexer);
    }
    lexer_advance(lexer);

    return init_token_with_line(TOKEN_STRING, value, lexer->line);
}

token_T* lexer_collect_number(lexer_T* lexer)
{
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';
    int isFloat = false;

    while (isdigit(lexer->c) || lexer->c == '.')
    {
        if (lexer->c == '.') {
            isFloat = true;
        }
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);
        lexer_advance(lexer);
    }

    if (isFloat) {
        return init_token_with_line(TOKEN_FLOAT, value, lexer->line);
    } 
    else 
    {
        return init_token_with_line(TOKEN_INT, value, lexer->line);
    }
}


token_T* lexer_collect_id(lexer_T* lexer) 
{
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while (isalnum(lexer->c)) {
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);

        lexer_advance(lexer);
    }

    if (strcmp(value, "true") == 0 || strcmp(value, "false") == 0) {
        return init_token_with_line(TOKEN_BOOL, value, lexer->line);
    }

    return init_token_with_line(TOKEN_ID, value, lexer->line);
}

token_T* lexer_collect_line_comment(lexer_T* lexer) 
{
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    //Should eat input until newline and do nothing.
    //A comment should be stripped away at lexer, why am I sending it through to parser??
    while(lexer->c != '\n' && lexer->c != '\0') 
    {
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);
        lexer_advance(lexer);
    }

    return init_token_with_line(TOKEN_LINE_COMMENT, value, lexer->line);
}

token_T* lexer_advance_with_token(lexer_T* lexer, token_T* token) 
{
    lexer_advance(lexer);

    return token;
}

char* lexer_get_current_char_as_string(lexer_T* lexer)
{
    char* str = calloc(2, sizeof(char));
    str[0] = lexer->c;
    str[1] = '\0';

    return str;
}