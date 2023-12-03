use std::fs;


fn is_symbol(c: char) -> bool {
    /*
    Checks if the given char is a symbol
     */
    return !c.is_numeric() && c != '.';
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

fn extract_number(input: &Vec<char>, row_index: usize) -> usize {
    /*
    Extracts the number from the grid at a given row index
     */
    let mut number = String::new();
    for c in input[row_index..].iter() {
        if c.is_numeric() {
            number.push(*c);
        }
        if !c.is_numeric(){
            return number.parse::<usize>().unwrap();
        }
    }
    return number.parse::<usize>().unwrap();
}

fn main() {
    let filename = "src/input.txt";
    let contents = fs::read_to_string(filename)
        .expect("Should have been able to read the file");

    let mut sum = 0;
    
    let mut grid = transform_input_to_grid(&contents);


    for j in 0.. grid.len() {
        let mut found_part = false;    // if the number is a part (adjecent to a symbol)
        let mut number_start = false;   // indices that the first digit of a number is found
        let mut found_number = 0;       // the number that is found

        let row = &grid[j];
        for i in 0..row.len() {
            if row[i].is_numeric(){
                if !number_start {  // only extract the number if it is the first digit (please AOC do not let numbers extend over two lines....)
                    number_start = true;
                    found_number = extract_number(&row, i);
                }
                // those are the adjecent indices
                let adj = get_adjacent_indices(i, j, grid.len(), grid.len());
                // check if any of the adjecent is a symbol (not '.' or a number)
                for (i, j) in adj {
                    // only add the number once
                    if is_symbol(grid[j][i]) && !found_part{
                        found_part = true;
                        println!("Found number: {}", found_number);
                        sum += found_number;
                    }
                }
            // if char is not a number reset all buffers
            } else{
                number_start = false;
                found_part = false;
                found_number = 0;
            }
        }
    }
    
    print!("Result: {}\n", sum);
}
