use crate::chunk::*;

pub fn disassemble_chunk(chunk: &Chunk) {
    println!("== chunk ==");

    let mut i: usize = 0;
    while i < chunk.code.len() {
        i = disassemble_instruction(chunk, i);
    }
}

fn disassemble_instruction(chunk: &Chunk, index: usize) -> usize {
    print!("{:0>4} ", index);
    let instruction: u8 = chunk.code[index];
    match OpCodes::try_from(instruction) {
        Ok(OpCodes::Halt) => simple_instruction("Halt", index),
        Ok(OpCodes::PushInteger) => constant_instruction("Integer", chunk, index),
        Ok(OpCodes::PushFloat) => constant_instruction("Float", chunk, index),
        Ok(OpCodes::PushCharacter) => constant_instruction("Character", chunk, index),
        Ok(OpCodes::Nope) => simple_instruction("Nope", index),
        Ok(OpCodes::Add) => simple_instruction("Add", index),
        Ok(OpCodes::Subtract) => simple_instruction("Subtract", index),
        Ok(OpCodes::Multiply) => simple_instruction("Multiply", index),
        Ok(OpCodes::Out) => simple_instruction("Out", index),
        Ok(OpCodes::Pop) => simple_instruction("Pop", index),
        Ok(OpCodes::Print) => simple_instruction("Print", index),
        Err(_) => {
            println!("Unknown OpCode");
            index + 1
        }
    }
}

fn simple_instruction(name: &str, index: usize) -> usize {
    println!("{}", name);
    index + 1
}

fn constant_instruction(name: &str, chunk: &Chunk, index: usize) -> usize {
    let constant = chunk.code[index + 1];
    print!("{0:<16} {1:0>4} ", name, constant);
    match chunk.constants[constant as usize] {
        Value::Integer(val) => print!("{}", val),
        Value::Float(val) => print!("{:.e}", val),
        Value::Character(val) => print!("'{}'", val),
    };
    print!("\n");
    index + 2
}
