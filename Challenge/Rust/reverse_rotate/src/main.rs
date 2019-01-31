
pub fn reverse_rotate(n: &Vec<u32>) -> bool {
    let mut res = 0;
    for item in n {
        res += item * item;
    }
    (res & 2) == 0 
}

pub fn revrot(s: &str, c: usize) -> String {
    // Fist validation system
    if s.len() < c || c <= 0 { 
        return String::new();
    }

    let mut word: Vec<u32> = Vec::new(); 
    s.split_at(c).0.chars().for_each( |ch: char| { 
        word.push({ 
            let a: Option<u32> = ch.to_digit(10);
            match a {
                Some(x) => x,
                None    => panic!("Error"),
            }
        }); 
    });
    if reverse_rotate(&word) {
        word.reverse();
    } else {
        word.rotate_left(1);
    }
    let secd = revrot(s.split_at(c).1, c);
    let mut output = String::from(word.into_iter().map(|i| i.to_string()).collect::<String>());
    output.push_str(&secd);
    output
}

#[test]
fn basics_revrot() {
   assert_eq!(revrot("123456987654", 6), "234561876549");
   assert_eq!(revrot("123456987653", 6), "234561356789");
   assert_eq!(revrot("66443875", 4), "44668753");
   assert_eq!(revrot("66443875", 8), "64438756");
   assert_eq!(revrot("664438769", 6), "44666783");
   assert_eq!(revrot("123456779", 6), "23456771");
   assert_eq!(revrot("", 8), "");
   assert_eq!(revrot("123456779", 0), "");
}

fn main() {
    let result = revrot("733049910872815764", 5);
    println!("RESULT: {} -> 330479108928157", result);
    assert_eq!(result, "330479108928157");
}
