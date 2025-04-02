#include <stdio.h>
#include <stdlib.h>
 
typedef struct {
    int id;
    int at, bt, ct, wt, tat, queue;
} process;


void fcfs(process p[], int n, process final_order[], int *index);
void roundRobin(process p[], int n, int q, process final_order[], int *index);
void display(process p[], int n);


int total_wt = 0, total_tat = 0;


int main() {
    int n, q, user_count = 0, s_count = 0;
   
    printf("Enter number of processes: ");
    scanf("%d", &n);
   
    process p[n], user[n], system[n], final_order[n];  
    int final_index = 0;  
   
    printf("To differentiate between types of queues: \nEnter 0 for system process, 1 for user process\n");
   
    for (int i = 0; i < n; i++) {
        printf("Enter Process ID, Arrival Time, Burst Time, and Type of queue for Process %d: ", i + 1);
        scanf("%d %d %d %d", &p[i].id, &p[i].at, &p[i].bt, &p[i].queue);
    }
     
    for (int i = 0; i < n; i++) {
        if (p[i].queue == 0) {
            system[s_count++] = p[i];
        } else {
            user[user_count++] = p[i];
        }
    }
   
    if (s_count > 0) {
        printf("Enter time quantum for Round Robin: ");
        scanf("%d", &q);
        roundRobin(system, s_count, q, final_order, &final_index);
    }
   
    if (user_count > 0) {
        fcfs(user, user_count, final_order, &final_index);
    }
   
    display(final_order, final_index);
   
    return 0;
}


void fcfs(process p[], int n, process final_order[], int *index) {
    int currentTime = 0;


    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].at) {
            currentTime = p[i].at;
        }
        p[i].ct = currentTime + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        total_wt += p[i].wt;
        total_tat += p[i].tat;
        currentTime = p[i].ct;
        final_order[*index] = p[i];
        final_order[*index].queue = 1;
        (*index)++;
    }
}


void roundRobin(process p[], int n, int q, process final_order[], int *index) {
    int currentTime = 0, completed = 0;
    int remaining_time[n];


    for (int i = 0; i < n; i++) {
        remaining_time[i] = p[i].bt;
    }


    while (completed < n) {
        int all_idle = 1;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && remaining_time[i] > 0) {
                all_idle = 0;
                int time_slice = (remaining_time[i] > q) ? q : remaining_time[i];
                currentTime += time_slice;
                remaining_time[i] -= time_slice;


                if (remaining_time[i] == 0) {
                    completed++;
                    p[i].ct = currentTime;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    total_wt += p[i].wt;
                    total_tat += p[i].tat;
                    final_order[*index] = p[i];
                    final_order[*index].queue = 0;
                    (*index)++;
                }
            }
        }
        if (all_idle && completed < n) {
            currentTime++;
        }
    }
}


void display(process p[], int n) {
    printf("\nFinal Scheduling Table:\n");
    printf("PID\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\tQueue Type\n");
   
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%s\n",
               p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat,
               (p[i].queue == 0) ? "RR" : "FCFS");
    }
   
    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}
