use std::collections::HashMap;

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
    let grid: Vec<Vec<u8>> = input
        .lines()
        .map(|line| line.as_bytes().to_owned())
        .collect();

    // 1. keep a cursor of the current pointer
    // 2. traverse down like if it were a tree with DFS, keeping track of each time it goes
    //    left and right, calling the traversing function recursively
    // 3. add 1 each time you reach the end, returning from the function
    //
    // NOTE: keep a memo to not recompute solved problems
    let start: (usize, usize) = (0, grid[0].iter().position(|&x| x == b'S').unwrap());
    let mut memo = HashMap::new();
    traverse_grid(&grid, start, &mut memo)
}

fn traverse_grid(
    grid: &[Vec<u8>],
    start: (usize, usize),
    memo: &mut HashMap<(usize, usize), u64>,
) -> u64 {
    if let Some(&result) = memo.get(&start) {
        return result;
    }

    let (i, j) = start;
    let mut timelines = 0;

    tracing::debug!("{:?}", (i, j));
    if i == grid.len() - 1 {
        memo.insert(start, 1);
        return 1;
    }

    match grid[i + 1][j] {
        b'^' => {
            // go left
            if j > 0 {
                timelines += traverse_grid(grid, (i + 1, j - 1), memo);
            }

            // go right
            if j < grid[i].len() - 1 {
                timelines += traverse_grid(grid, (i + 1, j + 1), memo);
            }
        }
        _ => {
            timelines += traverse_grid(grid, (i + 1, j), memo);
        }
    }

    memo.insert(start, timelines);
    timelines
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
        let _ = tracing_subscriber::fmt::try_init();
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
    fn p2_test() {
        let _ = tracing_subscriber::fmt::try_init();
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

        assert_eq!(p2(input), 40);
    }
}
