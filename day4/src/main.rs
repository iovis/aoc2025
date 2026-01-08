fn main() {
    tracing_subscriber::fmt::init();

    let input = include_str!("input.txt");

    println!("p1 = {:?}", p1(input));
    println!("p2 = {:?}", p2(input));
}

fn p1(input: &str) -> usize {
    let grid: Vec<Vec<u8>> = input.lines().map(|line| line.as_bytes().to_vec()).collect();
    let rows = grid.len();
    let cols = grid[0].len();
    let mut count = 0;

    for i in 0..rows {
        for j in 0..cols {
            if grid[i][j] == b'@' {
                if can_be_accessed(&grid, (i, j)) {
                    count += 1;
                }
            }
        }
    }

    count
}

fn can_be_accessed(grid: &Vec<Vec<u8>>, (i, j): (usize, usize)) -> bool {
    let rows = grid.len() as i32;
    let cols = grid[0].len() as i32;
    let mut count = 0;

    #[rustfmt::skip]
    let directions = [
        (-1, -1), (-1,  0), (-1,  1),
        ( 0, -1),           ( 0,  1),
        ( 1, -1), ( 1,  0), ( 1,  1),
    ];

    for (h, v) in directions {
        let ii = i as i32 + h;
        let jj = j as i32 + v;

        if ii < 0 || ii >= rows {
            continue;
        }

        if jj < 0 || jj >= cols {
            continue;
        }

        if grid[ii as usize][jj as usize] == b'@' {
            count += 1;
        }
    }

    count < 4
}

fn p2(input: &str) -> usize {
    let mut grid: Vec<Vec<u8>> = input.lines().map(|line| line.as_bytes().to_vec()).collect();
    let rows = grid.len();
    let cols = grid[0].len();

    loop {
        let mut count = 0;

        for i in 0..rows {
            for j in 0..cols {
                if grid[i][j] == b'@' {
                    if can_be_accessed(&grid, (i, j)) {
                        grid[i][j] = b'x';
                        count += 1;
                    }
                }
            }
        }

        if count == 0 {
            break;
        }
    }

    grid.iter().flatten().filter(|&&char| char == b'x').count()
}

#[cfg(test)]
mod tests {
    use super::*;
    use pretty_assertions::assert_eq;

    #[test]
    fn p1_test() {
        let input = indoc::indoc! {"
            ..@@.@@@@.
            @@@.@.@.@@
            @@@@@.@.@@
            @.@@@@..@.
            @@.@@@@.@@
            .@@@@@@@.@
            .@.@.@.@@@
            @.@@@.@@@@
            .@@@@@@@@.
            @.@.@@@.@.
        "};

        assert_eq!(p1(input), 13);
    }

    #[test]
    fn p2_test() {
        let input = indoc::indoc! {"
            ..@@.@@@@.
            @@@.@.@.@@
            @@@@@.@.@@
            @.@@@@..@.
            @@.@@@@.@@
            .@@@@@@@.@
            .@.@.@.@@@
            @.@@@.@@@@
            .@@@@@@@@.
            @.@.@@@.@.
        "};

        assert_eq!(p2(input), 43);
    }
}
