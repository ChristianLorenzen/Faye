pub enum AST_Type {
    AST_VARIABLE_DEFINITION,
    AST_FUNCTION_DEFINITION,
    AST_VARIABLE,
    AST_FUNCTION_CALL,
    AST_STRING,
    AST_INT,
    AST_FLOAT,
    AST_BOOL,

    AST_COMPOUND,
    AST_LINE_COMMENT,
    AST_NOOP,
}

pub enum Variable_Type {
    VAR_STRING,
    VAR_INT,
    VAR_FLOAT,
    VAR_BOOL,
}

//I don't see how this structure will work in Rust. I'll actually have to start thinking for myself here.
pub struct AST {
    _type: AST_Type,

    line: usize,

    variable_definition_name: String,
    variable_definition_value: Box<AST>,

    function_definition_name: String,
    function_definition_body: Box<AST>,
    function_definition_args: Vec<AST>,
    function_definition_args_size: usize,

    variable_name: String,

    function_call_name: String,
    function_call_args: Vec<AST>,
    function_call_args_size: usize,

    compound_ast: Vec<AST>,
    compound_size: usize,
}
