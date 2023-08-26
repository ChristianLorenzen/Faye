#ifndef PARSER_H
#define PARSER_H
#include "AST.h"
#include "lexer.h"
#include "scope.h"

typedef struct PARSER_STRUCT
 {
    lexer_T* lexer;
    token_T* current_token;
    token_T* previous_token;
    scope_T* scope;
} parser_T;

parser_T* init_parser(lexer_T* lexer);

void parser_eat(parser_T* parser, int token_type);

AST_T* parser_parse(parser_T* parser, scope_T* scope);

AST_T* parser_parse_statement(parser_T* parser, scope_T* scope);

AST_T* parser_parse_statements(parser_T* parser, scope_T* scope);

AST_T* parser_parse_line_comment(parser_T* parser, scope_T* scope);

AST_T* parser_parse_expression(parser_T* parser, scope_T* scope);

AST_T* parser_parse_factor(parser_T* parser, scope_T* scope);

AST_T* parser_parse_term(parser_T* parser, scope_T* scope);

AST_T* parser_parse_function_call(parser_T* parser, scope_T* scope);

AST_T* parser_parse_variable_definition(parser_T* parser, scope_T* scope, unsigned int var_type);

AST_T* parser_parse_function_definition(parser_T* parser, scope_T* scope);

AST_T* parser_parse_variable(parser_T* parser, scope_T* scope);

AST_T* parser_parse_int(parser_T* parser, scope_T* scope);

AST_T* parser_parse_float(parser_T* parser, scope_T* scope);

AST_T* parser_parse_bool(parser_T* parser, scope_T* scope);

AST_T* parser_parse_string(parser_T* parser, scope_T* scope);

AST_T* parser_parse_id(parser_T* parser, scope_T* scope);

#endif