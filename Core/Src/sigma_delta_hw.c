#include "main.h"
#include "sigma_delta/sigma_delta_hw.h"

#include <stdio.h>

/*
 * This function updates the voltage in the capacitor after the dac output is set
 */
void sigma_delta_hw_write_dac(bool b) {
	HAL_GPIO_WritePin(DAC_GPIO_Port, DAC_Pin,
			(b ? GPIO_PIN_SET : GPIO_PIN_RESET));
}

bool sigma_delta_hw_read_comparator() {
	GPIO_PinState s = HAL_GPIO_ReadPin(COMP_GPIO_Port, COMP_Pin);
	return s;
}

static sigma_delta_hw_operations sigma_delta_hw_operations_bindings =
		{
				.read_comparator = sigma_delta_hw_read_comparator,
				.write_dac = sigma_delta_hw_write_dac,
		};

sigma_delta_hw_operations init_sigma_delta_hw() {
	return sigma_delta_hw_operations_bindings;
}
