use regex::Regex;
use std::fs;

struct SchematicNumber {
    value: i32,
    start: usize,
    end: usize,
}
struct SchematicSymbol {
    position: usize,
    is_gear: bool,
}

fn main() {
    // let filepath ="/home/fass/codeProjects/adventofcode2023/LeonFassbier/days/leon-03/testInput.txt";
    let filepath = "/home/fass/codeProjects/adventofcode2023/LeonFassbier/days/leon-03/input.txt";

    let num_re = Regex::new(r"\d+").unwrap();
    let sym_re = Regex::new(r"[^\.\d]").unwrap();

    let mut schematic_lines: Vec<(Vec<SchematicNumber>, Vec<SchematicSymbol>)> = Vec::new();

    for line in fs::read_to_string(filepath).unwrap().lines() {
        let mut line_schematic_nums: Vec<SchematicNumber> = Vec::new();
        let mut line_schematic_syms: Vec<SchematicSymbol> = Vec::new();

        for num_match in num_re.find_iter(line) {
            let value = i32::from_str_radix(num_match.as_str(), 10)
                .expect("Could not deserialize into number");
            let schematic_num = SchematicNumber {
                value: value,
                start: num_match.start(),
                end: num_match.end() - 1,
            };
            line_schematic_nums.push(schematic_num);
        }
        for sym_match in sym_re.find_iter(line) {
            let schematic_sym = SchematicSymbol {
                position: sym_match.start(),
                is_gear: sym_match.as_str() == "*",
            };
            line_schematic_syms.push(schematic_sym);
        }

        schematic_lines.push((line_schematic_nums, line_schematic_syms));
    }

    let mut part_nums: Vec<&SchematicNumber> = Vec::new();
    let mut iter_next_syms = schematic_lines.iter().skip(1).map(|(_, syms)| syms);
    let mut prev_syms: Option<&Vec<SchematicSymbol>> = None;

    for (nums, syms) in schematic_lines.iter() {
        let next_syms = iter_next_syms.next();

        for symset in [Some(syms), prev_syms, next_syms] {
            match symset {
                None => continue,
                Some(symset) => {
                    for num in nums.iter() {
                        let any_adjacent = symset.iter().any(|sym| is_adjacent(sym, num));
                        if any_adjacent {
                            part_nums.push(num);
                            continue;
                        }
                    }
                }
            }
        }

        prev_syms = Some(&syms)
    }

    let part_sum: i32 = part_nums.into_iter().map(|num| num.value).sum();
    println!("Total part sum is {part_sum}");

    let mut gear_ratios: Vec<i32> = Vec::new();
    let mut iter_next_nums = schematic_lines.iter().skip(1).map(|(nums, _)| nums);
    let mut prev_nums: Option<&Vec<SchematicNumber>> = None;

    for (nums, syms) in schematic_lines.iter() {
        let next_nums = iter_next_nums.next();

        for sym in syms.iter().filter(|sym| sym.is_gear) {
            let mut adjacent_vals: Vec<i32> = Vec::new();
            for numset in [Some(nums), prev_nums, next_nums]
                .into_iter()
                .filter_map(|x| x)
            {
                for num in numset.into_iter().filter(|num| is_adjacent(sym, &num)) {
                    adjacent_vals.push(num.value);
                }
            }
            if adjacent_vals.len() == 2 {
                let gear_ratio = adjacent_vals[0] * adjacent_vals[1];
                gear_ratios.push(gear_ratio);
            }
        }

        prev_nums = Some(&nums);
    }
    let gear_sum: i32 = gear_ratios.into_iter().sum();
    println!("Total gear sum is {gear_sum}");
}

fn is_adjacent(symbol: &SchematicSymbol, number: &SchematicNumber) -> bool {
    (symbol.position + 1) >= number.start && symbol.position <= (number.end + 1)
}
