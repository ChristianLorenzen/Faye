use std::{env, process};
mod f_lexer;
use f_lexer::{Lexer, token};
mod f_io;
use f_io::io;

fn main() {
    let args : Vec<String> = env::args().collect();

    if args.len() < 2 {
        println!("Not enough arguments specified: please use format cargo run 'file'");
        process::exit(1);
    }

    let file_contents = io::file_read(&args[1]).unwrap_or_else(|err| {
       println!("Problem reading specified file: {err}");
       process::exit(1);
    });

    let mut lex : Lexer = Lexer::init(&file_contents);

    let mut token : token::Token = lex.next();
    println!("The first lexer token is {} with type {}", &token.value, &token.token_type);

    while !matches!(token.token_type, token::TokenType::TOKEN_EOF) {
        token = lex.next();
        println!("The first lexer token is {} with type {}", &token.value, &token.token_type);
    }

}
