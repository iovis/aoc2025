use std::ops::RangeInclusive;

use nom::multi::separated_list1;
use nom::{
    IResult, Parser, bytes::complete::tag, character::complete::u64, combinator::map,
    sequence::separated_pair,
};

pub fn parse(input: &str) -> Vec<RangeInclusive<u64>> {
    let (_rest, ranges) = separated_list1(tag(","), parse_range).parse(input).unwrap();

    ranges
}

fn parse_range(input: &str) -> IResult<&str, RangeInclusive<u64>> {
    map(separated_pair(u64, tag("-"), u64), |(a, b)| a..=b).parse(input)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn parse_range_test() {
        assert_eq!(parse_range("11-22"), Ok(("", 11..=22)));
        assert_eq!(
            parse_range("1188511880-1188511890"),
            Ok(("", 1188511880..=1188511890))
        );
    }

    #[test]
    fn parse_test() {
        assert_eq!(
            parse("11-22,95-115,998-1012"),
            vec![11..=22, 95..=115, 998..=1012]
        );
    }
}
