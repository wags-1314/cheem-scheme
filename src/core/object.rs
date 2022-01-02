use crate::util;
use std::fmt;

#[derive(Debug)]
pub enum Object {
    Integer(i64),
    Boolean(bool),
    Character(char),
    String(String),
    Symbol(String),
    Cons { car: Box<Object>, cdr: Box<Object> },
    Nil,
}

pub type ObjectBox = Box<Object>;

pub mod constants {
    use super::Object;
    pub const TRUE: Object = Object::Boolean(true);
    pub const FALSE: Object = Object::Boolean(false);
    pub const NIL: Object = Object::Nil;
}

impl Object {
    fn pair_to_string(&self, other: &Self) -> String {
        let mut result = self.string_repr();
        match other {
            Object::Cons { car, cdr } => {
                result.push(' ');
                result.push_str(&car.pair_to_string(&cdr));
            }
            Object::Nil => result.push_str(""),
            _ => {
                result.push_str(" . ");
                result.push_str(&other.string_repr());
            }
        };

        result
    }

    fn string_repr(&self) -> String {
        match &*self {
            Object::Integer(i) => i.to_string(),
            Object::Boolean(i) => {
                if *i {
                    "#t".to_string()
                } else {
                    "#f".to_string()
                }
            }
            Object::Character(i) => match i {
                '\n' => "$\\n".to_string(),
                '\t' => "$\\t".to_string(),
                '\r' => "$\\r".to_string(),
                '\0' => "$\\0".to_string(),
                '\\' => "$\\\\".to_string(),
                ' ' => "$space".to_string(),
                _ => format!("${}", i),
            },
            Object::String(i) => format!("\"{}\"", util::raw_string(i)),
            Object::Symbol(i) => i.to_string(),
            cons @ Object::Cons { car: _, cdr: _ } => format!("({})", cons.pair_to_string()),
            Object::Nil => "()".to_string(),
        }
    }
}

impl fmt::Display for Object {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}", self.string_repr())
    }
}
