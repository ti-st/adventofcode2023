use std::{collections::HashMap, fs};

#[derive(Debug, Clone, Eq, PartialEq, Hash)]
enum Direction {
    Left,
    Right,
}

#[derive(Debug, Clone, Eq, PartialEq, Hash)]
struct MapNodeRaw {
    id: String,
    left_id: String,
    right_id: String,
}

struct MapNode {
    id: String,
    index: usize,
    left_id: String,
    left_i: usize,
    right_id: String,
    right_i: usize,
    // left: Option<&'a MapNode<'a>>,
    // right: Option<&'a MapNode<'a>>,
}

fn main() {
    let filepath = "input.txt";

    println!("Using input {}", filepath.split('/').last().unwrap());

    let file_input = fs::read_to_string(filepath).unwrap();
    let mut input_lines = file_input.lines();
    let first_line = input_lines.next().expect("No line parsed");

    let mut directions: Vec<Direction> = Vec::new();
    for char in first_line.chars() {
        match char {
            'L' => directions.push(Direction::Left),
            'R' => directions.push(Direction::Right),
            _ => continue,
        };
    }

    println!("Found {} directions", directions.len());

    let _blank_line = input_lines.next();
    let mut nodes_raw: HashMap<String, MapNodeRaw> = HashMap::new();

    for node_line in input_lines {
        let mut line_parts = node_line.split('=');
        let id = line_parts
            .next()
            .expect("Could not split line properly")
            .trim();
        let mut dest_ids = line_parts
            .next()
            .expect("Could not split line properly")
            .trim()
            .split(',');
        let dest_left = dest_ids
            .next()
            .expect("dest parse fail")
            .trim()
            .replace("(", "");
        let dest_right = dest_ids
            .next()
            .expect("dest parse fail")
            .trim()
            .replace(")", "");

        let map_node = MapNodeRaw {
            id: id.to_string(),
            left_id: dest_left,
            right_id: dest_right,
        };
        nodes_raw.insert(id.to_string(), map_node);
    }

    // let start_map = maps_raw.get("AAA").expect("Could not find Start map 'AAA'");
    let mut i_steps = 0;
    let mut next_id = "AAA";
    let mut direction_iter = directions.iter();
    while let Some(cur_node) = nodes_raw.get(next_id) {
        let step = match direction_iter.next() {
            Some(direction) => direction,
            None => {
                direction_iter = directions.iter();
                direction_iter
                    .next()
                    .expect("Expected direction iterator to have at leas one input")
            }
        };

        if cur_node.id == "ZZZ" {
            break;
        }
        match step {
            Direction::Left => next_id = &cur_node.left_id,
            Direction::Right => next_id = &cur_node.right_id,
        }
        i_steps += 1;
    }

    if next_id != "ZZZ" {
        println!("Did not end up at ZZZ");
    }
    println!("Walked {i_steps} steps");

    let mut nodes_arr: Vec<MapNode> = Vec::with_capacity(nodes_raw.len());
    let mut indices: HashMap<String, usize> = HashMap::new();

    let mut index = 0;
    for (_, node_raw) in nodes_raw.iter() {
        let complex_node = MapNode {
            id: node_raw.id.clone(),
            index: index,
            left_id: node_raw.left_id.clone(),
            right_id: node_raw.right_id.clone(),
            left_i: 0,
            right_i: 0,
        };
        // nodes_by_id.insert(node_raw.id.clone(), complex_node);
        indices.insert(complex_node.id.clone(), index);
        nodes_arr.push(complex_node);
        index += 1;
    }

    for i in 0..nodes_arr.len() {
        let node = nodes_arr.get_mut(i).unwrap();

        let dest_left = indices
            .get(&node.left_id)
            .expect("Failed to set up map entries correctly");
        let dest_right = indices
            .get(&node.right_id)
            .expect("Failed to set up map entries correctly");

        node.left_i = dest_left.clone();
        node.right_i = dest_right.clone();
    }

    // for (_, node_raw) in nodes_raw.iter() {
    // let to_mutate = nodes_by_id.get_mut(&node_raw.id).unwrap();
    // nodes_by_id2.insert(to_mutate.id.clone(), to_mutate);
    // nodes.push(complex_node);
    // }

    // for (_, node_raw) in nodes_raw.iter() {
    // let dest_left = nodes_by_id
    //     .get(&node_raw.left_id)
    //     .expect("Failed to set up map entries correctly")
    //     .clone();
    // let dest_right = nodes_by_id
    //     .get(&node_raw.right_id)
    //     .expect("Failed to set up map entries correctly");

    // let to_mutate = nodes_by_id.get_mut(&node_raw.id).unwrap();
    // to_mutate.id = "test".to_string();
    // to_mutate.left = Some(dest_left);
    // nodes_by_id.entry(node_raw.id.clone()).and_modify(|n| {
    //     n.left = Some(nodes_by_id2.get(&node_raw.left_id).expect(""));
    //     n.right = Some(nodes_by_id2.get(&node_raw.left_id).expect(""));
    // });

    // to_link.insert(node_raw.id.clone(), (*dest_left, *dest_right));
    // maps.push(complex_map);
    // }

    let mut next_ids: Vec<usize> = nodes_arr
        .iter()
        .filter_map(|s| {
            if s.id.ends_with('A') {
                return Some(s.index);
            }
            None
        })
        .collect();


    println!("gcd of 5, 10 is {}", gcd(5, 10));
    println!("gcd of 10, 5 is {}", gcd(10, 5));
    println!("gcd of 5, 13 is {}", gcd(5, 13));
    println!("gcd of 13, 5 is {}", gcd(13, 5));
    let mut cycles: Vec<Cycle> = Vec::new();
    for next_id in next_ids.iter() {
        let node = nodes_arr.get(next_id.clone()).unwrap();
        let cycle = get_cycle(&node.id, &nodes_raw, &directions);
        println!("Found {:?} for start {}", cycle, node.id);
    
        cycles.push(cycle);
    }

    let mut cycles_iter = cycles.iter();
    let mut lowest_common_multiple: i64 = cycles_iter.next().unwrap().length.into();
    for cycle in cycles_iter {
        let new_lcm = lowest_common_multiple * i64::from(cycle.length) / gcd(lowest_common_multiple, cycle.length.into());
        lowest_common_multiple = new_lcm;
    }

    println!("Lowest common multiple is {lowest_common_multiple}");

    let mut i_steps_ghost: i64 = 0;

    direction_iter = directions.iter();
    loop {
        if i_steps_ghost % 100_000 == 0 {
            print!("\r walked {i_steps_ghost} steps")
        }

        let step = match direction_iter.next() {
            Some(direction) => direction,
            None => {
                direction_iter = directions.iter();
                direction_iter
                    .next()
                    .expect("Expected direction iterator to have at leas one input")
            }
        };
        let mut new_next_ids: Vec<usize> = Vec::with_capacity(next_ids.len());
        let mut cur_nodes: Vec<&MapNode> = Vec::with_capacity(new_next_ids.len());

        for id in next_ids.iter() {
            let cur_node = nodes_arr.get(id.clone()).unwrap();
            match step {
                Direction::Left => new_next_ids.push(cur_node.left_i),
                Direction::Right => new_next_ids.push(cur_node.right_i),
            }
            cur_nodes.push(cur_node);
        }
        if cur_nodes.iter().all(|n| n.id.ends_with('Z')) {
            break;
        }

        i_steps_ghost += 1;
        next_ids = new_next_ids;
    }
    println!();
    println!("Walked {i_steps_ghost} steps as ghosts");
}

