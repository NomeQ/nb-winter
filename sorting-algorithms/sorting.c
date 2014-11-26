/*
 * sorting.c
 *
 *  Naomi Dickerson 2014
 *  Coursework for New Beginnings
 *
 *  Implement Insertion Sort, Quicksort, and Merge Sort Algorithms
 *  then time and test each algorithm
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILENAME "Data1.txt"

void Merge(int* B, int size_B, int* C, int size_C, int* A) {
	int i = 0;
	int j = 0;
	int k = 0;

	while (i < size_B && j < size_C) {
		if (B[i] <= C[j]) {
			A[k] = B[i];
			i++;
		} else {
			A[k] = C[j];
			j++;
		}
		k++;
	}
	if (i == size_B) {
		for (; j < size_C; j++) {
			A[k] = C[j];
			k++;
		}
	} else {
		for (; i < size_B; i++) {
			A[k] = B[i];
			k++;
		}
	}
}

void mergeSort(int* A, int size) {
	if (size > 1) {
		int* B = NULL;
		int* C = NULL;
		int size_B, size_C;

		size_B = (size / 2);
		// Account for the case of odd size arrays
		size_C = (size - (size / 2));

		B = (int*) (malloc(sizeof(int) * size_B));
		C = (int*) (malloc(sizeof(int) * size_C));

		memcpy(B, A, size_B * sizeof(int));
		memcpy(C, &A[size_B], size_C * sizeof(int));

		mergeSort(B, size_B);
		mergeSort(C, size_C);
		Merge(B, size_B, C, size_C, A);
		free(B);
		free(C);
 	}
}

void insertionSort(int* array, int size) {
	int v, j;
	for (int i = 1; i < size; i++) {
		v = array[i];
		j = i - 1;
		while (j >= 0 && array[j] > v) {
			array[j + 1] = array[j];
			j -= 1;
		}
		array[j + 1] = v;
	}
}

void swap(int* array, int pos1, int pos2) {
	int temp = array[pos1];
	array[pos1] = array[pos2];
	array[pos2] = temp;
}

int Partition(int* array, int upper, int lower) {
	int p = array[lower];
	int i = lower;
	int j = upper + 1;

	while (i < j) {
		do {
			i++;
		} while (array[i] < p);
		do {
			j--;
		} while (array[j] > p);
		swap(array, i, j);
	}
	swap(array, i, j);
	swap(array, lower, j);
	return j;
}

void quickSort(int* array, int upper, int lower) {
	int split;
	if (lower < upper) {
		split = Partition(array, upper, lower);
		quickSort(array, split - 1, lower);
		quickSort(array, upper, split + 1);
	}
}

double printSeconds(clock_t total_t) {
	double seconds;
	seconds = (double) total_t / CLOCKS_PER_SEC;
	return seconds;
}

int main() {
	int size;
	int* intArray = NULL;
	int* intArray2 = NULL;
	int* intArray3 = NULL;
	clock_t merge_time, insert_time, quick_time, start_t, end_t;

	FILE* fileHandle = fopen(FILENAME, "r");
	fscanf(fileHandle, "%d", &size);

	// Dynamically allocate space for 3 intArrays, to be
	// used with each algorithm.
	intArray = (int*) (malloc(sizeof(int) * size));
	intArray2 = (int*) (malloc(sizeof(int) * size));
	intArray3 = (int*) (malloc(sizeof(int) * size));
	for (int i = 0; i < size; i++) {
		fscanf(fileHandle, "%d", &intArray[i]);
	}

	fclose(fileHandle);

	// Copy array elements into intArray2 & 3
	memcpy(intArray2, intArray, size * sizeof(int));
	memcpy(intArray3, intArray, size * sizeof(int));

	// Time quickSort function
	start_t = clock();
	quickSort(intArray2, size - 1, 0);
	end_t = clock();
	quick_time = end_t - start_t;

	// Time insertionSort function
	start_t = clock();
	insertionSort(intArray3, size);
	end_t = clock();
	insert_time = end_t - start_t;

	// Time mergeSort function
	start_t = clock();
	mergeSort(intArray, size);
	end_t = clock();
	merge_time = end_t - start_t;

	printf("Array size: %d\n", size);
	printf("Time for merge sorting: %f\n", printSeconds(merge_time));
	printf("Time for quick sorting: %f\n", printSeconds(quick_time));
	printf("Time for insertion sorting: %f\n", printSeconds(insert_time));

	free(intArray);
	free(intArray2);
	free(intArray3);

	return 0;
}

