mod chunk;
use self::chunk::*;

mod debug;
use self::debug::*;

mod vm;
use self::vm::*;

fn main() {
    let mut chunk: Chunk = Chunk::new();

    let constant = chunk.add_character('H');
    chunk.write(OpCodes::PushCharacter.into());
    chunk.write(constant);

    chunk.write(OpCodes::Print.into());

    let constant = chunk.add_character('e');
    chunk.write(OpCodes::PushCharacter.into());
    chunk.write(constant);

    chunk.write(OpCodes::Print.into());

    let constant = chunk.add_character('l');
    chunk.write(OpCodes::PushCharacter.into());
    chunk.write(constant);

    chunk.write(OpCodes::Print.into());

    let constant = chunk.add_character('l');
    chunk.write(OpCodes::PushCharacter.into());
    chunk.write(constant);

    chunk.write(OpCodes::Print.into());

    let constant = chunk.add_character('o');
    chunk.write(OpCodes::PushCharacter.into());
    chunk.write(constant);

    chunk.write(OpCodes::Print.into());

    let constant = chunk.add_character(' ');
    chunk.write(OpCodes::PushCharacter.into());
    chunk.write(constant);

    chunk.write(OpCodes::Print.into());

    let constant = chunk.add_character('W');
    chunk.write(OpCodes::PushCharacter.into());
    chunk.write(constant);

    chunk.write(OpCodes::Print.into());

    let constant = chunk.add_character('o');
    chunk.write(OpCodes::PushCharacter.into());
    chunk.write(constant);

    chunk.write(OpCodes::Print.into());

    let constant = chunk.add_character('r');
    chunk.write(OpCodes::PushCharacter.into());
    chunk.write(constant);

    chunk.write(OpCodes::Print.into());

    let constant = chunk.add_character('l');
    chunk.write(OpCodes::PushCharacter.into());
    chunk.write(constant);

    chunk.write(OpCodes::Print.into());

    let constant = chunk.add_character('d');
    chunk.write(OpCodes::PushCharacter.into());
    chunk.write(constant);

    chunk.write(OpCodes::Print.into());

    let constant = chunk.add_character('!');
    chunk.write(OpCodes::PushCharacter.into());
    chunk.write(constant);

    chunk.write(OpCodes::Print.into());

    chunk.write(OpCodes::Halt.into());

    disassemble_chunk(&chunk);
    println!("== interpreting ==");

    let mut vm = VM::new(false);
    let result = vm.interpret(chunk);
    println!("\n== result ==");
    println!("{:?}", result);
}
