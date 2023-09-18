use std::{env, process};
mod f_lexer;
use f_lexer::{token, Lexer};
mod f_io;
use f_io::io;
mod f_parser;
use f_parser::parser;
mod f_ast;
mod f_err;

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        println!("Not enough arguments specified: please use format cargo run 'file'");
        process::exit(1);
    }

    let file_contents = io::file_read(&args[1]).unwrap_or_else(|err| {
        println!("Problem reading specified file: {err}");
        process::exit(1);
    });

    let mut lex: Lexer = Lexer::init(&file_contents);
    let mut token: token::Token =
        token::Token::create(token::TokenType::TOKEN_LINE_COMMENT, &"".to_string(), 0, 0);
    while !matches!(token.token_type, token::TokenType::TOKEN_EOF) {
        token = lex.next();
        token.print();
    }
}
