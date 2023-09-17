#include "include/visitor.h"
#include "include/scope.h"
#include <stdio.h>
#include <string.h>

static AST_T* builtin_function_print(visitor_T* visitor, AST_T** args, int args_size) {
    for (int i = 0; i < args_size; i++) {
        AST_T* visited_ast = visitor_visit(visitor, args[i]);

        switch (visited_ast->type)
        {
            case AST_STRING: printf("%s\n", visited_ast->string_value); break;
            case AST_INT: printf("%d\n", visited_ast->int_value); break;
            case AST_FLOAT: printf("%f\n", visited_ast->float_value); break;
            case AST_BOOL: visited_ast->bool_value == 1 ? printf("true\n") : printf("false\n"); break;
            default: printf("%p\n", visited_ast); break;
        }

    }

    return init_ast(AST_NOOP);
}

visitor_T* init_visitor() 
{
    visitor_T* visitor = calloc(1, sizeof(struct VISITOR_STRUCT));
    visitor->variable_definitions = (void*) 0;
    visitor->variable_definitions_size = 0;

    return visitor;
}

AST_T* visitor_visit(visitor_T* visitor, AST_T* node) 
{
    switch(node->type) {
        case AST_VARIABLE_DEFINITION: return visitor_visit_variable_definition(visitor, node);
        case AST_FUNCTION_DEFINITION: return visitor_visit_function_definition(visitor, node);
        case AST_VARIABLE: return visitor_visit_variable(visitor, node);
        case AST_FUNCTION_CALL: return visitor_visit_function_call(visitor, node);
        case AST_STRING: return visitor_visit_string(visitor, node);
        case AST_INT: return visitor_visit_int(visitor, node);
        case AST_FLOAT: return visitor_visit_float(visitor, node);
        case AST_BOOL: return visitor_visit_float(visitor, node);
        case AST_COMPOUND: return visitor_visit_compound(visitor, node);
        case AST_LINE_COMMENT: return node;
        case AST_NOOP: return node;
    }

    printf("Line %d - Uncaught statement of type '%d'\n", node->line, node->type);

    exit(1);

    return init_ast(AST_NOOP);
}

AST_T* visitor_visit_variable_definition(visitor_T* visitor, AST_T* node)
{
    scope_add_variable_definition(node->scope, node);

    return node;
}

AST_T* visitor_visit_function_definition(visitor_T* visitor, AST_T* node)
{
    scope_add_function_definition( node->scope, node );

    return node;
}

AST_T* visitor_visit_variable(visitor_T* visitor, AST_T* node)
{
    AST_T* vdef = scope_get_variable_definition(node->scope, node->variable_name);

    if (vdef == (void*)0)
    {
        printf("Undefined variable '%s'\n", node->variable_name);
        exit(1);
        return visitor_visit(visitor, vdef->variable_definition_value);
    }

    AST_T* ast_var = init_ast(AST_VARIABLE_DEFINITION);
    AST_T* string_ast = init_ast(AST_STRING);
    string_ast->string_value = "This is a test";
    ast_var->variable_definition_value = string_ast;

    return visitor_visit(visitor, vdef->variable_definition_value);
}

AST_T* visitor_visit_function_call(visitor_T* visitor, AST_T* node)
{
    if (strcmp(node->function_call_name, "print") == 0) 
    {
        return builtin_function_print(visitor, node->function_call_arguments, node->function_call_arguments_size);
    }
    
    AST_T* fdef = scope_get_function_definition(node->scope, node->function_call_name);

    if (fdef != (void*) 0) {
        return visitor_visit(visitor, fdef->function_definition_body);
    }

    printf("Line %d - Undefined method '%s'\n", node->line, node->function_call_name);
}

AST_T* visitor_visit_string(visitor_T* visitor, AST_T* node)
{
    return node;
}

AST_T* visitor_visit_int(visitor_T* visitor, AST_T* node)
{
    return node;
}

AST_T* visitor_visit_float(visitor_T* visitor, AST_T* node)
{
    return node;
}

AST_T* visitor_visit_bool(visitor_T* visitor, AST_T* node)
{
    return node;
}

AST_T* visitor_visit_comment(visitor_T* visitor, AST_T* node) 
{
    return node;
}

AST_T* visitor_visit_compound(visitor_T* visitor, AST_T* node)
{
    for (int i = 0; i < node->compound_size; i++)
    {
        AST_T* nodeV = visitor_visit(visitor, node->compound_value[i]);
    }

    return init_ast(AST_NOOP);
}