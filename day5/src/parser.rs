use std::ops::RangeInclusive;

use nom::bytes::complete::tag;
use nom::character::complete::{line_ending, u64};
use nom::multi::separated_list1;
use nom::sequence::{pair, separated_pair};
use nom::{IResult, Parser};

pub fn parse(input: &str) -> (Vec<RangeInclusive<u64>>, Vec<u64>) {
    let (_rest, (ranges, ingredients)) = separated_pair(
        separated_list1(line_ending, parse_range_line),
        pair(line_ending, line_ending),
        separated_list1(line_ending, parse_ingredient_line),
    )
    .parse(input)
    .unwrap();

    (ranges, ingredients)
}

fn parse_ingredient_line(input: &str) -> IResult<&str, u64> {
    u64.parse(input)
}

fn parse_range_line(input: &str) -> IResult<&str, RangeInclusive<u64>> {
    (u64, tag("-"), u64).map(|(a, _, b)| a..=b).parse(input)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn parse_range_line_test() {
        assert_eq!(parse_range_line("11-22"), Ok(("", 11..=22)));
    }

    #[test]
    fn parse_test() {
        let input = indoc::indoc! {"
            3-5
            10-14

            1
            5
        "};

        assert_eq!(parse(input), (vec![3..=5, 10..=14], vec![1, 5]));
    }
}
