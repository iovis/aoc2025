package main

import "core:fmt"
import "core:log"
import "core:slice"
import "core:strings"
import "core:testing"

main :: proc() {
	input :: #load("./input.txt", string)
	fmt.println("p1 =", p1(input))
}

p1 :: proc(input: string) -> u64 {
	total: u64 = 0
	lines := input

	for line in strings.split_lines_iterator(&lines) {
		log.debug("line:", line)
		total += max_joltage(line)
	}

	return total
}

max_joltage :: proc(line: string) -> u64 {
	assert(len(line) > 1)
	bytes := transmute([]u8)line

	index := slice.max_index(bytes[:len(bytes) - 1])
	first_digit := u64(bytes[index] - '0')
	log.debug("first_digit:", first_digit)

	index = slice.max_index(bytes[index + 1:len(bytes)]) + index + 1
	second_digit := u64(bytes[index] - '0')
	log.debug("second_digit:", second_digit)

	total := 10 * first_digit + second_digit

	log.debug("total:", total)

	return total
}

@(test)
p1_test :: proc(t: ^testing.T) {
	input := "987654321111111\n" + "811111111111119\n" + "234234234234278\n" + "818181911112111\n"

	testing.expect_value(t, p1(input), 357)
}
