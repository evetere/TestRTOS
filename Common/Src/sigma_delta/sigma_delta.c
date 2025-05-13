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
}

void sigma_delta_tick() {
	bool c = converter_state.hw.read_comparator();
	converter_state.hw.write_dac(c);
	if (converter_state.counter < 1024) {
		int delta = (1 - c);
		converter_state.result += delta;
		converter_state.counter++;
	}
}

float sigma_delta_result() {
	return 5.0 * converter_state.result / converter_state.counter;
}

int sigma_delta_raw_result() {
	return converter_state.result;
}

bool sigma_delta_ended() {
	return converter_state.counter == 1024;
}

static sigma_delta_operations sigma_delta_operations_bindings = {
		.start_conversion = sigma_delta_start_conversion,
		.result = sigma_delta_result,
		.raw_result = sigma_delta_raw_result,
		.tick = sigma_delta_tick,
		.ended = sigma_delta_ended
};

sigma_delta_operations init_sigma_delta(
		sigma_delta_hw_operations hw) {
	converter_state.hw = hw;
	return sigma_delta_operations_bindings;
}

sigma_delta_operations get_sigma_delta() {
	return sigma_delta_operations_bindings;
}

