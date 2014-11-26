/*
 * binary-digits.c
 *
 * Naomi Dickerson 2014
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {

    int my_number, bit_count;
    int valid_input = 0;

    printf("\nEnter a positive integer: ");

    while (valid_input == 0) {

        scanf("%d", &my_number);

        if (my_number < 0) {
            printf("\nNegative input. Try again.\n");
        }

        else {
            valid_input = 1;
        }
    }

    bit_count = floor(log2(my_number)) + 1;

    printf("\nThe number of bits in the binary of %d is: %d\n", my_number, bit_count);

    return 0;
}
