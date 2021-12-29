mod chunk;
use self::chunk::*;

mod debug;
use self::debug::*;

fn main() {
    let mut chunk: Chunk = Chunk::new();
    chunk.write(OpCodes::Print.into());

    let constant = chunk.add_integer(69i64);
    chunk.write(OpCodes::PushInteger.into());
    chunk.write(constant);

    let constant = chunk.add_float(69f64);
    chunk.write(OpCodes::PushFloat.into());
    chunk.write(constant);
    disassemble_chunk(&chunk);
}
