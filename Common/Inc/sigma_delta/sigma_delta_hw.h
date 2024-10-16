/*
 * sigma_delta_hw.h
 *
 *  Created on: Oct 13, 2024
 *      Author: evetere
 */

#ifndef INC_SIGMA_DELTA_SIGMA_DELTA_HW_H_
#define INC_SIGMA_DELTA_SIGMA_DELTA_HW_H_

#include <stdbool.h>

typedef struct sigma_delta_hw_operations_struct {
	bool (*read_comparator)();
	void (*write_dac)(bool);
} sigma_delta_hw_operations;

sigma_delta_hw_operations init_sigma_delta_hw();

#endif /* INC_SIGMA_DELTA_SIGMA_DELTA_HW_H_ */
