use day2::parse;

fn main() {
    let input = include_str!("input.txt");

    println!("p1 = {:?}", p1(input));
    println!("p2 = {:?}", p2(input));
}

fn p1(input: &str) -> u64 {
    parse(input)
        .iter()
        .flat_map(|range| range.clone().filter(|&a| !is_valid_id(a)))
        .sum()
}

fn is_valid_id(id: u64) -> bool {
    let binding = id.to_string();
    let id = binding.as_bytes();

    if !id.len().is_multiple_of(2) {
        return true;
    }

    let first_half = 0..id.len() / 2;
    let second_half = id.len() / 2..id.len();

    for (i, j) in first_half.clone().zip(second_half) {
        if id[i] != id[j] {
            return true;
        }
    }

    false
}

fn p2(input: &str) -> u64 {
    parse(input)
        .iter()
        .flat_map(|range| range.clone().filter(|&a| !is_valid_id_slow(a)))
        // .inspect(|x| eprintln!("{x:?}"))
        .sum()
}

fn is_valid_id_slow(id: u64) -> bool {
    let binding = id.to_string();
    let id = binding.as_bytes();

    for chunk_size in 1..=id.len() / 2 {
        if id
            .chunks(chunk_size)
            .all(|chunk| chunk == &id[0..chunk_size])
        {
            return false;
        }
    }

    true
}

#[cfg(test)]
mod tests {
    use super::*;
    use pretty_assertions::assert_eq;

    #[test]
    fn p1_test() {
        let input = "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124";

        assert_eq!(p1(input), 1227775554);
    }

    #[test]
    fn p2_test() {
        let input = "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124";

        assert_eq!(p2(input), 4174379265);
    }

    #[test]
    fn is_valid_id_test() {
        assert_eq!(is_valid_id(123123), false);
        assert_eq!(is_valid_id(101), true);
        assert_eq!(is_valid_id(1188511880), true);
    }

    #[test]
    fn is_valid_id_slow_test() {
        assert_eq!(is_valid_id_slow(123123), false, "123123");
        assert_eq!(is_valid_id_slow(101), true, "101");
        assert_eq!(is_valid_id_slow(1188511880), true, "1188511880");
        assert_eq!(is_valid_id_slow(12341234), false, "12341234");
        assert_eq!(is_valid_id_slow(123123123), false, "123123123");
        assert_eq!(is_valid_id_slow(1212121212), false, "1212121212");
        assert_eq!(is_valid_id_slow(1111111111), false, "1111111111");
    }
}
