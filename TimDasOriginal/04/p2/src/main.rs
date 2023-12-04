use std::{fs, collections::HashMap};

const SEPERATOR: char = '|';
#[derive(Copy, Clone)]
struct Card<'a> {
    id: i32,
    matching_numbers: i32,
    numbers: &'a str,
    copies: i32,
}

impl Card<'_> {
    fn get_matches(&mut self) {
        // let line_content:Vec<&str> = self.numbers.split(":").collect();
        let numbers:Vec<&str> = self.numbers.split(SEPERATOR).collect();
        let mut lhs = numbers[0].trim().split(" ").collect::<Vec<&str>>();

        let mut rhs = numbers[1].trim().split(" ").collect::<Vec<&str>>();

        let mut matching = 0;
        for c in lhs {
            if c == "" {
                continue;
            } else {
                for c2 in &rhs {
                    if c2 == &"" {
                        continue;
                    } else if &c == c2 {
                        matching += 1;
                    }
                }
            }
        }
        self.matching_numbers = matching;
    }
}


fn main() {
    let mut id_to_card:HashMap<i32, Card> = HashMap::new();
    
    let filename = "src/input.txt";
    let contents = fs::read_to_string(filename)
        .expect("Should have been able to read the file");
    let mut sum = 0;

    // let mut cards:Vec<Card> = vec![];
    for line in contents.lines() {
        let line_content:Vec<&str> = line.split(":").collect();
        let mut new_card = Card{
            id: 0,
            matching_numbers: 0,
            numbers: line_content[1],
            copies: 0,
        };
        let mut str_nbr = String::new();
        for c in line_content[0].chars(){
            if c.is_numeric(){
                str_nbr.push(c);
            }
        }
        new_card.id = str_nbr.parse::<i32>().unwrap();
        new_card.get_matches();

        // print!("Found {} matches for card {}\n", new_card.matching_numbers, new_card.id);
        id_to_card.insert(new_card.id, new_card);
    }
    
    for id in 1..1+id_to_card.clone().values().len() as i32 {
        println!("id: {}", id);
        let mut card = id_to_card.get_mut(&id).unwrap().clone();
        if card.matching_numbers == 0{
            // println!("IF - id: {}, matching: {}", id, card.matching_numbers);
            continue;
        }else if card.matching_numbers+id <=id_to_card.values().len() as i32 {
            // println!("id: {}, matching: {}", id, card.matching_numbers);
            for i in 0..card.matching_numbers {
                let mut c = id_to_card.get_mut(&(i+id+1)).unwrap();
                c.copies+=(1+card.copies);
            }
        } else {
            // println!("ELSE - id: {}, matching: {}", id, card.matching_numbers);
            for i in 0..(id_to_card.values().len()-1-id as usize) as i32{
                let mut c = id_to_card.get_mut(&(i+id+1)).unwrap();
                c.copies+=(1+card.copies);
            }
        }
    }

    for card in id_to_card.values() {
        // print!("Card {} has {} copies\n", card.id, card.copies);
        sum += 1+card.copies;
    }
    
    print!("Result: {}\n", sum);
}
