use std::fs;
use std::collections::HashMap;

fn main() {
    let filename = "src/input.txt";
    let contents = fs::read_to_string(filename)
        .expect("Should have been able to read the file");


    let mut map: HashMap<String, i32> = HashMap::new();
    map.insert(String::from("red"), 12);
    map.insert(String::from("green"), 13);
    map.insert(String::from("blue"), 14);

    let mut sum_possiblegames = 0;
    let mut is_possible = true;
    for line in contents.lines() {
        let temp = (line.split(":").collect::<Vec<&str>>());
        // Game ID
        let id = temp[0].split(" ").collect::<Vec<&str>>()[1].parse::<i32>().unwrap();
        // Sets in the Game/line
        let sets = temp[1].split(";").collect::<Vec<&str>>();
        for element in sets{
            if is_possible{
                for draw in element.split(",").collect::<Vec<&str>>(){
                    let number = draw.trim().split(" ").collect::<Vec<&str>>()[0].parse::<i32>().unwrap();
                    let colour = draw.trim().split(" ").collect::<Vec<&str>>()[1];
                    if number > map[colour] {
                        is_possible = false;
                        println!("Game {} is not possible", id);
                    }
                }
            }
        }
        if is_possible {
            sum_possiblegames += id;
        }
        is_possible = true;
    }

    
    print!("Result: {}\n", sum_possiblegames);
}
