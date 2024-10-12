/*
 * fibonacci.c
 *
 *  Created on: Oct 12, 2024
 *      Author: evetere
 */
#include "fibonacci.h"

int fibonacci(int n) {
	int a = 0;
	int f = 1;
	if (n == 0) {
		f = 0;
	} else {
		for (int i = 1; i < n; i++) {
			int t = a;
			a = f;
			f = f + t;
		}
	}
	return f;
}
