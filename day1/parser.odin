package main

import "core:strconv"
import "core:testing"

parse :: proc(line: string) -> (int, bool) {
	sign := 0

	switch line[0] {
	case 'L':
		sign = -1
	case 'R':
		sign = 1
	case:
		return 0, false
	}

	n, ok := strconv.parse_int(line[1:])

	return sign * n, ok
}


@(test)
parse_test :: proc(t: ^testing.T) {
	result, ok := parse("L68")
	testing.expect_value(t, result, -68)
	testing.expect(t, ok)

	result, ok = parse("L99")
	testing.expect_value(t, result, -99)
	testing.expect(t, ok)

	result, ok = parse("R5")
	testing.expect_value(t, result, 5)
	testing.expect(t, ok)

	result, ok = parse("R14")
	testing.expect_value(t, result, 14)
	testing.expect(t, ok)
}
