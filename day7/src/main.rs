fn main() {
    tracing_subscriber::fmt::init();

    let input = include_str!("input.txt");

    println!("p1 = {:?}", p1(input));
    println!("p2 = {:?}", p2(input));
}

fn p1(input: &str) -> u64 {
    let mut splits = 0;
    let mut grid: Vec<Vec<u8>> = input
        .lines()
        .map(|line| line.as_bytes().to_owned())
        .collect();

    for i in 0..grid.len() {
        debug_line(&grid[i]);

        // bail out on the last line
        if i == grid.len() - 1 {
            break;
        }

        for j in 0..grid[i].len() {
            match grid[i][j] {
                b'S' => {
                    grid[i + 1][j] = b'|';
                }
                b'|' => {
                    if grid[i + 1][j] != b'^' {
                        grid[i + 1][j] = b'|';
                        continue;
                    }

                    let mut split = false;

                    if j > 0 && grid[i + 1][j - 1] != b'|' {
                        grid[i + 1][j - 1] = b'|';
                        split = true;
                    }

                    if j < grid[i].len() - 1 && grid[i + 1][j + 1] != b'|' {
                        grid[i + 1][j + 1] = b'|';
                        split = true;
                    }

                    if split {
                        splits += 1;
                    }
                }
                _ => (),
            }
        }
    }

    splits
}

fn p2(input: &str) -> u64 {
    todo!()
}

fn debug_line(line: &[u8]) {
    tracing::debug!("{}", std::str::from_utf8(line).unwrap());
}

#[cfg(test)]
mod tests {
    use super::*;
    use pretty_assertions::assert_eq;

    #[test]
    fn p1_test() {
        tracing_subscriber::fmt::init();
        let input = indoc::indoc! {"
            .......S.......
            ...............
            .......^.......
            ...............
            ......^.^......
            ...............
            .....^.^.^.....
            ...............
            ....^.^...^....
            ...............
            ...^.^...^.^...
            ...............
            ..^...^.....^..
            ...............
            .^.^.^.^.^...^.
            ...............
        "};

        assert_eq!(p1(input), 21);
    }

    #[test]
    #[ignore = "pending"]
    fn p2_test() {
        tracing_subscriber::fmt::init();
        let input = indoc::indoc! {"
            .......S.......
            ...............
            .......^.......
            ...............
            ......^.^......
            ...............
            .....^.^.^.....
            ...............
            ....^.^...^....
            ...............
            ...^.^...^.^...
            ...............
            ..^...^.....^..
            ...............
            .^.^.^.^.^...^.
            ...............
        "};

        assert_eq!(p2(input), 21);
    }
}
