#include <stdio.h>
#include "include/lexer.h"
#include "include/parser.h"
#include "include/visitor.h"
#include "include/io.h"

void print_help()
{
    printf("Usage:\n faye <filename>\n");
    exit(2);
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        print_help();
    }

    lexer_T* lexer = init_lexer(get_file_contents(argv[1]));
    parser_T* parser = init_parser(lexer);

    token_T* tok = (void*) 0;

    //while ((tok = lexer_get_next_token(lexer))->type != TOKEN_EOF) {
    //   printf("TOKEN( %d - %s )\n", tok->type, tok->value);
    //}

    //Parser contains global scope.
    //TODO-1: Add subscopes for each found function..
    AST_T* root = parser_parse(parser, parser->scope);
    visitor_T* visitor = init_visitor();
    visitor_visit(visitor, root);

    return 0;
}