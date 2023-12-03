use std::fs;


fn is_gear(c: char) -> bool {
    /*
    Checks if the given char is a symbol
     */
    return c == '*';
}

fn get_adjacent_indices(i: usize, j: usize, width: usize, height: usize) -> Vec<(usize, usize)> {
    /*
    Returns a list of indices that are adjacent to the given index
     */
    let mut indices = Vec::new();
    if i > 0 {
        indices.push((i - 1, j));
    }
    if i < height - 1 {
        indices.push((i + 1, j));
    }
    if j > 0 {
        indices.push((i, j - 1));
    }
    if j < width - 1 {
        indices.push((i, j + 1));
    }
    if i > 0 && j > 0 {
        indices.push((i - 1, j - 1));
    }
    if i > 0 && j < width - 1 {
        indices.push((i - 1, j + 1));
    }
    if i < height - 1 && j > 0 {
        indices.push((i + 1, j - 1));
    }
    if i < height - 1 && j < width - 1 {
        indices.push((i + 1, j + 1));
    }
    return indices;
}

fn transform_input_to_grid(input: &str) -> Vec<Vec<char>> {
    /*
    Transforms the input into a grid
     */
    let mut grid = Vec::new();
    for line in input.lines() {
        let mut row = Vec::new();
        for c in line.chars() {
            row.push(c);
        }
        grid.push(row);
    }
    return grid;
}

fn extract_number_from_index(input: &Vec<char>, column_index: usize) -> (usize, usize, usize) {
    /*
    Extracts the number from the grid at a given column index. 
    Returns last and first column index of the number.
     */
    let mut number = String::new();
    let mut start_index = column_index;
    let mut end_index = column_index;
    for c in input[..column_index].iter().rev() {
        if c.is_numeric() {
            start_index -= 1;
            number.push(*c);
        }
        if !c.is_numeric(){
            break;
        }
    }
    number = number.chars().rev().collect();
    for c in input[column_index..].iter() {
        if c.is_numeric() {
            end_index += 1;
            number.push(*c);
        }
        if !c.is_numeric(){
            break;
        }
    }
    return (number.parse::<usize>().unwrap(), start_index, end_index);
}

fn check_number_in_numbertuple(n: (usize, usize, usize), compare: &Vec<(usize, usize, usize)>) -> bool {
    /*
    Checks if a number is in a number tuple
     */
    for number in compare {
        if n.0 == number.0 && n.1 == number.1 && n.2 == number.2 {
            return true;
        }
    }
    return false;
}

// debugging.....
fn print_index_environment(grid: &Vec<Vec<char>>, i: usize, j: usize) {
    /*
    Prints the environment of an index
     */
    println!("ENVIRONMENT OF GEAR AT INDEX ({}, {})", i, j);
    print!("{}", grid[i-1][0..j].iter().collect::<String>());
    println!("{}", grid[i-1][j..].iter().collect::<String>());
    print!("{}", grid[i][0..j].iter().collect::<String>());
    println!("{}", grid[i][j..].iter().collect::<String>());
    print!("{}", grid[i+1][0..j].iter().collect::<String>());
    println!("{}", grid[i+1][j..].iter().collect::<String>());
    println!("==========================================");
}

fn main() {
    let filename = "src/input.txt";
    let contents = fs::read_to_string(filename)
        .expect("Should have been able to read the file");

    let mut sum = 0;
    
    let mut grid = transform_input_to_grid(&contents);
    let mut gear_indices: Vec<(usize, usize)> = Vec::new(); // indicies of all gears with adjecent numbers

    for j in 0.. grid.len() {
        let mut found_part = false;    // if the number is a part (adjecent to a symbol)
        let mut number_start = false;   // indices that the first digit of a number is found
        let mut found_number = 0;       // the number that is found

        let row = &grid[j];
        for i in 0..row.len() {
            if is_gear(row[i]) {
                let gear_index = (j,i);
                let adj = get_adjacent_indices(i, j, grid.len(), grid.len());
                let mut last_index:(usize, usize) = (100,100);
                for (m, n) in adj {
                    if grid[n][m].is_numeric() {
                        if last_index == (100,100){
                            last_index = (n,m);
                        }else{
                            gear_indices.push(gear_index);
                            break;
                        }
                    }
                }
            }
        }
    }
    
    for (m, n) in gear_indices {
        // print_index_environment(&grid, m, n);
        let mut prod = 1;
        let adj = get_adjacent_indices(m, n, grid.len(), grid.len());
        let mut last_numbers: Vec<(usize, usize, usize)> = Vec::new();
        for (i, j) in adj {
            if grid[i][j].is_numeric() {
                let number = extract_number_from_index(&grid[i], j);
                if !check_number_in_numbertuple(number, &last_numbers) {
                    println!("Found Number: {}", number.0);   
                    prod *= number.0;
                    last_numbers.push(number);
                }
                else{
                    println!("Number already found {} {} {}", number.0, number.1, number.2);
                }
            }
        }
        if last_numbers.len() > 1 {
            println!("Adding gear ratio {}", prod);
            sum += prod;
        }
    }

    print!("Result: {}\n", sum);
}