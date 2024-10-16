#include "sigma_delta/sigma_delta_hw.h"

#include <stdio.h>

#define V_REF 2.5

#define V_IN 3.0

#define R 47E3
#define C 100E-9

/*
 * This function updates the voltage in the capacitor after the dac output is set
 */
void sigma_delta_hw_write_dac(bool b) {
	// TODO write to GPIO
}

bool sigma_delta_hw_read_comparator() {
	bool c = false;
	// TODO read GPIO
	return c;
}

static sigma_delta_hw_operations sigma_delta_hw_operations_bindings =
		{
				.read_comparator = sigma_delta_hw_read_comparator,
				.write_dac = sigma_delta_hw_write_dac,
		};

sigma_delta_hw_operations init_sigma_delta_hw() {
	return sigma_delta_hw_operations_bindings;
}
