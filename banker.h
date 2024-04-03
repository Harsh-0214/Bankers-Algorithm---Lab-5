//Harsh Tamakuwala - 100824220
//David Hanna - 100828635
#ifndef BANKER_H
#define BANKER_H

#include <stdbool.h>

#define NUM_RESOURCES 3
#define NUM_CUSTOMERS 5

extern int available[NUM_RESOURCES];
extern int maximum[NUM_CUSTOMERS][NUM_RESOURCES];
extern int allocated[NUM_CUSTOMERS][NUM_RESOURCES];
extern int need[NUM_CUSTOMERS][NUM_RESOURCES];


void init_banker(int available[], int max[][NUM_RESOURCES]);
void cleanup_banker();
void calculate_need();
bool is_safe(int customer_id, int request[]);
void request_resources(int customer_id, int request[]);
void release_resources(int customer_id);
void print_state();

#endif
