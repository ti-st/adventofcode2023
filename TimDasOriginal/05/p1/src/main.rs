use std::{fs, collections::HashMap, hash::Hash};

const seed_soil: &str = "seed-to-soil map:";
const soil_fert: &str = "soil-to-fertilizer map:";
const fert_water: &str = "fertilizer-to-water map:";
const water_light: &str = "water-to-light map:";
const light_temp: &str = "light-to-temperature map:";
const temp_hum: &str = "temperature-to-humidity map:";
const hum_loc: &str = "humidity-to-location map:";

fn main() {
    let filename = "src/testinput.txt";
    let contents = fs::read_to_string(filename)
        .expect("Should have been able to read the file");
    let mut sum = 0;

    let mut map_seed_soil:HashMap<i32, i32> = HashMap::new();
    let mut map_soil_fert:HashMap<i32, i32> = HashMap::new();
    let mut map_fert_water:HashMap<i32, i32> = HashMap::new();
    let mut map_water_light:HashMap<i32, i32> = HashMap::new();
    let mut map_light_temp:HashMap<i32, i32> = HashMap::new();
    let mut map_temp_hum:HashMap<i32, i32> = HashMap::new();
    let mut map_hum_loc:HashMap<i32, i32> = HashMap::new();
    let mut empty:HashMap<i32, i32> = HashMap::new();

    let mut seeds:Vec<i32> = Vec::new();

    // references the hashmap to use
    let mut map_ref = &mut empty;

    let first_line_of_contents = contents.lines().next().unwrap();

    for part in first_line_of_contents.trim().split(" "){
        if part != "seeds:"{
            seeds.push(part.parse::<i32>().unwrap());
        }
    }

    for line in contents.lines() {
        match line {
            seed_soil => {
                map_ref = &mut map_seed_soil;
            },
            soil_fert => {
                map_ref = &mut map_soil_fert;
            },
            fert_water => {
                map_ref = &mut map_fert_water;
            },
            water_light => {
                map_ref = &mut map_water_light;
            },
            light_temp => {
                map_ref = &mut map_light_temp;
            },
            temp_hum => {
                map_ref = &mut map_temp_hum;
            },
            hum_loc => {
                map_ref = &mut map_hum_loc;
            },
            _ => {
                if line.trim() == "" || line.trim().split(" ").collect::<Vec<&str>>()[0] == "seeds:"{
                    map_ref = &mut empty;
                } else {
                    // three numbers per line
                    let numbers = line.trim().split(" ").collect::<Vec<&str>>();
                    let start = numbers[1].parse::<i32>().unwrap();
                    let end = numbers[0].parse::<i32>().unwrap();
                    let length: i32 = numbers[2].parse::<i32>().unwrap();
                    for i in 0..length{
                        map_ref.insert(start+i, end+i);
                    }
                }
            }

        }
    }
    
    print!("Result: {}\n", sum);
}
