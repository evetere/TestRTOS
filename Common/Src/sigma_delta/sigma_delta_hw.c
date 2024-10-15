#include "sigma_delta/sigma_delta_hw.h"

#include <stdio.h>

#define V_REF 2.5

#define V_IN 3.0

#define R 47E3
#define C 100E-9

static bool eng = 0;

static float v = 0.0; // value in the comparator input (voltage in the capacitor)

/*
 * This function updates the voltage in the capacitor after the dac output is set
 */
void sigma_delta_hw_write_dac(bool b) {
	// voltage in the output pin
	float v_dac = b ? 5.0 : 0.0;
	// calculate the current in the capacitor summing the currents from both voltage sources
	float ic = (V_IN - v) / R + (v_dac - v) / R;
	// assume 20us between calls
	float dt = 20e-6;
	// voltage in the capacitor is 1/C * integral(i(t), dt)
	// as current is roughly constant in the period, the integral is the area ic x dt
	float dv = ic * dt / C;

	// adjust capacitor voltage from dv
	v = v + dv;
//	printf("ic =%e    dv=%e    v=%e\n", ic, dv, v);
}

bool sigma_delta_hw_read_comparator() {
	bool c = (v < V_REF);
	if (eng) {
		sigma_delta_hw_write_dac(c);
	}
	return c;
}

void sigma_delta_hw_engage(bool e) {
	eng = e;
}

float sigma_delta_read_v() {
	return v;
}

static struct sigma_delta_hw_operations sigma_delta_hw_operations_bindings =
		{
				.read_comparator = sigma_delta_hw_read_comparator,
				.write_dac = sigma_delta_hw_write_dac,
				.engage = sigma_delta_hw_engage,
				.read_v = sigma_delta_read_v
		};

struct sigma_delta_hw_operations init_sigma_delta_hw() {
	return sigma_delta_hw_operations_bindings;
}
