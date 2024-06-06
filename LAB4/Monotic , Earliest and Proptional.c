#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int period;
    int execution_time;
    int deadline;
    int remaining_time;
} Task;

void rate_monotonic(Task tasks[], int n, int hyper_period);
void earliest_deadline_first(Task tasks[], int n, int hyper_period);
void proportional_scheduling(Task tasks[], int n, int hyper_period);
int gcd(int a, int b);
int lcm(int a, int b);

int main() {
    int n, hyper_period = 1;

    printf("Enter the number of tasks: ");
    scanf("%d", &n);

    Task tasks[n];
    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("Enter period, execution time and deadline for task %d: ", i + 1);
        scanf("%d %d %d", &tasks[i].period, &tasks[i].execution_time, &tasks[i].deadline);
        tasks[i].remaining_time = tasks[i].execution_time;
        hyper_period = lcm(hyper_period, tasks[i].period);
    }

    printf("Rate-Monotonic Scheduling:\n");
    rate_monotonic(tasks, n, hyper_period);
    printf("\nEarliest-Deadline First Scheduling:\n");
    earliest_deadline_first(tasks, n, hyper_period);
    printf("\nProportional Scheduling:\n");
    proportional_scheduling(tasks, n, hyper_period);

    return 0;
}

void rate_monotonic(Task tasks[], int n, int hyper_period) {
    int time = 0;
    while (time < hyper_period) {
        int min_period = __INT_MAX__;
        int task_index = -1;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0 && tasks[i].period < min_period && time % tasks[i].period == 0) {
                min_period = tasks[i].period;
                task_index = i;
            }
        }
        if (task_index != -1) {
            printf("Time %d: Task %d\n", time, tasks[task_index].id);
            tasks[task_index].remaining_time--;
            if (tasks[task_index].remaining_time == 0) {
                tasks[task_index].remaining_time = tasks[task_index].execution_time;
            }
        } else {
            printf("Time %d: Idle\n", time);
        }
        time++;
    }
}

void earliest_deadline_first(Task tasks[], int n, int hyper_period) {
    int time = 0;
    while (time < hyper_period) {
        int min_deadline = __INT_MAX__;
        int task_index = -1;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0 && tasks[i].deadline < min_deadline) {
                min_deadline = tasks[i].deadline;
                task_index = i;
            }
        }
        if (task_index != -1) {
            printf("Time %d: Task %d\n", time, tasks[task_index].id);
            tasks[task_index].remaining_time--;
            if (tasks[task_index].remaining_time == 0) {
                tasks[task_index].remaining_time = tasks[task_index].execution_time;
                tasks[task_index].deadline += tasks[task_index].period;
            }
        } else {
            printf("Time %d: Idle\n", time);
        }
        time++;
    }
}

void proportional_scheduling(Task tasks[], int n, int hyper_period) {
    int time = 0;
    while (time < hyper_period) {
        int max_ratio = -1;
        int task_index = -1;
        for (int i = 0; i < n; i++) {
            int ratio = tasks[i].remaining_time * 100 / tasks[i].period;
            if (tasks[i].remaining_time > 0 && ratio > max_ratio) {
                max_ratio = ratio;
                task_index = i;
            }
        }
        if (task_index != -1) {
            printf("Time %d: Task %d\n", time, tasks[task_index].id);
            tasks[task_index].remaining_time--;
            if (tasks[task_index].remaining_time == 0) {
                tasks[task_index].remaining_time = tasks[task_index].execution_time;
            }
        } else {
            printf("Time %d: Idle\n", time);
        }
        time++;
    }
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}