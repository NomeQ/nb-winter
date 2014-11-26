/*
 * binary-search.c
 *
 * Naomi Dickerson 2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FILENAME "Data8.txt"

int binarySearch(int* array, int size, int key) {
	int l = 0;
	int r = size - 1;
	int m;
	while (l <= r) {
		m = floor((l + r) / 2);
		if (key == array[m]) {
			return m;
		} else if (key < array[m]) {
			r = m - 1;
		} else {
			l = m + 1;
		}
	}

	return -1;
}

int main() {
	int size, key, index;
	int* array = NULL;
	FILE* fileHandle = fopen(FILENAME, "r");

	fscanf(fileHandle, "%d", &size);

	array = (int*) (malloc(sizeof(int) * size));
	for (int i = 0; i < size; i++) {
		fscanf(fileHandle, "%d", &array[i]);
	}

	fclose(fileHandle);

	printf("Search key: \n");
	scanf("%d", &key);

	index = binarySearch(array, size, key);

	printf("\nFound at index: %d \n", index);

	return 0;
}
