#ifndef AST_H
#define AST_H
#include <stdlib.h>

typedef struct AST_STRUCT
{
    enum
    {
        AST_VARIABLE_DEFINITION,
        AST_FUNCTION_DEFINITION,
        AST_VARIABLE,
        AST_FUNCTION_CALL,
        AST_STRING,
        AST_INT,
        AST_FLOAT,
        AST_BOOL,
        AST_COMPOUND,
        AST_LINE_COMMENT,
        AST_NOOP,
    } type;

    enum variable_type
    {
        VAR_STRING,
        VAR_INT,
        VAR_FLOAT,
        VAR_BOOL,
    } var_type;

    struct SCOPE_STRUCT *scope;

    unsigned int line;

    /* AST_VBARIABLE DEFITION */
    char *variable_definition_variable_name;
    struct AST_STRUCT *variable_definition_value;

    /* AST FUNCTION DEFITION */
    struct AST_STRUCT *function_definition_body;
    char *function_definition_name;
    struct AST_STRUCT **function_def_args;
    size_t function_def_args_size;

    /* AST_VARIABLE */
    char *variable_name;
    // DECLARED ABOVE;
    // enum variable_type var_type;

    /* AST_FUNCTION_CALL */
    char *function_call_name;
    struct AST_STRUCT **function_call_arguments;
    size_t function_call_arguments_size;

    /* AST_STRING */
    char *string_value;

    /* AST_INT */
    int int_value;

    /* AST_FLOAT */
    float float_value;

    /* AST_BOOL */
    int bool_value;

    /* AST_COMPOUND */
    struct AST_STRUCT **compound_value;
    size_t compound_size;

} AST_T;

AST_T *init_ast(int type);

AST_T *init_ast_with_line(int type, unsigned int line);

#endif