#include <stdio.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 4

int available[MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int finish[MAX_PROCESSES];

int num_processes = 5;
int num_resources = 4;

void initialize() {
    printf("Enter available resources (space-separated): ");
    for (int i = 0; i < num_resources; ++i) {
        scanf("%d", &available[i]);
    }
    
    printf("Enter maximum demand of each process (matrix form):\n");
    for (int i = 0; i < num_processes; ++i) {
        printf("For process %d: ", i);
        for (int j = 0; j < num_resources; ++j) {
            scanf("%d", &max[i][j]);
        }
    }
    
    printf("Enter allocated resources for each process (matrix form):\n");
    for (int i = 0; i < num_processes; ++i) {
        printf("For process %d: ", i);
        for (int j = 0; j < num_resources; ++j) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    
    // Initialize finish array
    for (int i = 0; i < num_processes; ++i) {
        finish[i] = 0;
    }
}

int safety_check() {
    int work[MAX_RESOURCES];
    int i, j, k;
    
    // Initialize work array with available resources
    for (i = 0; i < num_resources; ++i) {
        work[i] = available[i];
    }
    
    int safe_sequence[MAX_PROCESSES];
    int count = 0;
    
    printf("Initial Work array: ");
    for (i = 0; i < num_resources; ++i) {
        printf("%d ", work[i]);
    }
    printf("\n");
    
    // Find an i which is not finished and need <= work
    for (k = 0; k < num_processes; ++k) {
        for (i = 0; i < num_processes; ++i) {
            if (finish[i] == 0) {
                int can_allocate = 1;
                for (j = 0; j < num_resources; ++j) {
                    if (need[i][j] > work[j]) {
                        can_allocate = 0;
                        break;
                    }
                }
                if (can_allocate) {
                    // Allocate resources to process i
                    for (j = 0; j < num_resources; ++j) {
                        work[j] += allocation[i][j];
                    }
                    // Mark process i as finished
                    finish[i] = 1;
                    // Add process i to safe sequence
                    safe_sequence[count++] = i;
                    
                    // Display updated work array
                    printf("Work array after allocating resources to process %d: ", i);
                    for (int w = 0; w < num_resources; ++w) {
                        printf("%d ", work[w]);
                    }
                    printf("\n");
                    
                    // Reset inner loop to check all processes again
                    break;
                }
            }
        }
    }
    
    // Check if all processes are finished
    if (count < num_processes) {
        printf("System is in unsafe state.\n");
        return 0;
    } else {
        printf("System is in safe state.\nSafe sequence: ");
        for (i = 0; i < num_processes; ++i) {
            printf("%d ", safe_sequence[i]);
        }
        printf("\n");
        return 1;
    }
}

int main() {
    initialize();
    safety_check();
    return 0;
}
