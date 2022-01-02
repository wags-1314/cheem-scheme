#![allow(dead_code)]
mod core;
mod util;

use self::core::parser::*;

fn main() {
    let mut scanner = Parser::new("\"Hello \\nWorld\"");
    match scanner.parse() {
        Ok(object) => println!("{}", object),
        Err(message) => println!("{}", message),
    }
}
