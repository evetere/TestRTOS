#include "sigma_delta_fake_hw.h"

#include <stdio.h>

static sigma_delta_fake_hw_parameters parameters;
static sigma_delta_fake_hw_state state;

/*
 * This function updates the voltage in the capacitor after the dac output is set
 */
void sigma_delta_fake_hw_write_dac(bool b) {
	// voltage in the output pin
	float v_dac = b ? 5.0 : 0.0;
	// calculate the current in the capacitor summing the currents from both voltage sources
	float ic = (state.v_in - state.v) / parameters.r
			+ (v_dac - state.v) / parameters.r;
	// assume 20us between calls
	float dt = 20e-6;
	// voltage in the capacitor is 1/C * integral(i(t), dt)
	// as current is roughly constant in the period, the integral is the area ic x dt
	float dv = ic * dt / parameters.c;

	// adjust capacitor voltage from dv
	state.v += dv;
//	printf("ic =%e    dv=%e    v=%e\n", ic, dv, v);
}

bool sigma_delta_fake_hw_read_comparator() {
	return (state.v < parameters.v_ref);
}

void sigma_delta_fake_hw_set_v_in(float v_in) {
	printf("v_in = %f\n", v_in);
	state.v_in = v_in;
}

static sigma_delta_fake_hw_operations sigma_delta_fake_hw_operations_bindings =
		{
				.read_comparator = sigma_delta_fake_hw_read_comparator,
				.write_dac = sigma_delta_fake_hw_write_dac,
				.set_v_in = sigma_delta_fake_hw_set_v_in
		};

static sigma_delta_hw_operations sigma_delta_not_fake_hw_operations_bindings =
		{
				.read_comparator = sigma_delta_fake_hw_read_comparator,
				.write_dac = sigma_delta_fake_hw_write_dac,
		};

sigma_delta_fake_hw_operations init_sigma_delta_fake_hw(
		sigma_delta_fake_hw_parameters p) {
	parameters = p;
	return sigma_delta_fake_hw_operations_bindings;
}

sigma_delta_hw_operations as_sigma_delta_hw(sigma_delta_fake_hw_operations fake) {
	return sigma_delta_not_fake_hw_operations_bindings;

}