#[derive(Debug, Clone)]
struct Cycle {
    node_id: String,
    length: i32,
    first_encounter: i32,
}

fn get_cycle(
    start_node: &str,
    maps: &HashMap<String, MapNodeRaw>,
    directions: &Vec<Direction>,
) -> Cycle {
    let mut i_steps = 0;
    let mut next_id = start_node;
    let mut direction_iter = directions.iter();
    let mut direction_i = 0;

    let mut encounters: HashMap<String, Vec<(i32, i32)>> = HashMap::new();
    for possible_end_id in maps.keys().filter(|s| s.ends_with('Z')) {
        encounters.insert(possible_end_id.clone(), Vec::new());
    }

    while let Some(cur_map) = maps.get(next_id) {
        let step = match direction_iter.next() {
            Some(direction) => direction,
            None => {
                direction_iter = directions.iter();
                direction_i = 0;
                direction_iter
                    .next()
                    .expect("Expected direction iterator to have at leas one input")
            }
        };
        if cur_map.id.ends_with('Z') {
            let encounter_list = encounters.get_mut(&cur_map.id).unwrap();
            let previous_same = encounter_list.iter().find(|v| v.0 == direction_i);
            if previous_same.is_some() {
                return Cycle {
                    node_id: cur_map.id.clone(),
                    first_encounter: previous_same.unwrap().1,
                    length: i_steps - previous_same.unwrap().1,
                };
            }
            encounter_list.push((direction_i, i_steps));
        }

        match step {
            Direction::Left => next_id = &cur_map.left_id,
            Direction::Right => next_id = &cur_map.right_id,
        }
        i_steps += 1;
        direction_i += 1;
    }
    panic!("Did not want to get here");
}

fn gcd (a: i64, b: i64) -> i64 {
    if a == 0 {
        return b;
    }
    if b == 0 {
        return a;
    }

    if a > b {
        return gcd(b, a % b);
    } else {
        return gcd(a, b % a);
    }
}

// fn get_steps_to_z_maps(start_node: &str, maps: &HashMap<String, MapRaw>, directions: &Vec<Direction>) -> Vec<i32> {
//     let mut computed_end_nodes: Vec<String> = Vec::new();
//     let mut computed_end_node_steps: Vec<i32> = Vec::new();

//     let mut i_steps = 0;
//     let mut next_id = start_node;
//     let mut direction_iter = directions.iter();

//     while let Some(cur_map) = maps.get(next_id) {
//         let step = match direction_iter.next() {
//             Some(direction) => direction,
//             None => {
//                 direction_iter = directions.iter();
//                 direction_iter
//                     .next()
//                     .expect("Expected direction iterator to have at leas one input")
//             }
//         };

//         match step {
//             Direction::Left => next_id = &cur_map.left_id,
//             Direction::Right => next_id = &cur_map.right_id,
//         }
//         i_steps += 1;
//     }

//     computed_end_node_steps
// }
