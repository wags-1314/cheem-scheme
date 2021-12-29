use num_enum::IntoPrimitive;
use num_enum::TryFromPrimitive;

#[derive(Debug, Eq, PartialEq, TryFromPrimitive, IntoPrimitive)]
#[repr(u8)]
pub enum OpCodes {
    Print,
    PushInteger,
    PushFloat,
}

pub enum Value {
    Float(f64),
    Integer(i64),
}

pub struct Chunk {
    pub code: Vec<u8>,
    pub constants: Vec<Value>,
}

impl Chunk {
    pub fn new() -> Chunk {
        Chunk {
            code: Vec::new(),
            constants: Vec::new(),
        }
    }

    pub fn write(&mut self, byte: u8) {
        self.code.push(byte);
    }

    pub fn add_integer(&mut self, constant: i64) -> u8 {
        self.constants.push(Value::Integer(constant));
        ((self.constants.len() - 1) as u8).try_into().unwrap()
    }

    pub fn add_float(&mut self, constant: f64) -> u8 {
        self.constants.push(Value::Float(constant));
        ((self.constants.len() - 1) as u8).try_into().unwrap()
    }
}
