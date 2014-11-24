void selectionSort(int* intArray, int arraySize) {
	int min;
	for (int i = 0; i < arraySize - 1; i++) {
		min = i;
		for (int j = i + 1; j < arraySize; j++) {
			if (intArray[j] < intArray[min]) {
				min = j;
			}
			swap(intArray, i, min);
			min = i;   //need to reset this before next iteration of loop!
		}
	}
}

void bubbleSort(int* intArray, int arraySize) {
	for (int i = 0; i < arraySize - 1; i++) {
		for (int j = 0; j < arraySize - 1 - i; j++) {
			if (intArray[j + 1] < intArray[j]) {
				swap(intArray, j, j + 1);
			}
		}
	}
}
