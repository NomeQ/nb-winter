/*
 * lomuto-partition.c
 *
 * Naomi Dickerson 2014
 */

#include <stdio.h>
#include <stdlib.h>

#define FILENAME "Data1.txt"

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

int partitionSearch(int* array, int upper, int lower, int k) {
	int p;
	int index = k - 1;
	p = Partition(array, upper, lower);
	if (p == index) {
		return array[p];
	} else if (p > index) {
		return partitionSearch(array, p - 1, lower, k);
	} else {
		return partitionSearch(array, upper, p + 1, k);
	}
}

int main() {
	int size;
	int* array = NULL;
	int k, result;
	FILE* fileHandle = fopen(FILENAME, "r");

	fscanf(fileHandle, "%d", &size);

	array = (int*) (malloc(sizeof(int) * size));
	for (int i = 0; i < size; i++) {
		fscanf(fileHandle, "%d", &array[i]);
	}
	fclose(fileHandle);

	printf("k = \n");
	scanf("%d", &k);

	result = partitionSearch(array, size - 1, 0, k);

	printf("The %d -th smallest element is: %d ", k, result);

	printf("\n");
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}

	free(array);
	return 0;
}
