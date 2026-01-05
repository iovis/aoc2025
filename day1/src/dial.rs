#[derive(Debug, Clone, Copy, PartialEq)]
pub enum Rotate {
    Left(i64),
    Right(i64),
}

#[derive(Debug, Default, PartialEq, Eq)]
pub struct Dial {
    pub number: i64,
}

const DIAL_RANGE: i64 = 100;

impl Dial {
    pub fn new(number: i64) -> Self {
        Self { number }
    }

    pub fn rotate(&mut self, rotation: Rotate) {
        match rotation {
            Rotate::Left(number) => self.left(number),
            Rotate::Right(number) => self.right(number),
        };
    }

    pub fn is_zero(&self) -> bool {
        self.number == 0
    }

    pub fn left(&mut self, number: i64) -> &mut Self {
        self.number = (self.number - number).rem_euclid(DIAL_RANGE);
        self
    }

    pub fn right(&mut self, number: i64) -> &mut Self {
        self.number = (self.number + number).rem_euclid(DIAL_RANGE);
        self
    }
}

impl std::fmt::Display for Dial {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.number)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn left_test() {
        assert_eq!(Dial { number: 50 }.left(68), &mut Dial { number: 82 });
        assert_eq!(Dial { number: 82 }.left(30), &mut Dial { number: 52 });
        assert_eq!(Dial { number: 0 }.left(5), &mut Dial { number: 95 });
        assert_eq!(Dial { number: 55 }.left(55), &mut Dial { number: 0 });
        assert_eq!(Dial { number: 0 }.left(1), &mut Dial { number: 99 });
        assert_eq!(Dial { number: 99 }.left(99), &mut Dial { number: 0 });
    }

    #[test]
    fn right_test() {
        assert_eq!(Dial { number: 52 }.right(18), &mut Dial { number: 70 });
        assert_eq!(Dial { number: 52 }.right(48), &mut Dial { number: 0 });
        assert_eq!(Dial { number: 95 }.right(60), &mut Dial { number: 55 });
        assert_eq!(Dial { number: 95 }.right(99), &mut Dial { number: 94 });
    }
}
