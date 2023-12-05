use regex::Regex;
use std::fs;

struct CardSet {
    winning: Vec<i32>,
    own: Vec<i32>,
    num: i32,
}

fn main() {
    // let filepath ="/home/fass/codeProjects/adventofcode2023/LeonFassbier/days/leon-04/testInput.txt";
    let filepath = "/home/fass/codeProjects/adventofcode2023/LeonFassbier/days/leon-04/input.txt";

    let num_re = Regex::new(r"\d+").unwrap();
    let mut cards: Vec<CardSet> = Vec::new();
    for line in fs::read_to_string(filepath).unwrap().lines() {
        let line_string = line.to_string();
        let card_string = line_string
            .split(':')
            .skip(1)
            .next()
            .expect("Could not split Game in parsing");

        let mut number_set_strings = card_string.split('|').map(|s| s.trim());
        let winning_string = number_set_strings
            .next()
            .expect("Could not split off winning numbers");
        let own_string = number_set_strings
            .next()
            .expect("Could not split off own numbers");

        let winning_nums = num_re.find_iter(winning_string).map(|m| {
            i32::from_str_radix(m.as_str(), 10).expect("Could not parse digits into i32 number")
        });
        let own_nums = num_re.find_iter(own_string).map(|m| {
            i32::from_str_radix(m.as_str(), 10).expect("Could not parse digits into i32 number")
        });
        let card = CardSet {
            winning: Vec::from_iter(winning_nums),
            own: Vec::from_iter(own_nums),
            num: 1,
        };
        cards.push(card);
    }

    let mut points = 0;
    for card in cards.iter() {
        let mut card_points = 0;
        for own_num in card.own.iter() {
            if card.winning.contains(own_num) {
                match card_points {
                    0 => card_points = 1,
                    _ => card_points = card_points * 2,
                }
            }
        }
        points += card_points;
    }

    println!("Total number of points for Part 1 is {points}");

    for i in 0..cards.len() {
        let card = &cards[i];
        let card_num = card.num;
        let mut num_matching = 0;
        for own_num in card.own.iter() {
            if card.winning.contains(own_num) {
                num_matching += 1;
            }
        }
        for i_copied in (i + 1)..(i + 1 + num_matching) {
            cards[i_copied].num += card_num;
        }
    }

    let total_cards: i32 = cards.into_iter().map(|c| c.num).sum();

    println!("Total number of cards for Part 2 is {total_cards}");
}
