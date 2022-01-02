pub fn raw_string(string: &str) -> String {
    let mut result = String::from("");

    for ch in string.chars() {
        match ch {
            '\n' => result.push_str("\\n"),
            '\t' => result.push_str("\\t"),
            '\r' => result.push_str("\\r"),
            '\\' => result.push_str("\\\\"),
            '\0' => result.push_str("\\0"),
            _ => result.push(ch),
        }
    }
    result
}
