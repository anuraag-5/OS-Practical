#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Process {
    int pid, arrival, burst, remaining, waiting, turnaround, completion;
};

int main() {
    int n, tq;
    srand(time(NULL));

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process *p = (struct Process *)malloc(sizeof(struct Process) * n);
    for(int i=0; i<n; i++) {
        p[i].pid=i+1;
        printf("Enter Arrival Time for P%d: ", i+1);
        scanf("%d", &p[i].arrival);
        printf("Enter First CPU Burst for P%d: ", i+1);
        scanf("%d", &p[i].burst);

        int nextBurst = rand() % 10 + 1;
        printf("Random next burst for P%d = %d (after 2 units IO)\n", i+1, nextBurst);
        p[i].burst += 2 + nextBurst;

        p[i].remaining = p[i].burst;
        p[i].waiting=0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time=0, completed=0;
    float avgWT=0, avgTAT=0;

    printf("\nGantt Chart:\n");
    
    while(completed < n) {
        int allDone=1;
        for(int i=0; i<n; i++) {
            if(p[i].remaining > 0 && p[i].arrival <= time) {
                allDone=0;
                printf("| P%d ", p[i].pid);

                if(p[i].remaining > tq) {
                    time += tq;
                    p[i].remaining -= tq;
                } else {
                    time += p[i].remaining;
                    p[i].completion=time;
                    p[i].turnaround = p[i].completion - p[i].arrival;
                    p[i].waiting = p[i].turnaround - p[i].burst;
                    avgWT += p[i].waiting;
                    avgTAT += p[i].turnaround;
                    p[i].remaining=0;
                    completed++;
                }
            }
        }
        if(allDone) time++;
    }
    printf("|\n");

    printf("\nProcess\tAT\tBT(total)\tWT\tTAT\tCT\n");
    for(int i=0; i<n; i++) {
        printf("P%d\t%d\t%d\t\t%d\t%d\t%d\n",
            p[i].pid, p[i].arrival, p[i].burst,
            p[i].waiting, p[i].turnaround, p[i].completion);
    }

    printf("\nAverage Waiting Time: %.2f", avgWT/n);
    printf("\nAverage Turnaround Time: %.2f\n", avgTAT/n);
    return 0;
}