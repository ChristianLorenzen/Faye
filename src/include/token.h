#ifndef TOKEN_H
#define TOKEN_H
typedef struct TOKEN_STRUCT {
    enum {

        // Standard typing tokens
        TOKEN_ID,
        TOKEN_EQUALS,
        TOKEN_SEMICOLON,
        TOKEN_LPARENTHESIS,
        TOKEN_RPARENTHESIS,
        TOKEN_LBRACE,
        TOKEN_RBRACE,
        TOKEN_COMMA,
        TOKEN_NEWLINE,

        //Math related tokens,
        TOKEN_PLUS,
        TOKEN_MINUS,
        TOKEN_DIVIDE,
        TOKEN_MULTIPLY,

        //Type tokens,
        TOKEN_STRING,
        TOKEN_INT,
        TOKEN_FLOAT,
        TOKEN_BOOL,

        //ETC Tokens,
        TOKEN_LINE_COMMENT,
        TOKEN_MULTILINE_COMMENT,
        TOKEN_EOF,
    } type;

    char* value;

    unsigned int line;

} token_T;

token_T* init_token(int type, char* value);

token_T* init_token_with_line(int type, char* value, unsigned int line);


#endif