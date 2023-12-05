use std::fs;

fn main() {
    println!("Hello, Puzzle 01.1!");
    // let filepath = "/mnt/e/codeProjects/adventofcode2023/LeonFassbier/days/leon-01/testInput2.txt";
    let filepath = "/mnt/e/codeProjects/adventofcode2023/LeonFassbier/days/leon-01/input.txt";

    let num_strings = vec![
        "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
    ];

    let mut result = Vec::new();

    for line in fs::read_to_string(filepath).unwrap().lines() {
        result.push(line.to_string())
    }

    let mut line_numbers: Vec<i32> = Vec::new();

    for line in result {
        let mut num_1 = -1;
        let mut num_1_index = line_numbers.len();
        let mut num_2 = -1;
        let mut num_2_index = 0;

        let mut i = 0;
        for char in line.chars() {
            let parsed = char.to_string().parse::<i32>();
            if parsed.is_ok() {
                if num_1 == -1 {
                    num_1 = parsed.unwrap();
                    num_1_index = i;
                } else {
                    num_2 = parsed.unwrap();
                    num_2_index = i;
                }
            }
            i += 1;
        }

        // if num_1 == -1{
        //     panic!("No number found");
        // }

        if num_2 == -1 {
            num_2 = num_1;
            num_2_index = num_1_index;
        }
        
        let mut cur_num = 0;
        for num_string in num_strings.iter() {
            cur_num += 1;
            let num_string_len = num_string.as_bytes().len();

            let find_index1 = line.find(num_string);
            if find_index1.is_none() {
                continue;
            }
            if find_index1.unwrap() < num_1_index {
                num_1_index = find_index1.unwrap();
                num_1 = cur_num;
            }

            let mut find_index2 = find_index1.unwrap();
            let mut find_index_temp = find_index1;
            while find_index_temp.is_some(){                
                let rest_slice = &line[find_index2 + num_string_len..];
                find_index_temp = rest_slice.find(num_string);
                if find_index_temp.is_some(){
                    find_index2 += num_string_len + find_index_temp.unwrap();
                }
            }

            if find_index2 > num_2_index{
                num_2_index = find_index2;
                num_2 = cur_num;
            }
        }

        let line_result = num_1 * 10 + num_2;
        line_numbers.push(line_result);
    }

    let num_lines = line_numbers.len();
    println!("Parsed {num_lines} lines.");

    let total = line_numbers.iter().fold(0, |sum, val| sum + val);
    println!("The total is {total}");
}
