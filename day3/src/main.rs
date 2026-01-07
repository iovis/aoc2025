fn main() {
    tracing_subscriber::fmt::init();

    let input = include_str!("input.txt");

    println!("p1 = {:?}", p1(input));
    // println!("p2 = {:?}", p2(input));
}

fn p1(input: &str) -> u64 {
    input
        .lines()
        .map(|line| {
            let line = line.as_bytes();
            let idx_first = max_index(&line[0..line.len() - 1]);
            let idx_second = max_index(&line[idx_first + 1..line.len()]) + idx_first + 1;

            tracing::info!(line = %std::str::from_utf8(line).unwrap());
            tracing::debug!(idx_first, idx_second);

            std::str::from_utf8(&[line[idx_first], line[idx_second]])
                .unwrap()
                .parse::<u64>()
                .unwrap()
        })
        .inspect(|x| tracing::debug!(result = x))
        .sum()
}

fn max_index(array: &[u8]) -> usize {
    let mut idx = 0;
    let mut max = 0u8;

    for (i, &val) in array.iter().enumerate() {
        if val > max {
            max = val;
            idx = i;
        }
    }

    idx
}

fn p2(input: &str) -> u64 {
    todo!()
}

#[cfg(test)]
mod tests {
    use super::*;
    use pretty_assertions::assert_eq;

    #[test]
    fn p1_test() {
        tracing_subscriber::fmt::init();
        let input = indoc::indoc! {"
            987654321111111
            811111111111119
            234234234234278
            818181911112111
        "};

        assert_eq!(p1(input), 357);
    }

    #[test]
    fn p1_edge_cases_test() {
        tracing_subscriber::fmt::init();
        let input = "5966546654588755548354591946657465889859765969657756889447669666979883895847755487857956955568577855";

        assert_eq!(p1(input), 99);
    }

    #[test]
    fn p2_test() {
        tracing_subscriber::fmt::init();
        let input = indoc::indoc! {"
            987654321111111
            811111111111119
            234234234234278
            818181911112111
        "};

        // assert_eq!(p2(input), 357);
    }
}
