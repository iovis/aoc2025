use std::ops::RangeInclusive;
mod parser;
use parser::parse;

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
    let (mut ranges, _) = parse(input);
    ranges.sort_unstable_by_key(|range| *range.start());

    merge_sorted_ranges(&ranges)
        .iter()
        .map(|range| range.end() - range.start() + 1)
        .sum()
}

fn merge_sorted_ranges(ranges: &[RangeInclusive<u64>]) -> Vec<RangeInclusive<u64>> {
    let mut merged: Vec<RangeInclusive<u64>> = Vec::with_capacity(ranges.len());

    for range in ranges {
        if let Some(last) = merged.last_mut()
            && range.start() <= last.end()
        {
            let new_start = *last.start();
            let new_end = *last.end().max(range.end());

            *last = new_start..=new_end;
        } else {
            merged.push(range.clone());
        }
    }

    merged
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

        assert_eq!(p2(input), 14);
    }
}
