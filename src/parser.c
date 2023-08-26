#include "include/parser.h"
#include <stdio.h>
#include <string.h>
#include "include/scope.h"

static scope_T* get_node_scope(parser_T* parser, AST_T* node) {
    return node->scope == (void*)0 ? parser->scope : node->scope;
}

parser_T *init_parser(lexer_T *lexer)
{
    parser_T *parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->current_token = lexer_get_next_token(lexer);
    parser->previous_token = parser->current_token;
    parser->scope = init_scope();

    return parser;
}

void parser_eat(parser_T *parser, int token_type)
{
    if (parser->current_token->type == token_type) {
        parser->previous_token = parser->current_token;
        parser->current_token = lexer_get_next_token(parser->lexer);

    } else {
        printf("Line %d - Unexpected Token '%s', with type %d\n", parser->current_token->line, parser->current_token->value, parser->current_token->type);
        exit(1);
    }
}

AST_T *parser_parse(parser_T *parser, scope_T* scope)
{
    return parser_parse_statements(parser, scope);
}

AST_T *parser_parse_statement(parser_T *parser, scope_T* scope)
{

    switch(parser->current_token->type)
    {
        case TOKEN_ID: return parser_parse_id(parser, scope);
        //case TOKEN_INT: return parser_parse_int(parser, scope);
        //case TOKEN_FLOAT: return parser_parse_float(parser, scope);
        //case TOKEN_LINE_COMMENT: return parser_parse_line_comment(parser, scope);
        default:
    }

    return init_ast(AST_NOOP);
}

AST_T *parser_parse_statements(parser_T *parser, scope_T* scope)
{
    AST_T* compound = init_ast(AST_COMPOUND);
    compound->scope = scope;
    compound->compound_value = calloc(1, sizeof(struct AST_STRUCT*));

    AST_T* ast_statement = parser_parse_statement(parser, scope);
    ast_statement->scope = scope;
    compound->compound_value[0] = ast_statement;
    compound->compound_size += 1;

    //Currently going through statements until a semicolon is found while ignoring line comments.
    while(parser->current_token->type == TOKEN_SEMICOLON || parser->current_token->type == TOKEN_LINE_COMMENT) 
    {

        //If current token is line comment, eat and continue as current statement is still ongoing.
        if (parser->current_token->type == TOKEN_LINE_COMMENT)
        {
            parser_eat(parser,TOKEN_LINE_COMMENT);
        }

        //If current token is semi, eat and continue as last "statement" ended, starting new one.
        if (parser->current_token->type == TOKEN_SEMICOLON)
        {
            parser_eat(parser, TOKEN_SEMICOLON);
        }
        
        AST_T* ast_statement = parser_parse_statement(parser, scope);

        if (ast_statement && ast_statement->type != AST_LINE_COMMENT) 
        {
            compound->compound_size += 1;
            compound->compound_value = realloc(
                compound->compound_value, 
                compound->compound_size * sizeof(struct AST_STRUCT*)
            );
            compound->compound_value[compound->compound_size - 1] = ast_statement;
        }
    }
    return compound;
}


AST_T *parser_parse_expression(parser_T *parser, scope_T* scope)
{
    //printf("Parse '%s' with token %d\n", parser->current_token->value, parser->current_token->type);
    switch(parser->current_token->type) {
        case TOKEN_STRING: return parser_parse_string(parser, scope);
        case TOKEN_INT: return parser_parse_int(parser,scope);
        case TOKEN_FLOAT: return parser_parse_float(parser, scope);
        case TOKEN_BOOL: return parser_parse_bool(parser, scope);
        case TOKEN_ID: return parser_parse_id(parser, scope);
        default:
    }

    return init_ast(AST_NOOP);
}

AST_T *parser_parse_factor(parser_T *parser, scope_T* scope)
{
    AST_T* ast = init_ast_with_line(AST_LINE_COMMENT, parser->current_token->line);

    return ast;
}

AST_T *parser_parse_term(parser_T *parser, scope_T* scope)
{
    AST_T* ast = init_ast_with_line(AST_LINE_COMMENT, parser->current_token->line);

    return ast;
}

AST_T* parser_parse_line_comment(parser_T* parser, scope_T* scope)
{
    AST_T* ast = init_ast_with_line(AST_LINE_COMMENT, parser->current_token->line);

    ast->scope = scope;

    return ast;
}

