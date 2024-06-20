#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int allocation[MAX_PROCESSES][MAX_RESOURCES];
int request[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];

int num_processes = 2;
int num_resources = 4;

bool visited[MAX_PROCESSES];
bool in_recursion_stack[MAX_PROCESSES];

// Function to perform Depth First Search (DFS) to detect cycles
bool detect_cycle(int process) {
    if (!visited[process]) {
        visited[process] = true;
        in_recursion_stack[process] = true;
        
        // Check all resources requested by this process
        for (int i = 0; i < num_resources; ++i) {
            if (request[process][i] > available[i]) {
                // If the request exceeds available resources, return false (no cycle)
                in_recursion_stack[process] = false;
                return false;
            }
        }
        
        // Recursively check processes in the request graph
        for (int i = 0; i < num_processes; ++i) {
            if (allocation[process][i] > 0) {  // Process `process` is holding some resources
                if (!visited[i] && detect_cycle(i)) {
                    return true;
                } else if (in_recursion_stack[i]) {
                    return true;
                }
            }
        }
    }
    
    in_recursion_stack[process] = false;
    return false;
}

// Function to check for deadlock
bool is_deadlock() {
    // Initialize visited and recursion stack
    for (int i = 0; i < num_processes; ++i) {
        visited[i] = false;
        in_recursion_stack[i] = false;
    }
    
    // Call detect_cycle for each process
    for (int i = 0; i < num_processes; ++i) {
        if (!visited[i]) {
            if (detect_cycle(i)) {
                return true;
            }
        }
    }
    
    return false;
}

int main() {
    // Input allocation matrix
    printf("Enter allocation matrix (%d processes x %d resources):\n", num_processes, num_resources);
    for (int i = 0; i < num_processes; ++i) {
        printf("For process %d: ", i);
        for (int j = 0; j < num_resources; ++j) {
            scanf("%d", &allocation[i][j]);
        }
    }
    
    // Input request matrix
    printf("Enter request matrix (%d processes x %d resources):\n", num_processes, num_resources);
    for (int i = 0; i < num_processes; ++i) {
        printf("For process %d: ", i);
        for (int j = 0; j < num_resources; ++j) {
            scanf("%d", &request[i][j]);
        }
    }
    
    // Input available resources array
    printf("Enter available resources (%d resources): ", num_resources);
    for (int i = 0; i < num_resources; ++i) {
        scanf("%d", &available[i]);
    }
    
    // Perform deadlock detection
    if (is_deadlock()) {
        printf("Deadlock detected.\n");
    } else {
        printf("No deadlock detected.\n");
    }
    
    return 0;
}
