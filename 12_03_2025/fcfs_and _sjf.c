#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int id;
    int at, bt, ct, wt, tat, completed, remaining_time;
} process;


void calculate_fcfs(process p[], int n);
void calculate_sjf_preemptive(process p[], int n);
void calculate_sjf_nonpreemptive(process p[], int n);


void main() {
    int option, n;
    printf("Enter number of processes: \n");
    scanf("%d", &n);
    process p[n];


    for (int i = 0; i < n; i++) {
        printf("Enter Process ID, Arrival Time, and Burst Time for Process %d: ", i + 1);
        scanf("%d %d %d", &p[i].id, &p[i].at, &p[i].bt);
        p[i].remaining_time = p[i].bt;
    }


    while (1) {
        printf("\nEnter 1. FCFS \n2. SJF (Preemptive) \n3. SJF (Non-Preemptive) \n4. Exit\n");
        scanf("%d", &option);
        switch (option) {
            case 1:
                calculate_fcfs(p, n);
                break;
            case 2:
                calculate_sjf_preemptive(p, n);
                break;
            case 3:
                calculate_sjf_nonpreemptive(p, n);
                break;
            case 4:
                exit(0);
            default:
                printf("Incorrect entry\n");
        }
    }
}


void calculate_fcfs(process p[], int n) {
    int total_wt = 0, total_tat = 0;
    p[0].wt = 0;  
    p[0].ct = p[0].at + p[0].bt;  


    for (int i = 1; i < n; i++) {
        p[i].wt = p[i - 1].ct - p[i].at;  
        if (p[i].wt < 0) p[i].wt = 0;
        p[i].ct = p[i].at + p[i].bt + p[i].wt;
    }


    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;  
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }


    printf("\nFCFS Scheduling:\n");
    printf("PID\tArrival\tBurst\tCT\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat);
    }
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}


void calculate_sjf_preemptive(process p[], int n) {
    int total_wt = 0, total_tat = 0;
    int current_time = 0, completed = 0;
    int index;
    int remaining_processes = n;


    while (remaining_processes > 0) {
        int min_bt = 9999;
        index = -1;


       
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].remaining_time > 0 && p[i].remaining_time < min_bt) {
                min_bt = p[i].remaining_time;
                index = i;
            }
        }


        if (index == -1) {  
            current_time++;
            continue;
        }
 
        p[index].remaining_time--;
        current_time++;
 
        if (p[index].remaining_time == 0) {
            completed++;
            p[index].ct = current_time;  
            p[index].wt = p[index].ct - p[index].at - p[index].bt;  
            p[index].tat = p[index].wt + p[index].bt;  


            total_wt += p[index].wt;
            total_tat += p[index].tat;
            remaining_processes--;
        }
    }


    printf("\nPreemptive SJF Scheduling:\n");
    printf("PID\tArrival\tBurst\tCT\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat);
    }
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}


void calculate_sjf_nonpreemptive(process p[], int n) {
    int total_wt = 0, total_tat = 0;
    int current_time = 0, completed = 0;
    int index;
    int remaining_processes = n;
 
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at || (p[i].at == p[j].at && p[i].bt > p[j].bt)) {
                process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }


    while (remaining_processes > 0) {
        int min_bt = 9999;
        index = -1;
 
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].remaining_time > 0 && p[i].remaining_time < min_bt) {
                min_bt = p[i].remaining_time;
                index = i;
            }
        }


        if (index == -1) {  
            current_time++;
            continue;
        }
 
        current_time += p[index].remaining_time;
        p[index].remaining_time = 0;
        completed++;
 
        p[index].ct = current_time;  
        p[index].wt = p[index].ct - p[index].at - p[index].bt;  
        p[index].tat = p[index].wt + p[index].bt;  


        total_wt += p[index].wt;
        total_tat += p[index].tat;
        remaining_processes--;
    }


    printf("\nNon-Preemptive SJF Scheduling:\n");
    printf("PID\tArrival\tBurst\tCT\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat);
    }
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}
