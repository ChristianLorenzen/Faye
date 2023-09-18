use crate::token::{Token, TokenType};

pub struct Lexer {
    pub contents : String,
    pub content_length : usize,
    pub character : char,
    pub indexer : usize,
    pub line : usize,
    pub column : usize,
}

impl Lexer {
        pub fn init(file_contents : &String) -> Lexer {
            Lexer {
                contents : file_contents.clone(),
                content_length: file_contents.len(),
                character: file_contents.chars().nth(0).unwrap(),
                indexer : 0,
                line: 0,
                column: 0,
            }
        }

        pub fn advance(&mut self) {
            if self.character != '\0' && self.indexer < self.content_length {
                self.indexer += 1;
                self.character = self.contents.chars().nth(self.indexer).unwrap_or_else(|| '\0');
            }
        }

        pub fn skip_whitespace(&mut self) {
            while self.character == ' ' || self.character == '\n' {
                if self.character == '\n' {
                    self.line += 1;
                    self.column = 0;
                }
                else {
                    self.column+= 1;
                }
                self.advance();
            }
        }

        pub fn next(&mut self) -> Token {
            while self.character != '\0' && self.indexer < self.content_length {
                if self.character == ' ' || self.character == '\n' {
                    self.skip_whitespace();
                }

                if self.character.is_digit(10) {
                    return self.collect_number();
                }

                if self.character.is_alphabetic() {
                    return self.collect_id();
                }

                if self.character == '"' {
                    return self.collect_string();
                }

                if self.character == '#' {
                    return self.collect_line_comment();
                }

                match self.character {
                    '=' => return Lexer::advance_with_token(self, Token::create(TokenType::TOKEN_EQUALS, &"=".to_string(), self.line, self.column)),
                    ';' => return Lexer::advance_with_token(self, Token::create(TokenType::TOKEN_SEMICOLON, &";".to_string(), self.line, self.column)),
                    '(' => return Lexer::advance_with_token(self, Token::create(TokenType::TOKEN_LPARENTHESIS, &"(".to_string(), self.line, self.column)),
                    ')' => return Lexer::advance_with_token(self, Token::create(TokenType::TOKEN_RPARENTHESIS, &")".to_string(), self.line, self.column)),
                    '{' => return Lexer::advance_with_token(self, Token::create(TokenType::TOKEN_LBRACE, &"{".to_string(), self.line, self.column)),
                    '}' => return Lexer::advance_with_token(self, Token::create(TokenType::TOKEN_RBRACE, &"}".to_string(), self.line, self.column)),
                    ',' => return Lexer::advance_with_token(self, Token::create(TokenType::TOKEN_COMMA, &",".to_string(), self.line, self.column)),
                    '+' => return Lexer::advance_with_token(self, Token::create(TokenType::TOKEN_PLUS, &"+".to_string(), self.line, self.column)),
                    '-' => return Lexer::advance_with_token(self, Token::create(TokenType::TOKEN_MINUS, &"-".to_string(), self.line, self.column)),
                    '/' => return Lexer::advance_with_token(self, Token::create(TokenType::TOKEN_DIVIDE, &"/".to_string(), self.line, self.column)),
                    '*' => return Lexer::advance_with_token(self, Token::create(TokenType::TOKEN_MULTIPLY, &"*".to_string(), self.line, self.column)),
                    _ => continue
                }
            }

        Token::create(TokenType::TOKEN_EOF, &'\0'.to_string(), self.line, self.column)
        }

        pub fn collect_string(&mut self) -> Token {
                self.advance();
                let mut string_value = "".to_string();
                while self.character != '"' {
                    string_value.push(self.character);
                    self.advance();
                }
            self.advance();
                Token::create(TokenType::TOKEN_STRING, &string_value,  self.line, self.column)
        }

        pub fn collect_number(&mut self) -> Token {
                let mut string_value = "".to_string();
                while self.character.is_digit(10) {
                    string_value.push(self.character);
                    self.advance();
                }
            return Token::create(TokenType::TOKEN_VARIABLE, &string_value, self.line, self.column)
        }

        pub fn collect_id(&mut self) -> Token {
                let mut string_value = "".to_string();
                while self.character.is_alphabetic() {
                    string_value.push(self.character);

                    self.advance();
                }
            return Token::create(TokenType::TOKEN_ID, &string_value, self.line, self.column)
        }

        pub fn collect_line_comment(&mut self) -> Token {
                let mut string_value = "".to_string();

                while self.character != '\n' && self.character != '\0' {
                    string_value.push(self.character);

                    self.advance();
                }

            return Token::create(TokenType::TOKEN_LINE_COMMENT, &string_value, self.line, self.column)
        }

        pub fn advance_with_token(&mut self, token : Token) -> Token {
                self.advance();

                token
        }

        pub fn character_as_string(&mut self) -> String {
                self.character.to_string()
        }

}
