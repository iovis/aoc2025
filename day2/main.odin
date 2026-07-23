package main

import "core:fmt"
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
	id_str := fast_uint_to_string(buf[:], id)

	if len(id_str) % 2 != 0 do return true

	mid := len(id_str) / 2
	return id_str[:mid] != id_str[mid:]
}

decimal_pairs ::
	"0001020304050607080910111213141516171819" +
	"2021222324252627282930313233343536373839" +
	"4041424344454647484950515253545556575859" +
	"6061626364656667686970717273747576777879" +
	"8081828384858687888990919293949596979899"

/// Use a lookup table to write pairs of characters
// taking 4 characters at a time
fast_uint_to_string :: proc(buf: []byte, number: uint) -> string {
	number := number
	i := len(buf)

	for number > 9999 {
		chunk := number % 10000
		number /= 10000

		i -= 4
		write_pair(&buf[i], chunk / 100) // first 2
		write_pair(&buf[i + 2], chunk % 100) // last 2
	}

	// final cleanup
	switch {
	case number > 999:
		i -= 4
		write_pair(&buf[i], number / 100) // first 2
		write_pair(&buf[i + 2], number % 100) // last 2
	case number > 99:
		i -= 3
		buf[i] = u8('0' + number / 100) // first number
		write_pair(&buf[i + 1], number % 100) // last 2
	case number > 9:
		i -= 2
		write_pair(&buf[i], number)
	case:
		i -= 1
		buf[i] = u8('0' + number)
	}

	return string(buf[i:])
}

write_pair :: proc(ptr: [^]byte, number: uint) {
	assert(number < 100)

	pairs := decimal_pairs
	i := number * 2

	ptr[0] = pairs[i]
	ptr[1] = pairs[i + 1]
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

@(test)
fast_uint_to_string_test :: proc(t: ^testing.T) {
	buf: [64]byte
	testing.expect_value(t, fast_uint_to_string(buf[:], 0), "0")
	testing.expect_value(t, fast_uint_to_string(buf[:], 9), "9")
	testing.expect_value(t, fast_uint_to_string(buf[:], 10), "10")
	testing.expect_value(t, fast_uint_to_string(buf[:], 101), "101")
	testing.expect_value(t, fast_uint_to_string(buf[:], 1234), "1234")
	testing.expect_value(t, fast_uint_to_string(buf[:], 1188511880), "1188511880")
	testing.expect_value(t, fast_uint_to_string(buf[:], 184467440737095), "184467440737095")
}
