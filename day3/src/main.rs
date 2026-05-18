fn main() {
    tracing_subscriber::fmt::init();

    let input = include_str!("../input.txt");

    println!("p1 = {:?}", p1(input));
    println!("p2 = {:?}", p2(input));
}

// 2 batteries
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

// 12 batteries
fn p2(input: &str) -> u64 {
    input
        .lines()
        .map(|line| {
            let line = line.as_bytes();
            let mut indices = vec![];

            max_recursive(line, 0, 12, &mut indices);

            let binding = indices.iter().map(|&i| line[i]).collect::<Vec<u8>>();
            let result = std::str::from_utf8(&binding).unwrap();

            tracing::info!(line = %std::str::from_utf8(line).unwrap());
            tracing::debug!(?indices);

            result.parse::<u64>().unwrap()
        })
        .inspect(|x| tracing::debug!(result = x))
        .sum()
}

// XXXXX XXXXX XXXXX XXXXX
// ╰────────╯
// 0 + (20 - (0+1)) - (12 - 1) = 8 => gotta leave a window of at least 11 characters
//
// XXXMX XXXXX XXXXX XXXXX
//     ╰─────╯
// if i = 3 => 16 spaces left for 11 digits (20 - (i+1))
// 4 + (20 - (4+1)) - (11 - 1) = 9 => gotta leave a window of at least 10 characters
//
// end = start + (arr.len() - (start+1)) - (chars_left - 1) => till where to look for max char
fn max_recursive(array: &[u8], start: usize, chars_left: usize, indices: &mut Vec<usize>) {
    if chars_left == 0 {
        return;
    }

    let end = start + (array.len() - (start + 1)) - (chars_left - 1);
    let mut max_idx = 0;
    let mut max_val = 0u8;

    #[allow(clippy::needless_range_loop)]
    for i in start..=end {
        if array[i] > max_val {
            max_val = array[i];
            max_idx = i;
        }
    }

    indices.push(max_idx);

    max_recursive(array, max_idx + 1, chars_left - 1, indices);
}

#[cfg(test)]
mod tests {
    use super::*;
    use pretty_assertions::assert_eq;

    #[test]
    fn p1_test() {
        let _ = tracing_subscriber::fmt::try_init();
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
        let _ = tracing_subscriber::fmt::try_init();
        let input = "5966546654588755548354591946657465889859765969657756889447669666979883895847755487857956955568577855";

        assert_eq!(p1(input), 99);
    }

    #[test]
    fn p2_test() {
        let _ = tracing_subscriber::fmt::try_init();
        let input = indoc::indoc! {"
            987654321111111
            811111111111119
            234234234234278
            818181911112111
        "};

        assert_eq!(p2(input), 3_121_910_778_619);
    }

    #[test]
    fn max_recursive_test() {
        let input = b"987654321111111";
        let mut indices = vec![];
        max_recursive(input, 0, 12, &mut indices);
        let binding = indices.iter().map(|&i| input[i]).collect::<Vec<u8>>();
        let result = std::str::from_utf8(&binding).unwrap();

        assert_eq!(result, "987654321111");

        let input = b"811111111111119";
        let mut indices = vec![];
        max_recursive(input, 0, 12, &mut indices);
        let binding = indices.iter().map(|&i| input[i]).collect::<Vec<u8>>();
        let result = std::str::from_utf8(&binding).unwrap();

        assert_eq!(result, "811111111119");

        let input = b"234234234234278";
        let mut indices = vec![];
        max_recursive(input, 0, 12, &mut indices);
        let binding = indices.iter().map(|&i| input[i]).collect::<Vec<u8>>();
        let result = std::str::from_utf8(&binding).unwrap();

        assert_eq!(result, "434234234278");

        let input = b"818181911112111";
        let mut indices = vec![];
        max_recursive(input, 0, 12, &mut indices);
        let binding = indices.iter().map(|&i| input[i]).collect::<Vec<u8>>();
        let result = std::str::from_utf8(&binding).unwrap();

        assert_eq!(result, "888911112111");
    }
}
