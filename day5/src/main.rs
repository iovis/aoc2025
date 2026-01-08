mod parser;
use parser::*;

fn main() {
    tracing_subscriber::fmt::init();

    let input = include_str!("input.txt");

    println!("p1 = {:?}", p1(input));
    println!("p2 = {:?}", p2(input));
}

fn p1(input: &str) -> usize {
    let (ranges, ingredients) = parse(input);

    ingredients
        .iter()
        .filter(|id| ranges.iter().any(|range| range.contains(id)))
        .count()
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
        let input = indoc::indoc! {"
            3-5
            10-14
            16-20
            12-18

            1
            5
            8
            11
            17
            32
        "};

        assert_eq!(p1(input), 3);
    }

    #[test]
    fn p2_test() {
        let input = indoc::indoc! {"
            3-5
            10-14
            16-20
            12-18

            1
            5
            8
            11
            17
            32
        "};

        // assert_eq!(p2(input), 3);
    }
}

