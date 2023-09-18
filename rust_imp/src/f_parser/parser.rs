use crate::f_lexer::{Lexer, Token, TokenType};

pub struct Parser {
    lexer: Lexer,
    cur_tok: Token,
    prev_tok: Token,
    //scope : Scope,
}

impl Parser {
    pub fn init(mut lexer: Lexer) -> Parser {
        let mut tok = lexer.next();

        Parser {
            lexer: lexer,
            cur_tok: tok.clone(),
            prev_tok: tok,
        }
    }

    pub fn eat(&mut self, token_type: TokenType) -> () {
        if matches!(&self.cur_tok.token_type, token_type) {
            self.prev_tok = self.cur_tok.clone();
            self.cur_tok = self.lexer.next();
        } else {
            println!(
                "Ln {}, Col {} - Unexpected Token {} with type {}",
                self.lexer.line, self.lexer.column, self.cur_tok.value, self.cur_tok.token_type
            )
        }
    }
}
