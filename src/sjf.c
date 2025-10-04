#include <stdio.h>
#include <limits.h>

int main() {
    int n, i, j;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int AT[n], BT[n], CT[n], TAT[n], WT[n], completed[n], gantt[n+1];
    for (i = 0; i < n; i++) completed[i] = 0;

    printf("Enter Arrival Times (space separated): ");
    for (i = 0; i < n; i++) scanf("%d", &AT[i]);

    printf("Enter Burst Times (space separated): ");
    for (i = 0; i < n; i++) scanf("%d", &BT[i]);

    int time = 0, done = 0, g = 0;
    gantt[g++] = 0;

    while (done < n) {
        int idx = -1, minBT = INT_MAX;
        for (i = 0; i < n; i++) {
            if (!completed[i] && AT[i] <= time && BT[i] < minBT) {
                minBT = BT[i];
                idx = i;
            }
        }
        if (idx == -1) {
            time++;
        } else {
            time += BT[idx];
            CT[idx] = time;
            TAT[idx] = CT[idx] - AT[idx];
            WT[idx] = TAT[idx] - BT[idx];
            completed[idx] = 1;
            gantt[g++] = time;
            done++;
        }
    }

    printf("\nProcess | AT | BT | CT | TAT | WT\n");
    printf("-----------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("P%-7d| %-2d | %-2d | %-2d | %-3d | %-2d\n",
               i+1, AT[i], BT[i], CT[i], TAT[i], WT[i]);
    }


    float avgTAT = 0, avgWT = 0;
    for (i = 0; i < n; i++) {
        avgTAT += TAT[i];
        avgWT += WT[i];
    }
    printf("\nAverage TAT = %.2f\n", avgTAT/n);
    printf("Average WT  = %.2f\n", avgWT/n);

    printf("\nGantt Chart:\n|");
    for (i = 1; i < g; i++) printf(" P%d |", i);
    printf("\n0");
    for (i = 1; i < g; i++) printf("   %d", gantt[i]);
    printf("\n");

    return 0;
}
