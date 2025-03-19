#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int pid, arrival, burst, waiting, turn, rem_time, priority;
} process;

void roundRobin(process p[], int n, int q);
void priority_preemptive(process p[], int n);
void priority_nonpreemptive(process p[], int n);

int main() {
    int option, n, q;
    printf("Enter number of processes: \n");
    scanf("%d", &n);
    process p[n];

    for (int i = 0; i < n; i++) {
        printf("Enter Process ID, Arrival Time, and Burst Time for Process %d: ", i + 1);
        scanf("%d %d %d", &p[i].pid, &p[i].arrival, &p[i].burst);
        p[i].rem_time = p[i].burst;
    }

    while (1) {
        printf("\nEnter 1. Round Robin \n2. Priority (Preemptive) \n3. Priority (Non-Preemptive) \n4. Exit\n");
        scanf("%d", &option);
        switch (option) {
            case 1:
                printf("Enter quantum time: ");
                scanf("%d", &q);
                roundRobin(p, n, q);
                break;
            case 2:
                for (int i = 0; i < n; i++) {
                    printf("Enter priority of Process ID %d: ", p[i].pid);
                    scanf("%d", &p[i].priority);
                }
                priority_preemptive(p, n);
                break;
            case 3:
                for (int i = 0; i < n; i++) {
                    printf("Enter priority of Process ID %d: ", p[i].pid);
                    scanf("%d", &p[i].priority);
                }
                priority_nonpreemptive(p, n);
                break;
            case 4:
                exit(0);
            default:
                printf("Incorrect entry\n");
        }
    }
}

void roundRobin(process p[], int n, int q) {
    int currentTime = 0, total_tat = 0, total_wt = 0, completed = 0;
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].rem_time > 0 && p[i].arrival <= currentTime) {
                int time_slice = (p[i].rem_time > q) ? q : p[i].rem_time;
                currentTime += time_slice;
                p[i].rem_time -= time_slice;

                if (p[i].rem_time == 0) {
                    completed++;
                    p[i].turn = currentTime - p[i].arrival;
                    p[i].waiting = p[i].turn - p[i].burst;
                    total_tat += p[i].turn;
                    total_wt += p[i].waiting;
                }
            }
        }
    }

    printf("\nRound Robin Scheduling:\n");
    printf("PID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].waiting, p[i].turn);
    }
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

void priority_preemptive(process p[], int n) {
    int currentTime = 0, completed = 0;
    int total_tat = 0, total_wt = 0;

    while (completed < n) {
        int min_priority = 9999, index = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= currentTime && p[i].rem_time > 0 && p[i].priority < min_priority) {
                min_priority = p[i].priority;
                index = i;
            }
        }

        if (index != -1) {
            p[index].rem_time--;
            currentTime++;

            if (p[index].rem_time == 0) {
                completed++;
                p[index].turn = currentTime - p[index].arrival;
                p[index].waiting = p[index].turn - p[index].burst;
                total_tat += p[index].turn;
                total_wt += p[index].waiting;
            }
        } else {
            currentTime++;
        }
    }

    printf("\nPriority Preemptive Scheduling:\n");
    printf("PID\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].priority, p[i].waiting, p[i].turn);
    }
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

void priority_nonpreemptive(process p[], int n) {
    int currentTime = 0, completed = 0;
    int total_tat = 0, total_wt = 0;

    while (completed < n) {
        int min_priority = 9999, index = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= currentTime && p[i].rem_time > 0 && p[i].priority < min_priority) {
                min_priority = p[i].priority;
                index = i;
            }
        }

        if (index != -1) {
            currentTime += p[index].rem_time;
            p[index].rem_time = 0;
            completed++;
            p[index].turn = currentTime - p[index].arrival;
            p[index].waiting = p[index].turn - p[index].burst;
            total_tat += p[index].turn;
            total_wt += p[index].waiting;
        } else {
            currentTime++;
        }
    }

    printf("\nPriority Non-Preemptive Scheduling:\n");
    printf("PID\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].priority, p[i].waiting, p[i].turn);
    }
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}
