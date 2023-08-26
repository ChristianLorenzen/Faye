#include "include/AST.h"


AST_T* init_ast(int type) {
    AST_T* ast = calloc(1, sizeof(struct AST_STRUCT));
    ast->type = type;
    ast->line = 0;

    ast->scope = (void*) 0;

    /* AST_VBARIABLE DEFITION */
    ast->variable_definition_variable_name = (void*) 0;
    ast->variable_definition_value = (void*) 0;

    /* AST FUNCTION DEFINITION */
    ast->function_definition_body = (void*) 0;
    ast->function_definition_name = (void*) 0;
    ast->function_def_args = (void*) 0;
    ast->function_def_args_size = 0;

    /* AST_VARIABLE */
    ast->variable_name = (void*) 0;
    
    /* AST_FUNCTION_CALL */
    ast->function_call_name = (void*) 0;
    ast->function_call_arguments = (void*) 0;
    ast->function_call_arguments_size = 0;

    /* AST_STRING */
    ast->string_value = (void*) 0;

    /* AST_COMPOUND */
    ast->compound_value = (void*)0;
    ast->compound_size = 0;

    return ast;
}

AST_T* init_ast_with_line(int type, unsigned int line) {
    AST_T* ast = calloc(1, sizeof(struct AST_STRUCT));
    ast->type = type;
    ast->line = line;

    ast->scope = (void*) 0;

    /* AST_VBARIABLE DEFITION */
    ast->variable_definition_variable_name = (void*) 0;
    ast->variable_definition_value = (void*) 0;

    /* AST FUNCTION DEFINITION */
    ast->function_definition_body = (void*) 0;
    ast->function_definition_name = (void*) 0;

    /* AST_VARIABLE */
    ast->variable_name = (void*) 0;
    
    /* AST_FUNCTION_CALL */
    ast->function_call_name = (void*) 0;
    ast->function_call_arguments = (void*) 0;
    ast->function_call_arguments_size = 0;

    /* AST_STRING */
    ast->string_value = (void*) 0;

    /* AST_COMPOUND */
    ast->compound_value = (void*)0;
    ast->compound_size = 0;

    return ast;
}