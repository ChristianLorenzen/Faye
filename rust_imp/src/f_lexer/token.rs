use std::fmt;

pub struct Token {
    pub token_type: TokenType,
    pub value: String,
    pub line: usize,
    pub column: usize,
}

impl Token {
    pub fn create(t_type: TokenType, val: &String, line_num: usize, col: usize) -> Token {
        Token {
            token_type: t_type,
            value: val.clone(),
            line: line_num,
            column: col,
        }
    }

    pub fn print(&mut self) -> () {
        println!(
            "Token id: {}\nToken Value: {}\nToken Ln {}, Col {}",
            self.token_type, self.value, self.line, self.column
        );
    }

    pub fn clone(&mut self) -> Token {
        Token {
            token_type: self.token_type,
            value: self.value.clone(),
            line: self.line,
            column: self.column,
        }
    }
}

#[derive(Clone, Copy)]
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
            TokenType::TOKEN_ID => write!(f, "Identifier ( id )"),
            TokenType::TOKEN_EQUALS => write!(f, "Equals ( = )"),
            TokenType::TOKEN_SEMICOLON => write!(f, "Semicolon ( ; )"),
            TokenType::TOKEN_LPARENTHESIS => write!(f, "LParenthesis ( ( )"),
            TokenType::TOKEN_RPARENTHESIS => write!(f, "RParenthesis ( ) )"),
            TokenType::TOKEN_LBRACE => write!(f, "LBrace ( {{ )"),
            TokenType::TOKEN_RBRACE => write!(f, "RBrace ( }} )"),
            TokenType::TOKEN_COMMA => write!(f, "Comma ( , )"),
            TokenType::TOKEN_NEWLINE => write!(f, "Newline ( '\n' )"),
            TokenType::TOKEN_PLUS => write!(f, "Plus ( + )"),
            TokenType::TOKEN_MINUS => write!(f, "Minus ( - )"),
            TokenType::TOKEN_DIVIDE => write!(f, "Deivide ( / )"),
            TokenType::TOKEN_MULTIPLY => write!(f, "Multiply ( * )"),
            TokenType::TOKEN_VARIABLE => write!(f, "Variabe"),
            TokenType::TOKEN_STRING => write!(f, "String"),
            TokenType::TOKEN_LINE_COMMENT => write!(f, "Line Comment ( # )"),
            TokenType::TOKEN_MULTILINE_COMMENT => write!(f, "Multiline Comment ( /* )"),
            TokenType::TOKEN_EOF => write!(f, "End of File ( EOF ) "),
        }
    }
}
