use regex::Regex;
use std::fs;

struct Map {
    src: String,
    dst: String,
    ranges: Vec<MapRange>,
}

struct MapRange {
    src: Range,
    dst_start: i64,
}

#[derive(Debug, Copy, Clone)]
struct Range {
    start: i64,
    len: i64,
}

impl Range {
    fn overlaps(&self, other: &Range) -> bool {
        if self.start >= other.start + other.len {
            return false;
        }
        if self.start + self.len <= other.start {
            return false;
        }
        true
    }
}

impl Map {
    fn map(&self, input: i64) -> i64 {
        let relevant_range = self
            .ranges
            .iter()
            .find(|r| r.src.start <= input && input < r.src.start + r.src.len);

        match relevant_range {
            None => input,
            Some(range) => {
                let offset = input - range.src.start;
                range.dst_start + offset
            }
        }
    }

    fn map_range(&self, input: Range) -> Vec<Range> {
        let mut result: Vec<Range> = Vec::new();
        let mut still_to_map: Vec<Range> = Vec::new();
        still_to_map.push(input);

        for range in self.ranges.iter() {
            let mut next_to_map: Vec<Range> = Vec::new();
            for to_map in still_to_map.into_iter() {
                if !range.src.overlaps(&to_map) {
                    next_to_map.push(to_map);
                    continue;
                }
                let mut mappable_lower = to_map.start;
                let mut mappable_len = to_map.len;
                if to_map.start < range.src.start {
                    let lower_overlap = Range {
                        start: to_map.start,
                        len: range.src.start - to_map.start,
                    };
                    mappable_lower = range.src.start;
                    mappable_len -= lower_overlap.len;
                    next_to_map.push(lower_overlap);
                }
                if to_map.start + to_map.len > range.src.start + range.src.len {
                    let upper_overlap = Range {
                        start: range.src.start + range.src.len,
                        len: to_map.start + to_map.len - range.src.start - range.src.len,
                    };
                    mappable_len -= upper_overlap.len;
                    next_to_map.push(upper_overlap);
                }

                let offset = mappable_lower - range.src.start;
                let mapped = Range {
                    start: range.dst_start + offset,
                    len: mappable_len,
                };
                result.push(mapped);
            }

            still_to_map = next_to_map;
        }

        for to_map in still_to_map.into_iter() {
            result.push(to_map);
        }
        result
    }
}

fn main() {
    // let filepath = "/home/fass/codeProjects/adventofcode2023/LeonFassbier/days/leon-05/testInput.txt";
    let filepath = "/home/fass/codeProjects/adventofcode2023/LeonFassbier/days/leon-05/input.txt";

    println!("Using input {}", filepath.split('/').last().unwrap());

    let num_re = Regex::new(r"\d+").unwrap();
    let mut seeds: Vec<i64> = Vec::new();
    let mut seed_ranges: Vec<Range> = Vec::new();

    let file_input = fs::read_to_string(filepath).unwrap();
    let mut input_lines = file_input.lines();
    let first_line = input_lines.next().expect("No line parsed");

    for digit_str in num_re.find_iter(first_line) {
        let seed = i64::from_str_radix(digit_str.as_str().trim(), 10)
            .expect("Could not parse seed number");
        seeds.push(seed);
    }

    for i in 0..seeds.len() / 2 {
        seed_ranges.push(Range {
            start: seeds[2 * i],
            len: seeds[2 * i + 1],
        });
    }

    println!("Found {} seeds", seeds.len());
    println!("Found {} seed ranges", seed_ranges.len());

    let mut maps: Vec<Map> = Vec::new();

    for line in input_lines {
        if line.contains("map") {
            let map_identifier = line
                .split(' ')
                .next()
                .expect("Could not get map identifier")
                .trim();
            let mut map_parts = map_identifier.split('-');
            let src = map_parts.next().expect("Could not determine map source");
            let dst = map_parts
                .skip(1)
                .next()
                .expect("Could not determine map destination");

            let map = Map {
                src: src.to_owned(),
                dst: dst.to_owned(),
                ranges: Vec::new(),
            };

            maps.push(map);
        }

        let found_nums =
            Vec::from_iter(num_re.find_iter(line).map(|m| {
                i64::from_str_radix(m.as_str(), 10).expect("Could not parse range number")
            }));

        match found_nums.len() {
            0 => continue,
            3 => {}
            _ => panic!("Ranges should have three number-strings"),
        }

        let range = MapRange {
            dst_start: found_nums[0],
            src: Range {
                start: found_nums[1],
                len: found_nums[2],
            },
        };

        let cur_map = maps.last_mut();
        cur_map.unwrap().ranges.push(range);
    }

    println!("Found {} maps", maps.len());

    let mut final_mapped: Vec<i64> = Vec::new();
    for seed in seeds {
        let mut cur_map = maps
            .iter()
            .find(|m| m.src == "seed")
            .expect("No seed-map found");
        let mut mapped = cur_map.map(seed);

        while let Some(next_map) = maps.iter().find(|m| m.src == cur_map.dst) {
            mapped = next_map.map(mapped);
            cur_map = &next_map;
        }
        // println!("Mapped to {mapped}");
        final_mapped.push(mapped);
    }

    let min_mapped = final_mapped
        .into_iter()
        .min()
        .expect("Could not get minimum");
    println!("Minimum mapped output is {min_mapped}");

    let mut final_mapped: Vec<Vec<Range>> = Vec::new();
    for seed_range in seed_ranges {
        let mut cur_map = maps
            .iter()
            .find(|m| m.src == "seed")
            .expect("No seed-map found");

        let mut mapped = cur_map.map_range(seed_range);
        // println!("Mapped to {} ranges", mapped.len());

        while let Some(next_map) = maps.iter().find(|m| m.src == cur_map.dst) {
            let mut next_mapped: Vec<Range> = Vec::new();
            for r in mapped {
                let partial_mapped = next_map.map_range(r);
                for partial in partial_mapped.into_iter() {
                    next_mapped.push(partial);
                }
            }

            cur_map = &next_map;
            mapped = next_mapped;
        }
        // println!("Mapped to {} ranges", mapped.len());
        println!("Mapping for seed range complete into {} total ranges", mapped.len());
        final_mapped.push(mapped);
    }

    let range_mins = Vec::from_iter(final_mapped.iter().map(|r_vec| {
        r_vec
            .into_iter()
            .map(|r| r.start)
            .min()
            .expect("Could not get minimum of starts")
    }));
    let total_min = range_mins.into_iter().min().expect("Could not get global minimum");

    println!("Lowest location number is {total_min}");
}
