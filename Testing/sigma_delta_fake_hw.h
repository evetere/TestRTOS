/*
 * sigma_delta_hw.h
 *
 *  Created on: Oct 13, 2024
 *      Author: evetere
 */

#ifndef INC_SIGMA_DELTA_SIGMA_DELTA_FAKE_HW_H_
#define INC_SIGMA_DELTA_SIGMA_DELTA_FAKE_HW_H_

#include <stdbool.h>
#include "sigma_delta/sigma_delta_hw.h"

typedef struct {
	bool (*read_comparator)();
	void (*write_dac)(bool);
	void (*set_v_in)(float);
} sigma_delta_fake_hw_operations;

typedef struct {
	float v_ref;
	float r; // the resistors' value
	float c; // the capacitor value
	float dt; // the time between calls to update the dac
} sigma_delta_fake_hw_parameters;

typedef struct {
	float v_in;  // input voltage to measure
	float v; // voltage in the comparator input (voltage at the capacitor)

} sigma_delta_fake_hw_state;

sigma_delta_fake_hw_operations init_sigma_delta_fake_hw(
		sigma_delta_fake_hw_parameters);

sigma_delta_hw_operations as_sigma_delta_hw(sigma_delta_fake_hw_operations);

#endif /* INC_SIGMA_DELTA_SIGMA_DELTA_FAKE_HW_H_ */
