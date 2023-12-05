use regex::Regex;
use std::fs;

struct CubeSet {
    red: i32,
    green: i32,
    blue: i32,
}

fn main() {
    // let filepath = "/mnt/e/codeProjects/adventofcode2023/LeonFassbier/days/leon-02/testInput.txt";
    let filepath = "/mnt/e/codeProjects/adventofcode2023/LeonFassbier/days/leon-02/input.txt";

    let compare_set = CubeSet {
        red: 12,
        green: 13,
        blue: 14,
    };
    let mut shown_sets: Vec<Vec<CubeSet>> = Vec::new();
    let num_re = Regex::new(r"\d+").unwrap();

    for line in fs::read_to_string(filepath).unwrap().lines() {
        let mut game_sets: Vec<CubeSet> = Vec::new();
        let line_string = line.to_string();
        let game = line_string
            .split(':')
            .skip(1)
            .next()
            .expect("Could not split Game in parsing");
        let game_parts = game.split(';');
        for game_part in game_parts {
            let color_parts = game_part.split(',');
            let mut cube_set = CubeSet {
                red: 0,
                green: 0,
                blue: 0,
            };
            for color_part in color_parts {
                let num_string = num_re
                    .find(color_part)
                    .expect("Could not find number of cubes")
                    .as_str();
                let num = num_string.parse::<i32>().expect("Could not parse integer");
                let is_red = color_part.find("red").is_some();
                if is_red {
                    cube_set.red = num;
                    continue;
                }
                let is_green = color_part.find("green").is_some();
                if is_green {
                    cube_set.green = num;
                    continue;
                }
                let is_blue = color_part.find("blue").is_some();
                if is_blue {
                    cube_set.blue = num;
                    continue;
                }
                panic!("Could not determine color of cube");
            }
            game_sets.push(cube_set);
        }

        shown_sets.push(game_sets);
    }

    let mut possible_games: Vec<usize> = Vec::new();
    let mut powers: Vec<i32> = Vec::new();
    for (i, set_list) in shown_sets.iter().enumerate() {
        let mut is_possible = true;
        let mut min_set = CubeSet {
            red: 0,
            green: 0,
            blue: 0,
        };
        for set in set_list.iter() {
            if set.red > compare_set.red
                || set.blue > compare_set.blue
                || set.green > compare_set.green
            {
                is_possible = false;
            }
            if set.red > min_set.red {
                min_set.red = set.red;
            }
            if set.green > min_set.green {
                min_set.green = set.green;
            }
            if set.blue > min_set.blue {
                min_set.blue = set.blue;
            }
        }
        if is_possible {
            possible_games.push(i + 1);
        }
        powers.push(min_set.red * min_set.green * min_set.blue);
    }
    let possible_game_sum = possible_games.iter().fold(0, |sum, val| sum + val);
    println!("Possible game sum is {possible_game_sum}");

    let mut power_sum = 0;
    for power in powers.iter() {
        power_sum += power;
        if power_sum < 0 { 
            panic!("Suspecting overflow");
        }
    }
    println!("Power sum is {power_sum}");
}
