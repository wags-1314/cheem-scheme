use crate::chunk::*;

#[derive(Debug)]
pub enum InterpretResult {
    Ok,
    CompileError,
    RuntimeError,
}

pub struct VM {
    chunk: Chunk,
    stack: Vec<Value>,
    pc: usize,
    debug: bool,
}

impl VM {
    pub fn new(debug: bool) -> VM {
        VM {
            chunk: Chunk::new(),
            stack: Vec::new(),
            pc: 0usize,
            debug: debug,
        }
    }

    pub fn interpret(&mut self, chunk: Chunk) -> InterpretResult {
        self.chunk = chunk;
        self.pc = 0;
        self.run()
    }

    fn run(&mut self) -> InterpretResult {
        loop {
            let instruction = self.chunk.code[self.pc];
            self.pc += 1;
            match OpCodes::try_from(instruction) {
                Ok(OpCodes::Halt) => {
                    break InterpretResult::Ok;
                }
                Ok(OpCodes::PushInteger) => {
                    let value_index = self.chunk.code[self.pc];
                    self.pc += 1;
                    let value = self.chunk.constants[value_index as usize];
                    match value {
                        Value::Integer(_) => self.stack.push(value),
                        _ => break InterpretResult::RuntimeError,
                    };
                }
                Ok(OpCodes::PushFloat) => {
                    let value_index = self.chunk.code[self.pc];
                    self.pc += 1;
                    let value = self.chunk.constants[value_index as usize];
                    match value {
                        Value::Float(_) => self.stack.push(value),
                        _ => break InterpretResult::RuntimeError,
                    };
                }
                Ok(OpCodes::PushCharacter) => {
                    let value_index = self.chunk.code[self.pc];
                    self.pc += 1;
                    let value = self.chunk.constants[value_index as usize];
                    match value {
                        Value::Character(_) => self.stack.push(value),
                        _ => break InterpretResult::RuntimeError,
                    };
                }
                Ok(OpCodes::Add) => {
                    let operand_1: Value;
                    let operand_2: Value;

                    if let Some(i) = self.stack.pop() {
                        operand_2 = i;
                    } else {
                        break InterpretResult::RuntimeError;
                    }

                    if let Some(i) = self.stack.pop() {
                        operand_1 = i;
                    } else {
                        break InterpretResult::RuntimeError;
                    }

                    match (operand_1, operand_2) {
                        (Value::Integer(i), Value::Integer(j)) => {
                            self.stack.push(Value::Integer(i + j))
                        }
                        (Value::Integer(i), Value::Float(j)) => {
                            self.stack.push(Value::Float((i as f64) + j))
                        }
                        (Value::Float(i), Value::Integer(j)) => {
                            self.stack.push(Value::Float((j as f64) + i))
                        }
                        (Value::Float(i), Value::Float(j)) => self.stack.push(Value::Float(i + j)),
                        (_, _) => break InterpretResult::CompileError,
                    };
                }
                Ok(OpCodes::Subtract) => {
                    let operand_1: Value;
                    let operand_2: Value;

                    if let Some(i) = self.stack.pop() {
                        operand_2 = i;
                    } else {
                        break InterpretResult::RuntimeError;
                    }

                    if let Some(i) = self.stack.pop() {
                        operand_1 = i;
                    } else {
                        break InterpretResult::RuntimeError;
                    }

                    match (operand_1, operand_2) {
                        (Value::Integer(i), Value::Integer(j)) => {
                            self.stack.push(Value::Integer(i - j))
                        }
                        (Value::Integer(i), Value::Float(j)) => {
                            self.stack.push(Value::Float((i as f64) - j))
                        }
                        (Value::Float(i), Value::Integer(j)) => {
                            self.stack.push(Value::Float(i - (j as f64)))
                        }
                        (Value::Float(i), Value::Float(j)) => self.stack.push(Value::Float(i - j)),
                        (_, _) => break InterpretResult::CompileError,
                    };
                }
                Ok(OpCodes::Multiply) => {
                    let operand_1: Value;
                    let operand_2: Value;

                    if let Some(i) = self.stack.pop() {
                        operand_2 = i;
                    } else {
                        break InterpretResult::RuntimeError;
                    }

                    if let Some(i) = self.stack.pop() {
                        operand_1 = i;
                    } else {
                        break InterpretResult::RuntimeError;
                    }

                    match (operand_1, operand_2) {
                        (Value::Integer(i), Value::Integer(j)) => {
                            self.stack.push(Value::Integer(i * j))
                        }
                        (Value::Integer(i), Value::Float(j)) => {
                            self.stack.push(Value::Float((i as f64) * j))
                        }
                        (Value::Float(i), Value::Integer(j)) => {
                            self.stack.push(Value::Float(i * (j as f64)))
                        }
                        (Value::Float(i), Value::Float(j)) => self.stack.push(Value::Float(i * j)),
                        (_, _) => break InterpretResult::CompileError,
                    };
                }
                Ok(OpCodes::Out) => {
                    if let Some(i) = self.stack.pop() {
                        print!("{}", i);
                    }
                }
                Ok(OpCodes::Pop) => {
                    if let None = self.stack.pop() {
                        break InterpretResult::RuntimeError;
                    }
                }
                Ok(OpCodes::Nope) => (),
                Ok(OpCodes::Print) => {
                    if let Some(i) = self.stack.pop() {
                        match i {
                            Value::Character(j) => print!("{}", j),
                            _ => break InterpretResult::RuntimeError,
                        }
                    } else {
                        break InterpretResult::RuntimeError;
                    }
                }
                Err(_) => {
                    break InterpretResult::CompileError;
                }
            }

            if self.debug {
                println!("VM Stack: {:?}", self.stack);
            }
        }
    }
}
