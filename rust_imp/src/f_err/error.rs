use crate::f_lexer::Lexer;

pub struct Error {}

impl Error {
    pub fn throw_lex(lex: &Lexer, reason: String) -> Error {
        println!(
            "Invalid token: {} at Ln {}, Col {} - {}",
            lex.character, lex.line, lex.column, reason
        );

        Error {}
    }
}
