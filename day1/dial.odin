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
