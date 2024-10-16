/*
 * test_sigma_delta.c
 *
 *  Created on: Oct 13, 2024
 *      Author: evetere
 */

#include <stdio.h>
#include <criterion/criterion.h>
#include "sigma_delta/sigma_delta.h"
#include "sigma_delta_fake_hw.h"

sigma_delta_operations sd;
sigma_delta_fake_hw_operations hw;

void setup(void) {
	puts("Init sd");
	sigma_delta_fake_hw_parameters p =
			{
					.v_ref = 2.5,
					.r = 48e3, // the resistors' value
					.c = 100e-9, // the capacitor value
					.dt = 20e-6 // the time between calls to update the dac
			}

	;
	hw = init_sigma_delta_fake_hw(p);
	sd = init_sigma_delta(as_sigma_delta_hw(hw));
}

TestSuite(sigma_delta_test, .init = setup);

Test(sigma_delta_test, convert) {
	for (int i = 0; i < 1000; i++) { // set to idle point
		sd.idle();
	}

	sd.start_conversion();
	printf("result %f\n", sd.result());
	hw.set_v_in(2.0);
	sd.start_conversion();
	printf("result %f\n", sd.result());
}

Test(sigma_delta_test, idle) {
	for (int i = 0; i < 250; i++) {
		sd.idle();
//		printf("%d v= %f\n", i, hw.read_v());
	}

}
