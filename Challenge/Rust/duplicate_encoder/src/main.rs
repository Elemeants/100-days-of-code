/**
 * The goal of this exercise is to convert a string to a new string 
 * where each character in the new string is '(' if that character 
 * appears only once in the original string, or ')' if that character
 * appears more than once in the original string. Ignore capitalization
 *  when determining if a character is a duplicate.
 */
pub fn duplicate_encoder(data: &str) -> String {
    let mut output: String = String::new();
    let funcion = |ch| { data.chars().filter(|x: &char| { ch == *x }).count() > 1 };
    for (_, ch) in data.to_lowercase().chars().enumerate() {
        output += if funcion(ch) { ")" } else { "(" };
    }
    output
}

#[test]
fn run_tests() {
  assert_eq!(duplicate_encoder("din"),"(((");
  assert_eq!(duplicate_encoder("recede"),"()()()");
  assert_eq!(duplicate_encoder("Success"),")())())");
  assert_eq!(duplicate_encoder("(( @"),"))((");
}

fn main() {
    duplicate_encoder("TestingAlgoritmWithLargeString");
}
