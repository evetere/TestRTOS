/*
 * sigma-delta.h
 *
 *  Created on: Oct 13, 2024
 *      Author: evetere
 */

#ifndef INC_SIGMA_DELTA_H_
#define INC_SIGMA_DELTA_H_

#include "sigma_delta/sigma_delta_hw.h"

typedef struct {
	void (*start_conversion)();
	float (*result)();
	int (*raw_result)();
	void (*tick)();
	bool (*ended)();
} sigma_delta_operations;

sigma_delta_operations init_sigma_delta(sigma_delta_hw_operations);
sigma_delta_operations get_sigma_delta();

#endif /* INC_SIGMA_DELTA_H_ */
