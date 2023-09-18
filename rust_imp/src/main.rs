use std::{env, process};
mod lexer;
use lexer::{f_token, f_lexer};
mod io;
use io::{f_io};

fn main() {
    let args : Vec<String> = env::args().collect();
    
    if args.len() < 2 {
        println!("Not enough arguments specified: please use format cargo run -filename-");
        process::exit(1);
    }
    
    let file_contents = f_io::file_read(&args[1]).unwrap_or_else(|err| {
       println!("Problem reading specified file: {err}");
       process::exit(1);
    });
    
    let mut lex : f_lexer::Lexer = f_lexer::Lexer::init(&file_contents);

    let mut token : f_token::Token = lex.next();
    println!("The first lexer token is {} with type {}", &token.value, &token.token_type);

    while !matches!(token.token_type, f_token::TokenType::TOKEN_EOF) {
        token = lex.next();
        println!("The first lexer token is {} with type {}", &token.value, &token.token_type);
    }

}
