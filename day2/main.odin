package main

import "core:fmt"
import "core:mem"
import "core:strconv"
import "core:strings"
import "core:testing"

main :: proc() {
	input :: #load("./input.txt", string)
	fmt.println("p1 =", p1(input))
}

Range :: struct {
	start: uint,
	end:   uint,
}

p1 :: proc(input: string) -> uint {
	total: uint = 0
	ranges := strings.trim_right(input, "\n")

	for range_str in strings.split_iterator(&ranges, ",") {
		range := parse_range(range_str)

		for id in range.start ..= range.end {
			if !is_valid_id(id) {
				total += id
			}
		}
	}

	return total
}

parse_range :: proc(range: string) -> Range {
	start_str, _, end_str := strings.partition(range, "-")

	start, ok := strconv.parse_uint(start_str)
	assert(ok)

	end, ok2 := strconv.parse_uint(end_str)
	assert(ok2)

	return Range{start, end}
}

is_valid_id :: proc(id: uint) -> bool {
	buf: [64]byte
	id_str := strconv.write_uint(buf[:], u64(id), 10)

	if len(id_str) % 2 != 0 do return true

	mid := len(id_str) / 2
	return id_str[:mid] != id_str[mid:]
}

@(test)
is_valid_id_test :: proc(t: ^testing.T) {
	testing.expect(t, is_valid_id(101) == true)
	testing.expect(t, is_valid_id(123123) == false)
	testing.expect(t, is_valid_id(1188511880) == true)
}

@(test)
p1_test :: proc(t: ^testing.T) {
	input :=
		"11-22,95-115,998-1012,1188511880-1188511890," +
		"222220-222224,1698522-1698528,446443-446449," +
		"38593856-38593862,565653-565659,824824821-824824827," +
		"2121212118-2121212124\n"

	testing.expect_value(t, p1(input), 1227775554)
}
