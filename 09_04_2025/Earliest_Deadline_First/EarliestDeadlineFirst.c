#include <stdio.h>

#define MAX 10

typedef struct {
    int pid;
    int burst;
    int deadline;
    int period;
    int remaining_burst;
    int next_deadline;
} Process;

int main() {
    int n;
    Process p[MAX];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the CPU burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].burst);
        p[i].remaining_burst = p[i].burst;
        p[i].pid = i + 1;
    }

    printf("Enter the deadlines:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].deadline);
        p[i].next_deadline = p[i].deadline;
    }

    printf("Enter the time periods:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].period);
    }

    printf("\nEarliest Deadline Scheduling:\n");
    printf("PID\tBurst\tDeadline\tPeriod\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t\t%d\n", p[i].pid, p[i].burst, p[i].deadline, p[i].period);
    }

    int time = 0, total_time = 20;
    printf("\nScheduling occurs for %d ms\n\n", total_time);

    while (time < total_time) {
        int earliest = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].remaining_burst > 0) {
                if (earliest == -1 || p[i].next_deadline < p[earliest].next_deadline) {
                    earliest = i;
                }
            }
        }

        if (earliest != -1) {
            printf("%dms : Task %d is running.\n", time, p[earliest].pid);
            p[earliest].remaining_burst--;
        } else {
            printf("%dms : CPU is idle.\n", time);
        }

        time++;

        for (int i = 0; i < n; i++) {
            if (time % p[i].period == 0) {
                p[i].remaining_burst = p[i].burst;
                p[i].next_deadline = time + p[i].deadline;
            }
        }
    }

    return 0;
}
