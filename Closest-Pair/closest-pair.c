/*
 * closest-pair.c
 *
 * Naomi Dickerson 2014
 *
 * Uses divide and conquer algorithm to find closest pair in a given
 * data set of points
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// It is not actually necessary to compute the square root
// and find the exact distance between the points to compare
// them, thus I leave the distance in its "squared" form for
// simplicity and to save on computer operations

int square(int num) {
    return num * num;
}

int sqr_distance(int x1, int x2, int y1, int y2) {
    return (square(x1 - x2) + square(y1 - y2));
}

int main() {

    int* x_coords = NULL;
    int* y_coords = NULL;
    int index1, index2, dist, dmin, num_points;
    FILE* fileHandle = fopen("Data6.txt", "r");

    {
        //Get the number of points in the file
        fscanf(fileHandle, "%d", &num_points);

        //Malloc the same space in both the x and y coord arrays
        x_coords = (int*) (malloc(sizeof(int) * num_points));
        y_coords = (int*) (malloc(sizeof(int) * num_points));

        //Read in each line of the file as an x & y coord of a point
        for (int i = 0; i < num_points; i++) {
            fscanf(fileHandle, "%d %d", &x_coords[i], &y_coords[i]);
        }
    }

    fclose(fileHandle);

    // CREATE FUNCTION HERE.


    {
        // Print the indices of the closest pair as well as their coordinates
        printf("\nThe closest pair:\n");
        printf("Points p%d (%d, %d) and p%d (%d, %d)\n\n",
                index1, x_coords[index1], y_coords[index1],
                index2, x_coords[index2], y_coords[index2]);
    }

    free(x_coords);
    free(y_coords);
    return 0;
}
