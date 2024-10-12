/*
 * test_main.c
 *
 *  Created on: Oct 12, 2024
 *      Author: evetere
 */

#include <criterion/criterion.h>
#include "fibonacci.h"

Test(fibonacci_test, base0) {
	cr_assert(fibonacci(0) == 0);
}

Test(fibonacci_test, base1) {
	cr_assert(fibonacci(1) == 1);
}

Test(fibonacci_test, 2) {
	cr_assert(fibonacci(2) == 1);
}

Test(fibonacci_test, 3) {
	cr_assert(fibonacci(3) == 2);
}

Test(fibonacci_test, 4) {
	cr_assert(fibonacci(4) == 3);
}

Test(fibonacci_test, 5) {
	cr_assert(fibonacci(5) == 5);
}

Test(fibonacci_test, 6) {
	cr_assert(fibonacci(6) == 8);
}
