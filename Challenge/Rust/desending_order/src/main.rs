use time::PreciseTime;

// Function that returns the exponentian from a base number and exponent
pub fn exponential(base: u32, exponent: u32) -> u64 {
    return {
        let mut res = 1;
        for _ in 0..exponent{
            res *= base;
        }
        res as u64
    };
}

// Function that takes a number and returns the max value from the numbers
pub fn descending_order(x: u64) -> u64 {
    let mut input_number = x;
    let mut result: u64 = 0;
    let mut vec_numbers: Vec<u8> = Vec::new();
    let start: PreciseTime = PreciseTime::now();
    while input_number > 0 {
        let var_at = (input_number%10) as u8; 
        input_number /= 10;
        vec_numbers.push(var_at);
    }
    vec_numbers.sort();
    for (index, item) in vec_numbers.iter().enumerate() {
        result += {
            let position: u64 = exponential(10, index as u32);
            let value = (item - 0) as u64;
            (if position == 0 { 1 } else { position } * value)
        };
    }
    let end: PreciseTime = PreciseTime::now();
    println!(" Execution time: {}", start.to(end));
    result
}

#[test]
fn returns_expected() {
    assert_eq!(descending_order(0), 0);
    assert_eq!(descending_order(1), 1);
    assert_eq!(descending_order(15), 51);
    assert_eq!(descending_order(1021), 2110);
    assert_eq!(descending_order(123456789), 987654321);
    assert_eq!(descending_order(145263), 654321);
    assert_eq!(descending_order(1254859723), 9875543221);
}

fn main() {
    descending_order(15);
}