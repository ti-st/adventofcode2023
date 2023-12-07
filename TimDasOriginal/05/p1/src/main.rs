use std::fs;

// const seed_soil: &str = "seed-to-soil map:";
// const soil_fert: &str = "soil-to-fertilizer map:";
// const fert_water: &str = "fertilizer-to-water map:";
// const water_light: &str = "water-to-light map:";
// const light_temp: &str = "light-to-temperature map:";
// const temp_hum: &str = "temperature-to-humidity map:";
// const hum_loc: &str = "humidity-to-location map:";
// const keyword: &str = "map:";

fn num_in_tup(num: i64, tup: (i64, i64, i64)) -> bool{
    if num >= tup.1 && num <= tup.1+tup.2-1{
        return true;
    }
    return false;
}

fn get_new_number(num: i64, tup: (i64, i64, i64)) -> i64{
    return tup.0 + (num - tup.1);
}

fn is_number_line(line: &str) -> bool{
    if line.trim() != "" && line.trim().split(" ").collect::<Vec<&str>>()[0] != "seeds:" && 
    line.trim().split(" ").collect::<Vec<&str>>()[1] != "map:"{
        return true;
    }
    return false;
}

fn main() {
    let filename = "src/input.txt";
    let contents = fs::read_to_string(filename)
        .expect("Should have been able to read the file");
    let mut lowest_loc = 0;

    let mut temp:Vec<(i64,i64,i64)> = Vec::new();

    let mut seeds:Vec<i64> = Vec::new();

    let first_line_of_contents = contents.lines().next().unwrap();

    for part in first_line_of_contents.trim().split(" "){
        if part != "seeds:"{
            seeds.push(part.parse::<i64>().unwrap());
        }
    }

    for line in contents.lines() {
        if is_number_line(line) {
            // three numbers per line
            let numbers = line.trim().split(" ").collect::<Vec<&str>>();
            let start = numbers[1].parse::<i64>().unwrap();
            let end = numbers[0].parse::<i64>().unwrap();
            let length: i64 = numbers[2].parse::<i64>().unwrap();
            
            temp.push((end, start, length));
        } else {
            if temp.len() > 0{
                let mut mapped_seeds:Vec<i64> = Vec::new();
                for i in 0..temp.len(){
                    for seed in seeds.iter_mut(){
                        // print!("{} ", seed);
                        if num_in_tup(*seed, temp[i]) && !mapped_seeds.contains(&seed){
                            *seed = get_new_number(*seed, temp[i]);
                            mapped_seeds.push(seed.clone());
                        }
                    }
                }
                temp.clear();
                for seed in seeds.iter(){
                    print!("{} ", seed)
                }
                print!("\n");
            }
        }
        // match line {
        //     seed_soil => {

        //         map_ref = &mut map_seed_soil;
        //     },
        //     soil_fert => {
        //         map_ref = &mut map_soil_fert;
        //     },
        //     fert_water => {
        //         map_ref = &mut map_fert_water;
        //     },
        //     water_light => {
        //         map_ref = &mut map_water_light;
        //     },
        //     light_temp => {
        //         map_ref = &mut map_light_temp;
        //     },
        //     temp_hum => {
        //         map_ref = &mut map_temp_hum;
        //     },
        //     hum_loc => {
        //         map_ref = &mut map_hum_loc;
        //     },
        //     _ => {
        //         if line.trim() == "" || line.trim().split(" ").collect::<Vec<&str>>()[0] == "seeds:"{
        //             map_ref = &mut empty;
        //         } else {
        //             // three numbers per line
        //             let numbers = line.trim().split(" ").collect::<Vec<&str>>();
        //             let start = numbers[1].parse::<i64>().unwrap();
        //             let end = numbers[0].parse::<i64>().unwrap();
        //             let length: i64 = numbers[2].parse::<i64>().unwrap();
        //             for i in 0..length{
        //                 map_ref.insert(start+i, end+i);
        //             }
        //         }
        //     }
        // }
    }

    let mut loc = i64::MAX;
    for seed in seeds.iter(){
        if *seed < loc{
            loc = *seed;
        }
    }

    print!("Result: {}\n", loc);
}
