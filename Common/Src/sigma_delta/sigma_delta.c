/*
 * sigma-delta.c
 *
 *  Created on: Oct 13, 2024
 *      Author: evetere
 *  See https://ww1.microchip.com/downloads/en/AppNotes/00700a.pdf
 */
#include <stdio.h>
#include "sigma_delta/sigma_delta.h"

static struct {
	int counter;
	int result;
	sigma_delta_hw_operations hw;
} converter_state;

void sigma_delta_start_conversion() {
	converter_state.counter = 0;
	converter_state.result = 0;

	while (converter_state.counter < 1024) {
		if (converter_state.hw.read_comparator()) {
			converter_state.hw.write_dac(true);
		} else {
			converter_state.hw.write_dac(false);
			converter_state.result++;
		}
		converter_state.counter++;
	}

}

void sigma_delta_idle() {
	bool c = converter_state.hw.read_comparator();
	converter_state.hw.write_dac(c);
}

float sigma_delta_result() {
	return 5.0 * converter_state.result / converter_state.counter;
}

static sigma_delta_operations sigma_delta_operations_bindings = {
		.start_conversion = sigma_delta_start_conversion,
		.result = sigma_delta_result,
		.idle = sigma_delta_idle
};

sigma_delta_operations init_sigma_delta(
		sigma_delta_hw_operations hw) {
	converter_state.hw = hw;

	return sigma_delta_operations_bindings;
}

