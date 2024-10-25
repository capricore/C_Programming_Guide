  
#include <stdio.h>
#include <stdlib.h>

// (a) Function to calculate the total distance to a given street number x
int total_dist(int x, int nRel, int* stNum) {
    int total = 0;
    for (int i = 0; i < nRel; i++) {
        total += abs(x - stNum[i]);  // Sum of absolute distances
    }
    return total;
}

// Comparison function for qsort (used to sort the street numbers)
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int nRel;

    // Read the number of relatives from input
    printf("Enter the number of relatives: ");
    scanf("%d", &nRel);

    // Allocate memory for the street numbers
    int* stNum = (int*)malloc(nRel * sizeof(int));
    if (stNum == NULL) {
        printf("Memory allocation failed.\n");
        return 1;  // Exit if memory allocation fails
    }

    // Initialize street numbers with random values
    for (int i = 0; i < nRel; i++) {
        stNum[i] = rand() % 100 + 1;  // Random street number between 1 and 100
    }

    // Sort the street numbers to find the median efficiently
    qsort(stNum, nRel, sizeof(int), compare);

    // The optimal street number is the median
    int optimalStreet = stNum[nRel / 2];

    // Calculate the total distance to the optimal street number
    int minDistance = total_dist(optimalStreet, nRel, stNum);

    // Print the result
    printf("Optimal street number: %d\n", optimalStreet);
    printf("Minimum total distance: %d\n", minDistance);

    // Free the allocated memory
    free(stNum);

    return 0;
}
