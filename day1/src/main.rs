use day1::Dial;
use day1::parser::parse;

fn main() {
    let input = include_str!("input.txt");

    println!("p1 = {:?}", p1(input));
    println!("p2 = {:?}", p2(input));
}

fn p1(input: &str) -> usize {
    let mut dial = Dial::new(50);
    let mut zeroes = 0;

    input.lines().map(parse).for_each(|rotation| {
        dial.rotate(rotation);

        if dial.is_zero() {
            zeroes += 1;
        }
    });

    zeroes
}

fn p2(input: &str) -> usize {
    123
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn p1_test() {
        let input = indoc::indoc! {"
            L68
            L30
            R48
            L5
            R60
            L55
            L1
            L99
            R14
            L82
        "};

        assert_eq!(p1(input), 3);
    }

    #[test]
    fn p2_test() {
        let input = indoc::indoc! {"
            something
        "};

        // assert_eq!(p2(input), 23);
    }
}
