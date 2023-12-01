use std::fs;
use std::collections::HashMap;

fn main() {
    let digits = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"];
    let map: HashMap<&str, i32> = HashMap::from(
        [
            ("one", 1),
            ("two", 2),
            ("three", 3),
            ("four", 4),
            ("five", 5),
            ("six", 6),
            ("seven", 7),
            ("eight", 8),
            ("nine", 9),
            ("zero", 0),
            ("0", 0),
            ("1", 1),
            ("2", 2),
            ("3", 3),
            ("4", 4),
            ("5", 5),
            ("6", 6),
            ("7", 7),
            ("8", 8),
            ("9", 9),
        ]
    );
    let filename = "src/input.txt";
    let contents = fs::read_to_string(filename)
        .expect("Should have been able to read the file");

    let mut found_digits = 0;
    let mut number_digits = (0, "", "");
    let mut index_digit = (1000, 0);
    for line in contents.lines() {
        found_digits = 0;
        index_digit = (1000, 0);
        for entry in &digits {
            let indices: Vec<usize> = line.match_indices(entry)
                .map(|(i, _)| i)
                .collect();

            for found_digit_index in indices {
                if found_digit_index < index_digit.0 {
                    index_digit.0 = found_digit_index;
                    number_digits.1 = entry;
                    found_digits += 1;
                }
                if found_digit_index > index_digit.1 {
                    index_digit.1 = found_digit_index;
                    number_digits.2 = entry;
                    found_digits += 1;
                }
            }
        }

        if found_digits == 1 {
            let number_str = format!("{}{}", map[number_digits.1], map[number_digits.1]);
            let number = number_str.parse::<i32>().unwrap();

            number_digits.0 += number;
            number_digits.1 = "";
            number_digits.2 = "";
        } else {
            let number_str = format!("{}{}", map[number_digits.1], map[number_digits.2]);
            let number = number_str.parse::<i32>().unwrap();

            number_digits.0 += number;
            number_digits.1 = "";
        }
    }

    print!("The sum of the numbers is: {}\n", number_digits.0)
}
