// Import necessary libraries
use std::fs;
use std::collections::HashMap;

fn main() {
    // Define an array of digit strings
    let digits = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"];

    // Create a HashMap to map digit strings to their corresponding integers
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

    // Specify the filename to read from
    let filename = "src/input.txt";

    // Read the contents of the file into a string
    let contents = fs::read_to_string(filename)
        .expect("Should have been able to read the file");

    // Initialize variables
    let mut found_digits = 0;
    let mut number_digits = (0, "", "");
    let mut index_digit = (1000, 0);

    // Iterate over each line in the file
    for line in contents.lines() {
        // Reset variables for each line
        found_digits = 0;
        index_digit = (1000, 0);

        // Iterate over each digit in the array
        for entry in &digits {
            // Find all occurrences of the digit in the line and get their indices
            let indices: Vec<usize> = line.match_indices(entry)
                .map(|(i, _)| i)
                .collect();

            // Iterate over each found digit index
            for found_digit_index in indices {
                // Update the minimum and maximum indices of the found digits
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

        // Check the number of found digits
        if found_digits == 1 {
            // If only one digit is found, concatenate it twice to form a number string
            let number_str = format!("{}{}", map[number_digits.1], map[number_digits.1]);
            let number = number_str.parse::<i32>().unwrap();

            // Add the number to the sum
            number_digits.0 += number;
            number_digits.1 = "";
            number_digits.2 = "";
        } else {
            // If two digits are found, concatenate them to form a number string
            let number_str = format!("{}{}", map[number_digits.1], map[number_digits.2]);
            let number = number_str.parse::<i32>().unwrap();

            // Add the number to the sum
            number_digits.0 += number;
            number_digits.1 = "";
        }
    }

    // Print the sum of the numbers
    print!("The sum of the numbers is: {}\n", number_digits.0)
}
