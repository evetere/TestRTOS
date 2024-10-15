/*
 * sigma_delta_hw.h
 *
 *  Created on: Oct 13, 2024
 *      Author: evetere
 */

#ifndef INC_SIGMA_DELTA_SIGMA_DELTA_HW_H_
#define INC_SIGMA_DELTA_SIGMA_DELTA_HW_H_

#include <stdbool.h>

struct sigma_delta_hw_operations {
	bool (*read_comparator)();
	void (*write_dac)(bool);
	void (*engage)(bool);
	float (*read_v)();
};

struct sigma_delta_hw_operations init_sigma_delta_hw();

#endif /* INC_SIGMA_DELTA_SIGMA_DELTA_HW_H_ */
