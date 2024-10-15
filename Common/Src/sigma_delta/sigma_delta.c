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
	struct sigma_delta_hw_operations hw;
} converter_state;

void sigma_delta_start_conversion() {
	converter_state.counter = 0;
	converter_state.result = 0;

	converter_state.hw.engage(false);

	while (converter_state.counter < 1024) {
		if (converter_state.hw.read_comparator()) {
			converter_state.hw.write_dac(true);
		} else {
			converter_state.hw.write_dac(false);
			converter_state.result++;
		}
		converter_state.counter++;
	}
	converter_state.hw.engage(true);

}

void sigma_delta_idle() {
	converter_state.hw.read_comparator();
}

float sigma_delta_result() {
	return 5.0 * converter_state.result / converter_state.counter;
}

static struct sigma_delta_operations sigma_delta_operations_bindings = {
		.start_conversion = sigma_delta_start_conversion,
		.result = sigma_delta_result,
		.idle = sigma_delta_idle
};

struct sigma_delta_operations init_sigma_delta(
		struct sigma_delta_hw_operations hw) {
	converter_state.hw = hw;
	converter_state.hw.engage(1);

	return sigma_delta_operations_bindings;
}

