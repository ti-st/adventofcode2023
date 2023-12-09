use std::collections::HashMap;
use std::{cmp::Ordering, fs};

#[derive(Debug, PartialEq, Eq, Hash, Clone)]
enum Cards {
    Joker = 1,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace,
}

#[derive(Debug, PartialEq, Eq, Hash, Clone)]
enum HandValues {
    HighCard = 1,
    Pair,
    TwoPair,
    ThreeOfAKind,
    FullHouse,
    FourOfAKind,
    DafuckIsThisCardDeck,
}

#[derive(Debug, Clone)]
struct Hand {
    cards: Vec<Cards>,
    bid: i32,
    value: HandValues,
}

#[derive(Debug, Clone)]
struct PokerError;

fn compute_hand_value(cards: &Vec<Cards>) -> Result<HandValues, PokerError> {
    if cards.len() != 5 {
        return Err(PokerError);
    }
    let mut map: HashMap<Cards, i32> = HashMap::new();
    for c in cards {
        if map.contains_key(c) {
            let cur = map[c];
            map.remove(c);
            map.insert(c.clone(), cur + 1);
        } else {
            map.insert(c.clone(), 1);
        }
    }

    let jokers = map.get(&Cards::Joker);
    match map.len() {
        5 => match jokers {
            None => Ok(HandValues::HighCard),
            Some(1) => Ok(HandValues::Pair),
            _ => panic!("Jokers + other cards apparently don't add up to 5?"),
        },
        4 => match jokers {
            None => Ok(HandValues::Pair),
            Some(1) | Some(2) => Ok(HandValues::ThreeOfAKind), // Joker + pair or pair of jokers + card
            _ => panic!("Jokers + other cards apparently don't add up to 5?"),
        },
        3 => {
            if map.iter().any(|(_, i)| *i == 3) {
                // Three-of-a kind (without considering jokers).
                match jokers {
                    None => Ok(HandValues::ThreeOfAKind),
                    Some(1) | Some(3) => Ok(HandValues::FourOfAKind),
                    _ => panic!("Jokers + other cards apparently don't add up to 5?"),
                }
            } else {
                // Two pair (without considering jokers).
                match jokers {
                    None => Ok(HandValues::TwoPair),
                    Some(1) => Ok(HandValues::FullHouse),
                    Some(2) => Ok(HandValues::FourOfAKind),
                    _ => panic!("Jokers + other cards apparently don't add up to 5?"),
                }
            }
        }
        2 => {
            if map.iter().any(|(_, i)| *i == 4) {
                match jokers {
                    None => Ok(HandValues::FourOfAKind),
                    Some(1) | Some(4) => Ok(HandValues::DafuckIsThisCardDeck),
                    _ => panic!("Jokers + other cards apparently don't add up to 5?"),
                }
            } else {
                match jokers {
                    None => Ok(HandValues::FullHouse),
                    Some(2) | Some(3) => Ok(HandValues::DafuckIsThisCardDeck),
                    _ => panic!("Jokers + other cards apparently don't add up to 5?"),
                }
            }
        }
        1 => Ok(HandValues::DafuckIsThisCardDeck),
        _ => Err(PokerError),
    }
}

impl Hand {
    fn compare(&self, other: &Hand) -> Ordering {
        if self.cards.len() != other.cards.len() {
            panic!("Tried to compare hands of different sizes");
        }

        if (self.value.clone() as i32) < (other.value.clone() as i32) {
            return Ordering::Less;
        }
        if (self.value.clone() as i32) > (other.value.clone() as i32) {
            return Ordering::Greater;
        }

        let mut other_iter = other.cards.iter();
        for c_self in self.cards.iter() {
            let c_other = other_iter
                .next()
                .expect("the two hands should have the same length");
            if (c_self.clone() as i32) < (c_other.clone() as i32) {
                return Ordering::Less;
            }
            if (c_self.clone() as i32) > (c_other.clone() as i32) {
                return Ordering::Greater;
            }
        }

        panic!("Could not determine order of hands {:?}, {:?}", self, other);
        // Ordering::Equal
    }
}

fn main() {
    let filepath =
        "/home/fass/codeProjects/adventofcode2023/LeonFassbier/days/leon-07/input.txt";
    let j_as_joker = true;

    let mut hands: Vec<Hand> = Vec::new();
    for line in fs::read_to_string(filepath).unwrap().lines() {
        let mut line_parts = line.split(' ');
        let hand_line = line_parts.next().expect("First part should be the cards");
        let bid_line = line_parts.next().expect("Second part should be the bid");
        let bid = i32::from_str_radix(bid_line, 10).expect("Could not parse bid as integer");

        let mut cards: Vec<Cards> = Vec::new();
        for c in hand_line.chars() {
            if cards.len() == 5 {
                break;
            }
            match c {
                '2' => cards.push(Cards::Two),
                '3' => cards.push(Cards::Three),
                '4' => cards.push(Cards::Four),
                '5' => cards.push(Cards::Five),
                '6' => cards.push(Cards::Six),
                '7' => cards.push(Cards::Seven),
                '8' => cards.push(Cards::Eight),
                '9' => cards.push(Cards::Nine),
                'T' => cards.push(Cards::Ten),
                'J' => {
                    if j_as_joker {
                        cards.push(Cards::Joker)
                    } else {
                        cards.push(Cards::Jack)
                    }
                }
                'Q' => cards.push(Cards::Queen),
                'K' => cards.push(Cards::King),
                'A' => cards.push(Cards::Ace),
                _ => {
                    panic!("Expected first five characters to be a number of one of T, J, Q, K, A")
                }
            };
        }

        let hand_value = compute_hand_value(&cards).expect("Could not determine hand value");
        // println!("Determined {:?} for {hand_line}", hand_value.clone());
        let hand = Hand {
            bid: bid,
            cards,
            value: hand_value,
        };
        hands.push(hand);
    }

    hands.sort_by(Hand::compare);
    let mut winnings = 0;
    let mut i = 0;
    for hand in hands.iter() {
        i += 1;
        winnings += i * hand.bid;
    }

    println!("Total winnings are {winnings}");
}
