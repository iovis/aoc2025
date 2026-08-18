package main

import "core:fmt"
import "core:slice"
import "core:strings"
import "core:testing"

main :: proc() {
	input :: #load("./input.txt", string)
	fmt.println("p1 =", p1(input))
	fmt.println("p2 =", p2(input))
}

p1 :: proc(input: string) -> u64 {
	total: u64 = 0
	lines := input

	for line in strings.split_lines_iterator(&lines) {
		total += max_joltage(line, 2)
	}

	return total
}

@(test)
p1_test :: proc(t: ^testing.T) {
	input := "987654321111111\n" + "811111111111119\n" + "234234234234278\n" + "818181911112111\n"

	testing.expect_value(t, p1(input), 357)
}

p2 :: proc(input: string) -> u64 {
	total: u64 = 0
	lines := input

	for line in strings.split_lines_iterator(&lines) {
		total += max_joltage(line, 12)
	}

	return total
}

max_joltage :: proc(line: string, n: uint) -> u64 {
	assert(uint(len(line)) > n)
	bytes := transmute([]u8)line
	joltage: u64 = 0

	start := 0
	for i := n; i > 0; i -= 1 {
		end := uint(len(bytes)) - i + 1
		idx := slice.max_index(bytes[start:end]) + start
		digit := u64(bytes[idx] - '0')

		joltage = 10 * joltage + digit

		start = idx + 1
	}

	return joltage
}

@(test)
max_joltage_n_tests :: proc(t: ^testing.T) {
	testing.expect_value(t, max_joltage("987654321111111", 12), 987654321111)
	testing.expect_value(t, max_joltage("811111111111119", 12), 811111111119)
	testing.expect_value(t, max_joltage("234234234234278", 12), 434234234278)
	testing.expect_value(t, max_joltage("818181911112111", 12), 888911112111)
}

@(test)
p2_test :: proc(t: ^testing.T) {
	input := "987654321111111\n" + "811111111111119\n" + "234234234234278\n" + "818181911112111\n"

	testing.expect_value(t, p2(input), 3121910778619)
}
