#include <stdio.h>

int main() {
    int n, i;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int AT[n], BT[n], CT[n], TAT[n], WT[n];
    int gantt[n+1]; // timeline values

    printf("Enter Arrival Times (space separated): ");
    for (i = 0; i < n; i++) scanf("%d", &AT[i]);

    printf("Enter Burst Times (space separated): ");
    for (i = 0; i < n; i++) scanf("%d", &BT[i]);

    // FCFS scheduling
    int time = 0;
    for (i = 0; i < n; i++) {
        if (time < AT[i]) time = AT[i]; 
        time += BT[i];
        CT[i] = time;
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];
        gantt[i+1] = CT[i];
    }

    // table
    printf("\nProcess | AT | BT | CT | TAT | WT\n");
    printf("-----------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("P%-7d| %-2d | %-2d | %-2d | %-3d | %-2d\n",
               i+1, AT[i], BT[i], CT[i], TAT[i], WT[i]);
    }
    

    // averages
    float avgTAT = 0, avgWT = 0;
    for (i = 0; i < n; i++) {
        avgTAT += TAT[i];
        avgWT += WT[i];
    }
    printf("\nAverage TAT = %.2f\n", avgTAT/n);
    printf("Average WT  = %.2f\n", avgWT/n);

    // gantt chart
    printf("\nGantt Chart:\n|");
    for (i = 0; i < n; i++) printf(" P%d |", i+1);
    printf("\n0");
    for (i = 1; i <= n; i++) printf("   %d", gantt[i]);
    printf("\n");

    return 0;
}