AST_T *parser_parse_function_call(parser_T *parser, scope_T* scope)
{
    AST_T* function_call = init_ast_with_line(AST_FUNCTION_CALL, parser->current_token->line);

    function_call->function_call_name = parser->previous_token->value;
    parser_eat(parser, TOKEN_LPARENTHESIS);

    function_call->function_call_arguments = calloc(1, sizeof(struct AST_STRUCT*));

    AST_T* ast_expr = parser_parse_expression(parser, scope);
    function_call->function_call_arguments[0] = ast_expr;
    function_call->function_call_arguments_size += 1;

    while(parser->current_token->type == TOKEN_COMMA) 
    {
        parser_eat(parser, TOKEN_COMMA);

        AST_T* ast_expr = parser_parse_expression(parser, scope);
        function_call->function_call_arguments_size += 1;
        function_call->function_call_arguments = realloc(
            function_call->function_call_arguments, 
            function_call->function_call_arguments_size * sizeof(struct AST_STRUCT*)
        );
        function_call->function_call_arguments[function_call->function_call_arguments_size - 1] = ast_expr;
    }

    parser_eat(parser, TOKEN_RPARENTHESIS);

    function_call->scope = scope;

    return function_call;
}

AST_T* parser_parse_function_value(parser_T* parser, scope_T* scope) {
    
}

AST_T* parser_parse_typed_variable(parser_T* parser, scope_T* scope, unsigned int var_type) {
    char* variable_type = parser->current_token->value;
    parser_eat(parser,TOKEN_ID);
    char* variable_definition_variable_name = parser->current_token->value;
    parser_eat(parser, TOKEN_ID);

    AST_T* variable_definition = init_ast_with_line(AST_VARIABLE_DEFINITION, parser->current_token->line);
    variable_definition->var_type = var_type;
    variable_definition->variable_definition_variable_name = variable_definition_variable_name;

    variable_definition->scope = scope;

    return variable_definition;
}

AST_T* parser_parse_variable_definition(parser_T* parser, scope_T* scope, unsigned int var_type) {
    char* variable_type = parser->current_token->value;
    parser_eat(parser, TOKEN_ID); //var, string, int etc..
    char* variable_definition_variable_name = parser->current_token->value;
    parser_eat(parser, TOKEN_ID); //var name

    if (parser->current_token->type == TOKEN_EQUALS) {
        parser_eat(parser, TOKEN_EQUALS); // var name =
        AST_T* variable_definition_value = parser_parse_expression(parser, scope);

        //printf("Parser parsed variable name %s and got var-type %d\n", variable_definition_variable_name, variable_definition_value->type);

        //Check that value matches the variable type
        switch(var_type){
            case 0:
                //printf("string variable type with value %s\n", variable_definition_value->string_value);
                if (variable_definition_value->type != AST_STRING) { printf("Line %d - cannot assign %d to string\n", parser->current_token->line, variable_definition_value->type); exit(2); }
                break;
            case 1:
                //printf("int variable type with value %d\n", variable_definition_value->int_value);
                if (variable_definition_value->type != AST_INT) { printf("Line %d - cannot assign %d to int\n", parser->current_token->line, variable_definition_value->type); exit(2); }
                break;
            case 2:
                //printf("float variable type with value %f\n", variable_definition_value->float_value);
                if (variable_definition_value->type != AST_FLOAT) { printf("Line %d - cannot assign %d to float\n", parser->current_token->line, variable_definition_value->type); exit(2); }
                break;
            case 3:
                //printf("bool variable type with value %d\n", variable_definition_value->bool_value);
                if (variable_definition_value->type != AST_BOOL) { printf("Line %d - cannot assign %d to bool\n", parser->current_token->line, variable_definition_value->type); exit(2); }
                break;
        }

        AST_T* variable_definition = init_ast_with_line(AST_VARIABLE_DEFINITION, parser->current_token->line);
        variable_definition->var_type = var_type;
        variable_definition->variable_definition_variable_name = variable_definition_variable_name;
        variable_definition->variable_definition_value = variable_definition_value;

        variable_definition->scope = scope;

        return variable_definition;
    }
    else {
        AST_T* variable_definition = init_ast_with_line(AST_VARIABLE_DEFINITION, parser->current_token->line);
        variable_definition->var_type = var_type;
        variable_definition->variable_definition_variable_name = variable_definition_variable_name;

        variable_definition->scope = scope;

        return variable_definition;
    }
}

