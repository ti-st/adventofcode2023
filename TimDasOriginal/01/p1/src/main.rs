use std::fs;

fn main() {
    let digits = "0123456789";
    let filename = "src/input.txt";
    let contents = fs::read_to_string(filename)
        .expect("Should have been able to read the file");

    let mut found_digits = 0;
    let mut number_digits = (0, 'a', 'a');

    for line in contents.lines() {
        found_digits = 0;
        for c in line.chars() {
            if digits.contains(c) {
                found_digits += 1;
                if found_digits == 1 {
                    number_digits.1 = c;
                } else {
                    number_digits.2 = c;
                }
            }
        }
        if number_digits.2 != 'a' {
            let number_str = format!("{}{}", number_digits.1, number_digits.2);
            let number: i32 = number_str.parse().unwrap();
    
            number_digits.0 += number;
            number_digits.1 = 'a';
            number_digits.2 = 'a';
        } else {
            let number_str = format!("{}{}", number_digits.1, number_digits.1);
            let number: i32 = number_str.parse().unwrap();
    
            number_digits.0 += number;
            number_digits.1 = 'a';
        }
    }

    
    print!("The sum of the numbers is: {}\n", number_digits.0)
}
