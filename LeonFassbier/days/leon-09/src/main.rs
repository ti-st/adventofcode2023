use std::fs;

fn main() {
    // test_vec(&vec![0, 3, 6, 9, 12]);
    // test_vec(&vec![9, 12]);
    // test_vec(&vec![0]);
    // test_vec(&vec![]);
    let filepath = "input.txt";

    let file_input = fs::read_to_string(filepath).unwrap();
    let input_lines = file_input.lines();
    let mut measurements: Vec<Vec<i32>> = Vec::new();

    for line in input_lines {
        let mut series: Vec<i32> = Vec::new();
        for s in line.split(' ') {
            let val = i32::from_str_radix(s, 10).expect("Could not parse into integer");
            series.push(val);
        }
        measurements.push(series);
    }

    let mut predictions: Vec<i32> = Vec::new();
    let mut extrapolations: Vec<i32> = Vec::new();
    for series in measurements {
        let mut diff_last_values: Vec<i32> = Vec::new(); // vec![series];
        let mut diff_first_values: Vec<i32> = Vec::new(); // vec![series];
        let mut cur_series = series;
        // diff_last_values.push(cur_series.last().unwrap().clone());
        // diff_first_values.push(cur_series.first().unwrap().clone());

        while cur_series.iter().any(|n| n.clone() != 0) {
            // let cur_diff = diffs.last().unwrap();
            diff_last_values.push(cur_series.last().unwrap().clone());
            diff_first_values.push(cur_series.first().unwrap().clone());
            let new_diff = differentiate(&cur_series);
            cur_series = new_diff;
        }


        let prediction: i32 = diff_last_values.into_iter().sum();
        println!("Prediction is {prediction}");
        predictions.push(prediction);
        let mut diff_extrapolation = 0;

        for i in 1..(diff_first_values.len() + 1)  { 
            let i_rev = diff_first_values.len() - i;
            let first_diff_value = diff_first_values[i_rev];
            // first_diff_value - new_extrapolation  = cur_extrapolation -> ...
            diff_extrapolation = first_diff_value - diff_extrapolation;
        }
        println!("Reverse extrapolation is {diff_extrapolation}");
        extrapolations.push(diff_extrapolation);
    }

    let prediction_sum: i32 = predictions.iter().sum();
    println!("Total prediction sum is {prediction_sum}");
    
    let extrapolation_sum: i32 = extrapolations.iter().sum();
    println!("Total extrapolation sum is {extrapolation_sum}");
}

fn differentiate(seq: &Vec<i32>) -> Vec<i32> {
    if seq.len() == 0 {
        return Vec::new();
    }

    let mut diff: Vec<i32> = Vec::with_capacity(seq.len() - 1);

    for i in 0..(seq.len() - 1) {
        diff.push(seq[i + 1] - seq[i]);
    }

    diff
}

// fn interpolate(seq_to_interpolate: &Vec<i32>, diff: i32) -> i32 {

// }

// fn test_vec(to_test: &Vec<i32>) {
//     let diff_vec1 = differentiate(to_test);
//     println!("{:?} -> {:?}", to_test, diff_vec1);
// }
