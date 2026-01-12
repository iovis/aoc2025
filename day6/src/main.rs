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
            123 328  51 64
            45 64  387 23
            6 98  215 314
            *   +   *   +
        "};

        assert_eq!(p1(input), 4277556);
    }

    #[test]
    fn p2_test() {
        let input = indoc::indoc! {"
            123 328  51 64
            45 64  387 23
            6 98  215 314
            *   +   *   +
        "};

        // assert_eq!(p2(input), 4277556);
    }
}
