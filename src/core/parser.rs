use super::object::*;

pub struct Parser<'a> {
    source: &'a str,
    start: usize,
    current: usize,
}

impl<'a> Parser<'a> {
    pub fn new(source: &'a str) -> Self {
        Parser {
            source,
            start: 0,
            current: 0,
        }
    }

    pub fn set_source(&mut self, new_source: &'a str) {
        self.source = new_source;
    }

    fn is_at_end(&self) -> bool {
        self.current - 1 == self.source.chars().count()
    }

    fn advance(&mut self) -> Option<char> {
        self.current += 1;
        self.source.chars().nth(self.current - 1)
    }

    fn peek(&self) -> Option<char> {
        self.source.chars().nth(self.current)
    }

    fn is_delimiter(&self, ch: char) -> bool {
        ch.is_ascii_whitespace() || matches!(ch, '(' | ')' | ';' | '"' | '\'') || self.is_at_end()
    }

    fn peek_delimiter(&self) -> bool {
        if let Some(ch) = self.peek() {
            self.is_delimiter(ch)
        } else {
            true
        }
    }

    fn is_symbol_initial(&self, ch: char) -> bool {
        !matches!(ch, '(' | ')' | ';' | '$' | '#' | '"' | '-' | '\'') && !ch.is_ascii_digit()
    }

    fn is_symbol_character(&self, ch: char) -> bool {
        !matches!(ch, '(' | ')' | ';' | '\'') || ch.is_ascii_whitespace()
    }

    fn skip_whitespace(&mut self) {
        while let Some(ch) = self.peek() {
            if ch.is_whitespace() {
                self.advance();
                continue;
            } else if ch == ';' {
                while let Some(ch) = self.advance() {
                    if ch == '\n' {
                        break;
                    }
                }
                continue;
            }

            break;
        }
    }

    fn peek_number(&self, ch: char) -> bool {
        ch.is_ascii_digit() || (ch == '-' && self.peek().unwrap().is_ascii_digit())
    }

    fn parse_number(&mut self) -> Result<ObjectBox, String> {
        while let Some(ch) = self.peek() {
            if ch.is_ascii_digit() {
                self.advance();
            } else {
                break;
            }
        }

        Ok(ObjectBox::new(Object::Integer(
            self.source
                .chars()
                .skip(self.start)
                .take(self.current - self.start)
                .collect::<String>()
                .parse::<i64>()
                .unwrap(),
        )))
    }

    fn parse_boolean(&mut self) -> Result<ObjectBox, String> {
        if let Some(ch) = self.advance() {
            match ch {
                't' => Ok(ObjectBox::new(constants::TRUE)),
                'f' => Ok(ObjectBox::new(constants::FALSE)),
                _ => Err(String::from("")),
            }
        } else {
            Err(String::from(""))
        }
    }

    fn parse_character(&mut self) -> Result<ObjectBox, String> {
        // TODO: Add $\x80 and $\d97 style characters
        if let Some(ch) = self.advance() {
            if ch == '\\' {
                if let Some(ch) = self.advance() {
                    if !self.peek_delimiter() {
                        return Err(String::from(""));
                    }
                    match ch {
                        'n' => Ok(ObjectBox::new(Object::Character('\n'))),
                        'r' => Ok(ObjectBox::new(Object::Character('\r'))),
                        't' => Ok(ObjectBox::new(Object::Character('\t'))),
                        '\\' => Ok(ObjectBox::new(Object::Character('\\'))),
                        '0' => Ok(ObjectBox::new(Object::Character('\0'))),
                        ' ' => Ok(ObjectBox::new(Object::Character(' '))),
                        _ => Err(String::from("")),
                    }
                } else {
                    Err(String::from(""))
                }
            } else if !self.peek_delimiter() {
                Err(String::from(""))
            } else {
                Ok(ObjectBox::new(Object::Character(ch)))
            }
        } else {
            Err(String::from(""))
        }
    }

    fn parse_string(&mut self) -> Result<ObjectBox, String> {
        let mut result = String::new();

        while let Some(ch) = self.advance() {
            if self.is_at_end() {
                return Err(String::from("at end"));
            }

            if ch == '"' {
                return Ok(ObjectBox::new(Object::String(result)));
            }

            if ch == '\\' {
                if let Some(ch) = self.advance() {
                    match ch {
                        'n' => result.push('\n'),
                        'r' => result.push('\r'),
                        't' => result.push('\t'),
                        '\\' => result.push('\\'),
                        '0' => result.push('\0'),
                        _ => result.push(ch),
                    }

                    continue;
                } else {
                    return Err(String::from("empty escape sequence"));
                }
            }

            result.push(ch);
        }

        Err(String::from("no ending quote"))
    }

    fn parse_pair(&mut self) -> Result<ObjectBox, String> {
        let car: ObjectBox;
        let cdr: ObjectBox;
        self.skip_whitespace();
        if let Some(ch) = self.peek() {
            if ch == ')' {
                self.advance();
                return Ok(ObjectBox::new(constants::NIL));
            }

            match self.parse() {
                Ok(object_box) => car = object_box,
                a @ Err(_) => return a,
            }

            self.skip_whitespace();

            if let Some(ch) = self.peek() {
                if ch == '.' {
                    self.advance();

                    if !self.peek_delimiter() {
                        return Err(String::from(""));
                    }

                    match self.parse() {
                        Ok(object_box) => cdr = object_box,
                        a @ Err(_) => return a,
                    }

                    self.skip_whitespace();

                    if let Some(ch) = self.advance() {
                        if ch == ')' {
                            return Ok(ObjectBox::new(Object::Cons { car, cdr }));
                        } else {
                            return Err(String::from(""));
                        }
                    } else {
                        return Err(String::from(""));
                    }
                } else {
                    match self.parse_pair() {
                        Ok(object_box) => cdr = object_box,
                        a @ Err(_) => return a,
                    }

                    return Ok(ObjectBox::new(Object::Cons { car, cdr }));
                }
            }
        }
        Err(String::from("here"))
    }

    fn parse_symbol(&mut self) -> Result<ObjectBox, String> {
        while let Some(ch) = self.peek() {
            if self.is_symbol_character(ch) {
                self.advance();
            } else {
                break;
            }
        }

        return Ok(ObjectBox::new(Object::Symbol(
            self.source
                .chars()
                .skip(self.start)
                .take(self.current - self.start)
                .collect::<String>(),
        )));
    }

    pub fn parse(&mut self) -> Result<ObjectBox, String> {
        self.skip_whitespace();
        self.start = self.current;

        let ch = self.advance().unwrap();

        match ch {
            ch if self.peek_number(ch) => self.parse_number(),
            '#' => self.parse_boolean(),
            '$' => self.parse_character(),
            '"' => self.parse_string(),
            '(' => self.parse_pair(),
            ch if self.is_symbol_initial(ch) => self.parse_symbol(),
            _ => Err(String::from("Unknown Character")),
        }
    }
}
