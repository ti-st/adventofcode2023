struct Race {
    dist: i64,
    time: i64
}

fn dist_in_time(wait_time: i64, total_time: i64) -> i64 {
    wait_time * (total_time - wait_time)
}

fn main() {
    // let r1_test = Race {
    //     time: 7,
    //     dist: 9,
    // };
    // let r2_test = Race {
    //     time: 15,
    //     dist: 40,
    // };
    // let r3_test = Race {
    //     time: 30,
    //     dist: 200,
    // };

    let r1 = Race {
        time: 47,
        dist: 207,
    };
    let r2 = Race {
        time: 84,
        dist: 1394,
    };
    let r3 = Race {
        time: 74,
        dist: 1209,
    };
    let r4 = Race {
        time: 67,
        dist: 1014,
    };

    let mut race_numbers_time_fix: Vec<i32> = Vec::new();
    // for r in [r1_test, r2_test, r3_test] {
    for r in [r1, r2, r3, r4] {

        let mut num_better_strategies_time_fix = 0;
        
        for i in 1..r.time {
            let travelled = dist_in_time(i, r.time);
            if travelled > r.dist {
                num_better_strategies_time_fix += 1;
            }
        }
        println!("Better strategies (fixed time): {num_better_strategies_time_fix}");
        race_numbers_time_fix.push(num_better_strategies_time_fix);
    }


    let solution_product: i32 = race_numbers_time_fix.into_iter().product();
    println!("Product of better strategies is for test_input is {solution_product}");

    let large_race_test = Race {
        time: 71530,
        dist: 940200
    };

    let mut num_better_large_test = 0;
    for i in 1..large_race_test.time {
        let travelled = dist_in_time(i, large_race_test.time);
        if travelled > large_race_test.dist {
            num_better_large_test += 1;
        }
    }
    println!("Better strategies for large test race: {num_better_large_test}");

    let large_race= Race {
        time: 47847467,
        dist: 207139412091014
    };

    let mut num_better_large = 0;
    for i in 1..large_race.time {
        let travelled = dist_in_time(i, large_race.time);
        if travelled > large_race.dist {
            num_better_large += 1;
        }
    }
    println!("Better strategies for large test race: {num_better_large}");

}
