/*
 * loop-optimization.c
 *
 *  Naomi Dickerson 2014
 *  Coursework for Wu-chang Feng's NB class
 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000

typedef int data_t;

void inner4(data_t* u, data_t* v, data_t* dest, int vec_length) {
	// loop with local variables
	long int i;
	int length = vec_length;
	data_t *udata = u;
	data_t *vdata = v;
	data_t sum = (data_t) 0;

	for (i = 0; i < length; i++) {
		sum = sum + udata[i] * vdata[i];
	}

	*dest = sum;
}

void inner5(data_t* u, data_t* v, data_t* dest, int vec_length) {
	// loop with 4-way data unrolling
	long int i;
	int length = vec_length;
	data_t *udata = u;
	data_t *vdata = v;
	data_t sum = (data_t) 0;

	for (i = 0; i < (length - 3); i += 4) {
		sum += udata[i] * vdata[i];
		sum += udata[i+1] * vdata[i+1];
		sum += udata[i+2] * vdata [i+2];
		sum += udata[i+3] * vdata [i+3];
	}

	for (; i < length; i++) {
		sum += udata[i] * vdata[i];
	}

	*dest = sum;
}

void inner6(data_t* u, data_t* v, data_t* dest, int vec_length) {
	// loop with four parallel accumulators
	long int i;
	int length = vec_length;
	data_t *udata = u;
	data_t *vdata = v;
	data_t sum1 = (data_t) 0;
	data_t sum2 = (data_t) 0;
	data_t sum3 = (data_t) 0;
	data_t sum4 = (data_t) 0;

	for (i = 0; i < (length - 3); i += 4) {
		sum1 += udata[i] * vdata[i];
		sum2 += udata[i+1] * vdata[i+1];
		sum3 += udata[i+2] * vdata [i+2];
		sum4 += udata[i+3] * vdata [i+3];
	}

	for (; i < length; i++) {
		sum1 += udata[i] * vdata[i];
	}

	*dest = sum1 + sum2 + sum3 + sum4;
}

void inner7(data_t* u, data_t* v, data_t* dest, int vec_length) {
	// loop with unrolling and reassociation
	long int i;
	int length = vec_length;
	data_t *udata = u;
	data_t *vdata = v;
	data_t sum = (data_t) 0;

	for (i = 0; i < (length - 3); i += 4) {
		sum = sum + ((udata[i] * vdata[i]) + (udata[i+1] * vdata[i+1]));
		sum = sum + ((udata[i+2] * vdata [i+2]) + (udata[i+3] * vdata [i+3]));
	}

	for (; i < length; i++) {
		sum += udata[i] * vdata[i];
	}

	*dest = sum;
}

int main() {
	int vec_length = SIZE;
	data_t vec_u[SIZE];
	data_t vec_v[SIZE];
	data_t *dest;

	// Fill vectors arbitrarily for testing.
	for (int i = 0; i < SIZE; i++) {
		vec_u[i] = (data_t) i;
		vec_v[i] = (data_t) i + 1;
	}

	inner4(vec_u, vec_v, dest, vec_length);
	inner5(vec_u, vec_v, dest, vec_length);
	inner6(vec_u, vec_v, dest, vec_length);
	inner7(vec_u, vec_v, dest, vec_length);

	return 0;
}
