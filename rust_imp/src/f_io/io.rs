use std::error::Error;
use std::fs;

pub fn file_read(filename: &String) -> Result<String, Box<dyn Error>> {
    let contents = fs::read_to_string(filename)?;

    Ok(contents)
}
