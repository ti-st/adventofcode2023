use std::fs;
use std::collections::HashMap;

const MIN_COLOURS: i32 = 0;

fn reset_buffer(buffer: &mut HashMap<&str, i32>) {
    buffer.insert("red", MIN_COLOURS);
    buffer.insert("green", MIN_COLOURS);
    buffer.insert("blue", MIN_COLOURS);
}

fn main() {
    let filename = "src/input.txt";
    let contents = fs::read_to_string(filename)
        .expect("Should have been able to read the file");

    let mut colour_appearances = HashMap::new();
    colour_appearances.insert("red", MIN_COLOURS);
    colour_appearances.insert("green", MIN_COLOURS);
    colour_appearances.insert("blue", MIN_COLOURS);

    let mut sum_powers = 0;
    for line in contents.lines() {
        let temp = (line.split(":").collect::<Vec<&str>>());
        // Game ID
        let mut power = 1;
        // Sets in the Game/line
        let sets = temp[1].split(";").collect::<Vec<&str>>();
        for element in sets{
            for draw in element.split(",").collect::<Vec<&str>>(){
                let number = draw.trim().split(" ").collect::<Vec<&str>>()[0].parse::<i32>().unwrap();
                let colour = draw.trim().split(" ").collect::<Vec<&str>>()[1];
                if number > colour_appearances[colour]{
                    colour_appearances.insert(colour,number);
                }
            }
        }
        for value in colour_appearances.values() {
            power *= value;
        }
        sum_powers += power;
        reset_buffer(&mut colour_appearances);
    }

    
    print!("Result: {}\n", sum_powers);
}
