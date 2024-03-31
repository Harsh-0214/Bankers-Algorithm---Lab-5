#ifndef BANKER_H
#define BANKER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define NUMBER_OF_CUSTOMERS 5 //Number of processes
#define NUMBER_OF_RESOURCES 3

//* Available is a 1x3 matrix, representing the available instances of each resource, inputted by usr

extern int available[NUMBER_OF_RESOURCES]; 

//* [ Y columns (5) ] by [ X sized rows (3) ]

extern int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES]; //Maximum matrix

extern int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES]; //Allocation matrix

extern int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES]; // Need = Max - Allocation

int request_resources(int customer_num, int request[]);
int release_resources(int customer_num, int release[]);
bool is_safe_state();

#endif