
pub fn reverse_rotate(n: &Vec<u32>) -> bool {
    let mut res = 0;
    for item in n {
        res += item * item;
    }
    (res / 2) == 0
}

pub fn revrot(s: &str, c: usize) -> String {
    // Fist validation system
    if s.len() < c || c <= 0 { 
        return String::new();
    }

    let mut word: Vec<u32> = Vec::new(); 
    let mut secd: String = String::new();
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
    if s.split_at(c).1.len() >= c {
        secd = revrot(s.split_at(c).1, c);
    }
    let mut output = String::from(word.into_iter().map(|i| i.to_string()).collect::<String>());
    output.push_str(&secd);
    output
}

pub fn testing(s: &str, c: usize, exp: &str) -> () {
    assert_eq!(&revrot(s, c), exp)
}

#[test]
fn basics_revrot() {
    testing("1234", 0, "");
    testing("", 0, "");
    testing("1234", 5, "");
    let s = "733049910872815764";
    testing(s, 5, "330479108928157");
    let s = "73304991087281576455176044327690580265896";
    testing(s, 8, "1994033775182780067155464327690480265895");
}

fn main() {
    let result = revrot("733049910872815764", 5);
    println!("RESULT: {} -> 330479108928157", result);
    assert_eq!(result, "330479108928157");
}
