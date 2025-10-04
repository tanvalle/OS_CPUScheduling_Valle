#include <stdio.h>

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int AT[n], BT[n], RT[n], CT[n], TAT[n], WT[n];
    int i, time = 0, done = 0;

    printf("Enter Arrival Times (space separated): ");
    for (i = 0; i < n; i++) scanf("%d", &AT[i]);

    printf("Enter Burst Times (space separated): ");
    for (i = 0; i < n; i++) {
        scanf("%d", &BT[i]);
        RT[i] = BT[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    printf("\nGantt Chart:\n|");
    int gantt[100], ganttTime[100], gIndex = 0;
    ganttTime[gIndex] = 0;

    while (done < n) {
        int flag = 0;
        for (i = 0; i < n; i++) {
            if (RT[i] > 0 && AT[i] <= time) {
                flag = 1;
                if (RT[i] > tq) {
                    time += tq;
                    RT[i] -= tq;
                    printf("  P%d  |", i+1);
                    gantt[++gIndex] = i+1;
                    ganttTime[gIndex] = time;
                } else {
                    time += RT[i];
                    CT[i] = time;
                    RT[i] = 0;
                    done++;
                    printf("  P%d  |", i+1);
                    gantt[++gIndex] = i+1;
                    ganttTime[gIndex] = time;
                }
            }
        }
        if (!flag) {
            time++;
        }
    }

    // Calculate TAT and WT
    float avgTAT = 0, avgWT = 0;
    for (i = 0; i < n; i++) {
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];
        avgTAT += TAT[i];
        avgWT += WT[i];
    }
    avgTAT /= n;
    avgWT /= n;

    // Table
    printf("\n\nProcess | AT | BT | CT | TAT | WT\n");
    printf("-----------------------------------\n");
    for (i = 0; i < n; i++)
        printf("P%-7d| %-2d | %-2d | %-2d | %-3d | %-2d\n",
               i+1, AT[i], BT[i], CT[i], TAT[i], WT[i]);

    printf("\nAverage TAT = %.2f", avgTAT);
    printf("\nAverage WT  = %.2f\n", avgWT);

    // Gantt Chart values
    printf("\nGantt Chart:\n");
    for (i = 1; i <= gIndex; i++) {
        printf("|  P%d  ", gantt[i]);
    }
    printf("|\n");

    for (i = 0; i <= gIndex; i++) {
        printf("%-6d", ganttTime[i]);
    }
    printf("\n");

    return 0;
}
