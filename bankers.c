// Harsh Tamakuwala - 100824220
// David Hanna - 100828635

#include "bankers.h"

int available[NUMBER_OF_RESOURCES];

/*the maximum demand of each customer */
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES] = {
    {7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3} };

/* the amount currently allocated to each customer */
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES] = {
    {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} };

/* the remaining need of each customer */
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES] = {
    {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} };

int request_resources(int customer_num, int request[]){
    
    //* CORE BANKER ALGORITHM IMPLEMENTATION
    
    for(int i = 0; i < NUMBER_OF_RESOURCES; i++){
        if(request[i] <= need[customer_num][i]){
            //Comparison of the request (Also known as `W`) with the available ressources
            if(request[i] <= available[i]){

                //Allocating to customer (proc) the amount of resources requested
                available[i] = available[i] - request[i];
                allocation[customer_num][i] = allocation[customer_num][i] + request[i]; // W + Allocation
                need[customer_num][i] = need[customer_num][i] - request[i]; // Need - W

            }else{
                printf("Resource Request for Customer %d can not be fulfilled\n",customer_num);
                return -1;
            }
        }else{
            printf("Error, Customer %d is requesting more resources than it needs\n",customer_num);
            return -1;
        }
    }
    printf("Resource Request for Customer %d can be fulfilled sucessfully\n",customer_num);
    return 0;
}

int release_resources(int customer_num, int release[]){
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {

        if (release[i] > allocation[customer_num][i]) {
            printf("Error, Customer %d is releasing more resources than it has allocated\n", customer_num);
            return -1;
        }
    }
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        available[i] += release[i]; // Add the released resources back to the available pool
        allocation[customer_num][i] -= release[i]; // Subtract the released resources from the customer's allocation
        need[customer_num][i] += release[i];  // Add the need back to the customer's need!
    }

    printf("Resource release for Customer %d fulfilled successfully\n", customer_num);
    return 0;
}

bool is_safe_state(){

    // INIT an array to keep track of which customers (processes) needs have been fully met
    bool finished[NUMBER_OF_CUSTOMERS] = {false};

    // INIT an array to represent the amount of each resource currently available
    int work[NUMBER_OF_RESOURCES];

    // Populate the work array with the total amount of each resource
    for(int i = 0;i < NUMBER_OF_RESOURCES; i++){
        work[i] = available[i];
    }

    // Iterate over each customer and each resource ( X by Y matrix)
    for(int i = 0;i< NUMBER_OF_CUSTOMERS; i++){
        for(int j = 0;j < NUMBER_OF_RESOURCES; j++){

            // If a customer's need for a resource is less than or equal to the amount of that resource currently available
            if(finished[i]==false && need[i][j] <= work[j]){

                // 'Allocate' the resource to the customer by adding the amount currently allocated to the customer to the amount available
                work[j] = work[j] + allocation[i][j];

                finished[i] = true;
            }
        }
    }

    // Initialize a variable to keep track of whether the system is in a safe state
    bool safe = true;

    // Check if there are any customers whose needs have not been met
    for(int i = 0; i < NUMBER_OF_CUSTOMERS; i++){
        if(finished[i] ==  false){ 
            safe = false;
            break;
        }
    }
    printf("Current state is safe?: %s\n", safe ? "True" : "False");

    // Return whether the system is in a safe state
    return safe;
}