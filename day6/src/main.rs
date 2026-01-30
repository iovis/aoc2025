fn main() {
    tracing_subscriber::fmt::init();

    let input = include_str!("input.txt");

    println!("p1 = {:?}", p1(input));
    println!("p2 = {:?}", p2(input));
}

fn p1(input: &str) -> u64 {
    let mut problems: Vec<Vec<u64>> = vec![];
    let mut operators: Vec<&str> = vec![];

    for (i, line) in input.lines().enumerate() {
        for (j, element) in line.split_whitespace().enumerate() {
            if let Ok(number) = element.parse() {
                // Store the numbers as columns
                if i == 0 {
                    // first line has to initialize all the columns
                    problems.push(vec![number]);
                } else {
                    problems[j].push(number);
                }
            } else {
                operators.push(element);
            }
        }
    }

    tracing::debug!(?problems);
    tracing::debug!(?operators);

    operators
        .iter()
        .enumerate()
        .map(|(i, &operation)| match operation {
            "*" => problems[i].iter().product::<u64>(),
            "+" => problems[i].iter().sum(),
            _ => panic!("don't panic!"),
        })
        .sum()
}

fn p2(input: &str) -> u64 {
    let mut problems: Vec<Vec<u8>> = vec![];
    let mut operators: Vec<u8> = vec![];

    // parse problem
    for line in input.lines() {
        let line = line.as_bytes();
        match line[0] {
            b'*' | b'+' => line.clone_into(&mut operators),
            _ => problems.push(line.to_owned()),
        }
    }

    debug_line(&operators);
    for problem in &problems {
        debug_line(problem);
    }

    // walk operators line to define grids
    let mut operator_indices: Vec<usize> = vec![];

    for (i, char) in operators.iter().enumerate() {
        match char {
            b'*' | b'+' => operator_indices.push(i),
            _ => (),
        }
    }

    tracing::debug!(?operator_indices);

    // calculate grids
    let mut op_iter = operator_indices.into_iter().peekable();
    let mut total = 0;

    while let Some(start) = op_iter.next() {
        let end = op_iter.peek().copied().unwrap_or(operators.len() + 1) - 1;

        let operation = operators[start];
        let mut numbers: Vec<u64> = vec![];

        // parse every column
        for j in start..end {
            let mut number: Vec<u8> = vec![];

            #[allow(clippy::needless_range_loop)]
            for i in 0..problems.len() {
                if problems[i][j] != b' ' {
                    number.push(problems[i][j]);
                }
            }

            debug_line(&number);
            let number = std::str::from_utf8(&number).unwrap().parse().unwrap();
            numbers.push(number);
        }

        tracing::debug!(?numbers);

        total += match operation {
            b'*' => numbers.iter().product::<u64>(),
            b'+' => numbers.iter().sum(),
            _ => panic!("keep calm!"),
        };

        tracing::debug!(?total);
    }

    total
}

fn debug_line(line: &[u8]) {
    tracing::debug!("{}", std::str::from_utf8(line).unwrap());
}

#[cfg(test)]
mod tests {
    use super::*;
    use pretty_assertions::assert_eq;

    const INPUT: &str = include_str!("input_test.txt");

    #[test]
    fn p1_test() {
        tracing_subscriber::fmt::init();

        assert_eq!(p1(INPUT), 4_277_556);
    }

    #[test]
    fn p2_test() {
        tracing_subscriber::fmt::init();

        assert_eq!(p2(INPUT), 3_263_827);
    }
}
