use std::fs;

#[derive(Clone)]
struct Interval{
    start: i64,
    end: i64,
    length: i64,
    maps_to: i32
}

impl Interval{
    fn new(start: i64, end: i64, length: i64, maps_to: i32) -> Interval{
        Interval{
            start,
            end,
            length,
            maps_to
        }
    }

    fn intervals_overlapp(&mut self, other: &mut Interval) -> bool{
        if self.start <= other.start && self.end >= other.start{
            return true;
        }
        if self.start <= other.end && self.end >= other.end{
            return true;
        }
        if self.start >= other.start && self.end <= other.end{
            return true;
        }
        return false;
    }

}


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
    let filename = "src/testinput.txt";
    let contents = fs::read_to_string(filename)
        .expect("Should have been able to read the file");
    let mut lowest_loc = 0;


    let mut seeds:Vec<i64> = Vec::new();

    let first_line_of_contents = contents.lines().next().unwrap();

    for part in first_line_of_contents.trim().split(" "){
        if part != "seeds:"{
            seeds.push(part.parse::<i64>().unwrap());
        }
    }

    // groups contain maps between intervals
    let mut groups:Vec<Vec<Interval>> = Vec::new();
    let mut intervals:Vec<Interval> = Vec::new();
    let mut temp:Vec<Interval> = Vec::new();

    // build interval maps
    let mut counter = 0;
    for line in contents.lines().rev() {
        if is_number_line(line) {
            // three numbers per line
            let numbers = line.trim().split(" ").collect::<Vec<&str>>();
            let start = numbers[1].parse::<i64>().unwrap();
            let end = numbers[0].parse::<i64>().unwrap();
            let length: i64 = numbers[2].parse::<i64>().unwrap();
            
            // build up intervals of the group and their images
            let mut interval = Interval::new(end, end+length-1, length, counter+1);
            intervals.push(interval);
            counter += 1;
            let mut other_interval = Interval::new(start, start+length-1, length, -1);
            intervals.push(other_interval);
            counter += 1;
        } else {
            // end of a group
            if intervals.len() > 0 {
                groups.push(intervals.clone());
                intervals.clear();
                counter = 0;
            }
            if "seeds:" == line.trim().split(" ").collect::<Vec<&str>>()[0]{
                break;
            }
        }
    }
    // loop trough intervall maps from bottom to top
    // each interval without an image in the next layer is removed
    // each interval which is only partially covered by an image is shortened
    // each interval which is fully covered by an image stays
    let lowest_intervals:Vec<Interval> = Vec::new();

    // TODO: 
    /*
    - start at lowest group
    - loop trough intervals, for each interval without map=-1, take their image (map_to) and check if the image overlaps with any other interval in the next group where the upper-level interval is the ground-level (map_to != -1)
    - shrink down the interval in the lower group to the BIGGEST possible interval
    - go to the next upper group level and repeat. If a middle-layer group interval is shrinked down, propagate the shrinking down to the lower group level
     */

    // for group_index in 0..groups.len()-1{
    //     let mut lower_intervals = groups[group_index];
    //     let mut upper_intervals = groups[group_index+1];
    //     for interval_lower in lower_intervals.clone().iter_mut(){
    //         for interval_upper in upper_intervals.iter_mut(){
    //             let a = interval_lower.maps_to;
    //             if lower_intervals[a as i32].intervals_overlapp(&mut interval_upper){

    //             }
    //         }
    //     }
    // }



    let mut loc = i64::MAX;
    for seed in seeds.iter(){
        if *seed < loc{
            loc = *seed;
        }
    }

    print!("Result: {}\n", loc);
}
