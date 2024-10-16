#include "sigma_delta_fake_hw.h"

#include <stdio.h>

#define V_REF 2.5

#define V_IN 3.0

#define R 47E3
#define C 100E-9

static sigma_delta_fake_hw_parameters parameters;
static sigma_delta_fake_hw_state state;

/*
 * This function updates the voltage in the capacitor after the dac output is set
 */
void sigma_delta_fake_hw_write_dac(bool b) {
	// voltage in the output pin
	float v_dac = b ? 5.0 : 0.0;
	// calculate the current in the capacitor summing the currents from both voltage sources
	float ic = (state.v_in - state.v) / R + (v_dac - state.v) / R;
	// assume 20us between calls
	float dt = 20e-6;
	// voltage in the capacitor is 1/C * integral(i(t), dt)
	// as current is roughly constant in the period, the integral is the area ic x dt
	float dv = ic * dt / C;

	// adjust capacitor voltage from dv
	state.v += dv;
//	printf("ic =%e    dv=%e    v=%e\n", ic, dv, v);
}

bool sigma_delta_fake_hw_read_comparator() {
	return (state.v < parameters.v_ref);
}

void sigma_delta_fake_hw_set_v_in(float v_in) {
	state.v_in = v_in;
}

static sigma_delta_fake_hw_operations sigma_delta_fake_hw_operations_bindings =
		{
				.read_comparator = sigma_delta_fake_hw_read_comparator,
				.write_dac = sigma_delta_fake_hw_write_dac,
				.set_v_in = sigma_delta_fake_hw_set_v_in
		};

sigma_delta_fake_hw_operations init_sigma_delta_fake_hw(
		sigma_delta_fake_hw_parameters p) {
	parameters = p;
	return sigma_delta_fake_hw_operations_bindings;
}

sigma_delta_hw_operations as_sigma_delta_hw(sigma_delta_fake_hw_operations fake) {
	sigma_delta_hw_operations sigma_delta_not_fake_hw_operations_bindings =
			{
					.read_comparator = sigma_delta_fake_hw_read_comparator,
					.write_dac = sigma_delta_fake_hw_write_dac,
			};

	return sigma_delta_not_fake_hw_operations_bindings;

}
