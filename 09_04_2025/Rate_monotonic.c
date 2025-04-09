#include <stdio.h>
#include <math.h>

int main() {
    int n, i;
    printf("Enter the number of processes:");
    scanf("%d", &n);

    int burst[n], period[n];
    printf("Enter the CPU burst times:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &burst[i]);
    }

    printf("Enter the time periods:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &period[i]);
    }

    int lcm = period[0];
    for (i = 1; i < n; i++) {
        int a = lcm, b = period[i];
        
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        lcm = (lcm * period[i]) / a;
    }
    printf("LCM=%d\n\n", lcm);

    printf("Rate Monotone Scheduling:\n");
    printf("PID\tBurst\tPeriod\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", i + 1, burst[i], period[i]);
    }

    float utilization = 0.0;
    for (i = 0; i < n; i++) {
        utilization += (float)burst[i] / period[i];
    }

    float bound = n * (pow(2, 1.0 / n) - 1);
    printf("\n%.6f <= %.6f =>%s\n", utilization, bound, (utilization <= bound) ? "true" : "false");

    return 0;
}
