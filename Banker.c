#include <stdio.h>
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

int available[NUM_RESOURCES] = {8, 5, 7};
int maximum[NUM_CUSTOMERS][NUM_RESOURCES] = {
    {6, 2, 1},
    {1, 5, 7},
    {6, 1, 0},
    {1, 5, 0},
    {4, 2, 4}
};
int allocated[NUM_CUSTOMERS][NUM_RESOURCES] = {
    {0, 0, 0},
    {0, 0, 0},
    {2, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
};
int need[NUM_CUSTOMERS][NUM_RESOURCES];

void calculate_need() {
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            need[i][j] = maximum[i][j] - allocated[i][j];
        }
    }
}

bool is_safe(int customer_id, int request[]) {
    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (request[i] > available[i]) {
            return false;
        }
    }

    int work[NUM_RESOURCES];
    for (int i = 0; i < NUM_RESOURCES; i++) {
        work[i] = available[i];
    }

    bool finish[NUM_CUSTOMERS];
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        finish[i] = false;
    }

    int count = 0;
    while (count < NUM_CUSTOMERS) {
        bool found = false;
        for (int i = 0; i < NUM_CUSTOMERS; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (int j = 0; j < NUM_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    for (int j = 0; j < NUM_RESOURCES; j++) {
                        work[j] += allocated[i][j];
                    }
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

void request_resources(int customer_id, int request[]) {
    if (is_safe(customer_id, request)) {
        for (int i = 0; i < NUM_RESOURCES; i++) {
            allocated[customer_id][i] += request[i];
            available[i] -= request[i];
            need[customer_id][i] -= request[i];
        }
        printf("Request granted.\n");
    } else {
        printf("Request denied.\n");
    }
}

void release_resources(int customer_id) {
    for (int i = 0; i < NUM_RESOURCES; i++) {
        available[i] += allocated[customer_id][i];
        allocated[customer_id][i] = 0;
    }
    printf("Resources released successfully.\n");
}

void print_state() {
    printf("Available resources:\n");
    for (int i = 0; i < NUM_RESOURCES; i++) {
        printf("%d ", available[i]);
    }
    printf("\n\n");

    printf("Maximum resources:\n");
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            printf("%d ", maximum[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Allocated resources:\n");
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            printf("%d ", allocated[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Needed resources:\n");
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void init_banker(int av[], int ma[][NUM_RESOURCES]) {
    for (int i = 0; i < NUM_RESOURCES; i++) {
        available[i] = av[i];
        for (int j = 0; j < NUM_CUSTOMERS; j++) {
            maximum[j][i] = ma[j][i];
            need[j][i] = maximum[j][i] - allocated[j][i];
        }
    }
}


