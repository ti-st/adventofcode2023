use std::fs;

const SEPERATOR: char = '|';

fn main() {
    let filename = "src/input.txt";
    let contents = fs::read_to_string(filename)
        .expect("Should have been able to read the file");
    let mut sum = 0;

    for line in contents.lines() {
        let line_content:Vec<&str> = line.split(":").collect();
        let numbers:Vec<&str> = line_content[1].split(SEPERATOR).collect();
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


        print!("{}\n", matching);
        if matching > 0
        {
            // sum += 2.pow((matching-1));  // WEIL JA OFFENSICHTLICH I32^I32 NICHT I32 IST, DA MUSS MAN JA AUFPASSEN......
            sum += i32::pow(2, (matching - 1).try_into().unwrap());
        }
    }
    
    print!("Result: {}\n", sum);
}
