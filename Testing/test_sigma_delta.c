/*
 * test_sigma_delta.c
 *
 *  Created on: Oct 13, 2024
 *      Author: evetere
 */

#include <stdio.h>
#include <criterion/criterion.h>
#include "sigma_delta/sigma_delta.h"
#include "sigma_delta/sigma_delta_hw.h"

struct sigma_delta_operations sd;
struct sigma_delta_hw_operations hw;

void setup(void) {
	puts("Init sd");
	hw = init_sigma_delta_hw();
	sd = init_sigma_delta(hw);
}

TestSuite(sigma_delta_test, .init = setup);

Test(sigma_delta_test, convert) {
	for (int i = 0; i < 1000; i++) { // set to idle point
		sd.idle();
	}
	printf("After idle v= %f\n", hw.read_v());

	sd.start_conversion();
	printf("result %f\n", sd.result());
	cr_assert(sd.result() == 512);

}

Test(sigma_delta_test, idle) {
	for (int i = 0; i < 250; i++) {
		sd.idle();
//		printf("%d v= %f\n", i, hw.read_v());
	}

}
