use std::fs;
use std::error::Error;

pub fn file_read(filename : &String ) -> Result<String, Box<dyn Error>> {
    let contents = fs::read_to_string(filename)?;

    Ok(contents)
}