AST_T* parser_parse_function_definition(parser_T* parser, scope_T* scope) 
{
    AST_T* ast = init_ast_with_line(AST_FUNCTION_DEFINITION, parser->current_token->line);

    parser_eat(parser, TOKEN_ID); //function keyword

    char* function_name = parser->current_token->value;

    ast->function_definition_name = calloc(strlen(function_name) + 1, sizeof(char));
    strcpy(ast->function_definition_name, function_name);

    parser_eat(parser, TOKEN_ID); // function name
    parser_eat(parser, TOKEN_LPARENTHESIS); //remove lparenthesis

    //arguments to functions would be "eaten" here.
    if (parser->current_token->type != TOKEN_RPARENTHESIS) {
        ast->function_def_args = calloc(1, sizeof(struct AST_STRUCT*));
        AST_T* arg = parser_parse_id(parser, scope);
        ast->function_def_args_size += 1;
        ast->function_def_args[ast->function_def_args_size-1] = arg;

        while(parser->current_token->type == TOKEN_COMMA) {
            parser_eat(parser, TOKEN_COMMA);
            ast->function_def_args_size += 1;
            ast->function_def_args = realloc(ast->function_def_args, ast->function_def_args_size * sizeof(struct AST_STRUCT*));
            AST_T* arg = parser_parse_id(parser, scope);
            ast->function_def_args[ast->function_def_args_size-1] = arg;
        }
    }
    parser_eat(parser, TOKEN_RPARENTHESIS); //remove rparenthesis
    parser_eat(parser, TOKEN_LBRACE);

    ast->function_definition_body = parser_parse_statements(parser, scope);

    parser_eat(parser, TOKEN_RBRACE);

    ast->scope = scope;

    return ast;
}

AST_T *parser_parse_variable(parser_T *parser, scope_T* scope)
{
    char* token_value = parser->current_token->value;
    parser_eat(parser, TOKEN_ID); //var name or fn call name

    if (parser->current_token->type == TOKEN_LPARENTHESIS) {
        return parser_parse_function_call(parser, scope);
    } 

    AST_T* ast_variable = init_ast_with_line(AST_VARIABLE, parser->current_token->line);
    ast_variable->variable_name = token_value;

    ast_variable->scope = scope;

    return ast_variable;
}

AST_T* parser_parse_int(parser_T* parser, scope_T* scope)
{
    printf("Parsing int: %s\n", parser->current_token->value);

    AST_T* ast_int = init_ast_with_line(AST_INT, parser->current_token->line);

    ast_int->int_value = atoi(parser->current_token->value);

    parser_eat(parser, TOKEN_INT);

    ast_int->scope = scope;

    return ast_int;
}

AST_T* parser_parse_float(parser_T* parser, scope_T* scope)
{
    printf("Parsing float: %s\n", parser->current_token->value);
    AST_T* ast_float = init_ast_with_line(AST_FLOAT, parser->current_token->line);

    ast_float->float_value = atof(parser->current_token->value);

    parser_eat(parser, TOKEN_FLOAT);

    ast_float->scope = scope;

    return ast_float;
}

AST_T* parser_parse_bool(parser_T* parser, scope_T* scope)
{
    printf("Parsing bool: %s\n", parser->current_token->value);

    AST_T* ast_bool = init_ast_with_line(AST_BOOL, parser->current_token->line);

    int boolV = (strcmp(parser->current_token->value, "true") == 0) ? 1 : 0;

    ast_bool->bool_value = boolV;

    parser_eat(parser, TOKEN_BOOL);

    ast_bool->scope = scope;

    return ast_bool;
}

AST_T *parser_parse_string(parser_T *parser, scope_T* scope)
{
    printf("Parsing string: %s\n", parser->current_token->value);

    AST_T* ast_string = init_ast_with_line(AST_STRING, parser->current_token->line);

    ast_string->string_value = parser->current_token->value;

    parser_eat(parser, TOKEN_STRING);

    ast_string->scope = scope;

    return ast_string;
}

AST_T* parser_parse_id(parser_T* parser, scope_T* scope) 
{

    if (strcmp(parser->current_token->value, "int") == 0) 
    {
        //printf("Found int variable: \n");
        return parser_parse_variable_definition(parser, scope, 1);
    }
    else if (strcmp(parser->current_token->value, "string") == 0) 
    {
        //printf("Found string variable: \n");
        return parser_parse_variable_definition(parser, scope, 0);
    }
    else if (strcmp(parser->current_token->value, "float") == 0) 
    {
        //printf("Found float variable: \n");
        return parser_parse_variable_definition(parser, scope, 2);
    }
    else if (strcmp(parser->current_token->value, "bool") == 0) 
    {
        //printf("Found bool variable: \n");
        return parser_parse_variable_definition(parser, scope, 3);
    }
    else if (strcmp(parser->current_token->value, "var") == 0) 
    {
        //printf("Found var variable: \n");
        return parser_parse_variable_definition(parser, scope, 4);
    } 
    else if (strcmp(parser->current_token->value, "function") == 0)
    {
        return parser_parse_function_definition(parser, scope);
    } 
    else if (strcmp(parser->current_token->value, "=") == 0) {
        return parser_parse_function_value(parser,scope);
    }
    else {
        return parser_parse_variable(parser, scope);
    }
}