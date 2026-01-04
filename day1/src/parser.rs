use nom::IResult;
use nom::Parser;
use nom::character::complete::{i64, one_of};
use nom::combinator::all_consuming;

use crate::Rotate;

pub fn parse(input: &str) -> Rotate {
    let (_rest, rotation) = parse_rotation(input).expect("All rotations should be valid");

    rotation
}

fn parse_rotation(input: &str) -> IResult<&str, Rotate> {
    all_consuming(
        (one_of("LR"), i64).map(|(direction, number)| match direction {
            'L' => Rotate::Left(number),
            'R' => Rotate::Right(number),
            _ => unreachable!("one_of(\"LR\") only returns L or R"),
        }),
    )
    .parse(input)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn parse_line_test() {
        assert_eq!(parse("L68"), Rotate::Left(68));
        assert_eq!(parse("L99"), Rotate::Left(99));
        assert_eq!(parse("R5"), Rotate::Right(5));
        assert_eq!(parse("R14"), Rotate::Right(14));
    }
}
