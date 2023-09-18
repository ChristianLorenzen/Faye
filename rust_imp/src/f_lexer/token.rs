use std::fmt;

pub struct Token {
    pub token_type: TokenType,
    pub value: String,
    pub line: usize,
    pub column: usize,
}


impl Token {
        pub fn create(t_type: TokenType, val : &String, line_num : usize, col : usize) -> Token {
            Token {
                token_type: t_type,
                value: val.clone(),
                line: line_num,
                column: col,
            }
        }

        pub fn print(&mut self) -> () {
            println!("Token id: {}\nToken Value: {}\nToken line/column: {}:{}",
                self.token_type, self.value, self.line, self.column);
        }
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
    TOKEN_STRING,

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
            TokenType::TOKEN_LBRACE => write!(f, "{{"),
            TokenType::TOKEN_RBRACE => write!(f, "}}"),
            TokenType::TOKEN_COMMA => write!(f, ","),
            TokenType::TOKEN_NEWLINE => write!(f, "'\n'"),
            TokenType::TOKEN_PLUS => write!(f, "+"),
            TokenType::TOKEN_MINUS => write!(f, "-"),
            TokenType::TOKEN_DIVIDE => write!(f, "/"),
            TokenType::TOKEN_MULTIPLY => write!(f, "*"),
            TokenType::TOKEN_VARIABLE => write!(f, "VAR"),
            TokenType::TOKEN_STRING => write!(f, "STRING"),
            TokenType::TOKEN_LINE_COMMENT => write!(f, "#"),
            TokenType::TOKEN_MULTILINE_COMMENT => write!(f, "/*"),
            TokenType::TOKEN_EOF => write!(f, "EOF"),
        }
    }
}
