package main

import "core:fmt"
import "core:strings"
import "core:testing"

main :: proc() {
	input :: #load("./input.txt", string)
	fmt.println("p1 =", p1(input))
}

p1 :: proc(input: string) -> uint {
	lines := input
	dial := dial_new(50)
	total: uint = 0

	for line in strings.split_lines_iterator(&lines) {
		number, ok := parse(line)
		assert(ok)

		if dial_rotate(&dial, number) == 0 {
			total += 1
		}
	}

	return total
}

@(test)
p1_test :: proc(t: ^testing.T) {
	input :=
		"L68\n" +
		"L30\n" +
		"R48\n" +
		"L5\n" +
		"R60\n" +
		"L55\n" +
		"L1\n" +
		"L99\n" +
		"R14\n" +
		"L82\n"

	testing.expect_value(t, p1(input), 3)
}
