package main

import "core:testing"

DIAL_RANGE :: 100

Dial :: struct {
	number: int,
}

dial_new :: proc(number: int) -> Dial {
	return Dial{number}
}

dial_rotate :: proc(self: ^Dial, amount: int) -> int {
	self.number += amount
	self.number %= DIAL_RANGE

	if self.number < 0 do self.number += DIAL_RANGE

	return self.number
}

dial_rotate_with_count :: proc(self: ^Dial, amount: int) -> int {
	zeroes := 0

	if self.number == 0 && amount < 0 {
		zeroes = -1
	}

	self.number += amount
	zeroes += abs(self.number / DIAL_RANGE)
	self.number %= DIAL_RANGE

	if self.number < 0 {
		self.number += DIAL_RANGE
		zeroes += 1
	}

	if (self.number == 0 && amount < 0) {
		zeroes += 1
	}

	return zeroes
}

@(test)
dial_rotate_test :: proc(t: ^testing.T) {
	dial := dial_new(52)

	testing.expect_value(t, dial_rotate(&dial, 18), 70)
	testing.expect_value(t, dial_rotate(&dial, 30), 0)
	testing.expect_value(t, dial_rotate(&dial, 95), 95)
	testing.expect_value(t, dial_rotate(&dial, 99), 94)
	testing.expect_value(t, dial_rotate(&dial, 60), 54)
	testing.expect_value(t, dial_rotate(&dial, -54), 0)
	testing.expect_value(t, dial_rotate(&dial, -5), 95)

	dial = dial_new(52)
	testing.expect_value(t, dial_rotate(&dial, 218), 70)

	dial = dial_new(52)
	testing.expect_value(t, dial_rotate(&dial, -218), 34)
}

@(test)
dial_rotate_with_count_test :: proc(t: ^testing.T) {
	dial := dial_new(50)
	testing.expect_value(t, dial_rotate_with_count(&dial, 50), 1)
	testing.expect_value(t, dial.number, 0)

	dial = dial_new(50)
	testing.expect_value(t, dial_rotate_with_count(&dial, -50), 1)
	testing.expect_value(t, dial.number, 0)

	dial = dial_new(0)
	testing.expect_value(t, dial_rotate_with_count(&dial, 1), 0)

	dial = dial_new(0)
	testing.expect_value(t, dial_rotate_with_count(&dial, -1), 0)

	dial = dial_new(50)
	testing.expect_value(t, dial_rotate_with_count(&dial, 203), 2)
	testing.expect_value(t, dial.number, 53)

	dial = dial_new(50)
	testing.expect_value(t, dial_rotate_with_count(&dial, -203), 2)
	testing.expect_value(t, dial.number, 47)

	dial = dial_new(0)
	testing.expect_value(t, dial_rotate_with_count(&dial, 100), 1)

	dial = dial_new(0)
	testing.expect_value(t, dial_rotate_with_count(&dial, -100), 1)

	dial = dial_new(1)
	testing.expect_value(t, dial_rotate_with_count(&dial, -1), 1)

	dial = dial_new(99)
	testing.expect_value(t, dial_rotate_with_count(&dial, 1), 1)
}
