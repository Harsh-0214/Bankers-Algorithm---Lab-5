#include "Banker.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != NUM_RESOURCES + 1) {
        printf("Usage: %s <resource1> <resource2> ... <resourceN>\n", argv[0]);
        return 1;
    }

    // Initialize available resources from command-line arguments
    int available[NUM_RESOURCES];
    for (int i = 0; i < NUM_RESOURCES; i++) {
        available[i] = atoi(argv[i + 1]);
    }

    // Initialize maximum demand of each customer (you can use any method)
    int max[NUM_CUSTOMERS][NUM_RESOURCES] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    // Initialize allocation and need arrays to zero
    int allocation[NUM_CUSTOMERS][NUM_RESOURCES] = {0};
    int need[NUM_CUSTOMERS][NUM_RESOURCES];

    // Calculate need matrix
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Initialize the banker with the maximum resources and print the initial state
    init_banker(available, max);
    print_state();

    // Example: Request resources for customer 1
    int request1[NUM_RESOURCES] = {1, 0, 2};
    request_resources(1, request1);
    print_state();

    // Example: Release resources for customer 1
    release_resources(1);
    print_state();

    // Clean up and exit
    return 0;
}

