use std::{env, process};

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
    
    let lex : f_lexer::Lexer = f_lexer::init_lexer(&file_contents);
    
    println!("The lexer has value {} with {} characters", &lex.contents, lex.content_length);
    
}

mod f_lexer {
    pub struct Lexer {
        pub contents : String,
        pub content_length : usize,
        pub character : char,
        pub indexer : usize,
        pub line : usize,
        pub column : usize,
    }

    pub fn init_lexer(file_contents : &String) -> Lexer {
        let lex : Lexer = Lexer {
            contents : file_contents.clone(),
            content_length: file_contents.len(),
            character: ' ',
            indexer : 0,
            line: 0,
            column: 0,
        };
        
        lex
    }
    
}

mod f_token {
    use std::fmt;

    pub struct Token {
        pub token_type: TokenType,
        pub value: String,
        pub line: usize,
        pub column: usize,        
    }

    pub enum TokenType {
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
        TOKEN_VARIABLE,

        //ETC Tokens,
        TOKEN_LINE_COMMENT,
        TOKEN_MULTILINE_COMMENT,
        TOKEN_EOF,
        
    }

    impl fmt::Display for TokenType {
        fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
            match self {
                TokenType::TOKEN_ID => write!(f, "id"),
                TokenType::TOKEN_EQUALS => write!(f, "="),
                TokenType::TOKEN_SEMICOLON => write!(f, ";"),
                TokenType::TOKEN_LPARENTHESIS => write!(f, "("),
                TokenType::TOKEN_RPARENTHESIS => write!(f, ")"),
                TokenType::TOKEN_LBRACE => write!(f, "["),
                TokenType::TOKEN_RBRACE => write!(f, "]"),
                TokenType::TOKEN_COMMA => write!(f, ","),
                TokenType::TOKEN_NEWLINE => write!(f, "'\n'"),
                TokenType::TOKEN_PLUS => write!(f, "+"),
                TokenType::TOKEN_MINUS => write!(f, "-"),
                TokenType::TOKEN_DIVIDE => write!(f, "/"),
                TokenType::TOKEN_MULTIPLY => write!(f, "*"),
                TokenType::TOKEN_VARIABLE => write!(f, "VAR"),
                TokenType::TOKEN_LINE_COMMENT => write!(f, "#"),
                TokenType::TOKEN_MULTILINE_COMMENT => write!(f, "/*"),
                TokenType::TOKEN_EOF => write!(f, "EOF"),
            }
        }
    }
}

mod f_io {
    use std::fs;
    use std::error::Error;
    
    pub fn file_read(filename : &String ) -> Result<String, Box<dyn Error>> {
        let contents = fs::read_to_string(filename)?;
        
        Ok(contents)
    }
}