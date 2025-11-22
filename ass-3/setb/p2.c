#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

struct Process {
    int pid, arrival, burst, priority, waiting, turnaround, completion, done;
};

int main() {
    int n, timee=0, completed=0, isFirstPrinted = 0;
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
        printf("Enter Priority for P%d (Lower number = Higher priority): ", i+1);
        scanf("%d", &p[i].priority);

        int nextBurst = rand() % 10 + 1;
        printf("Random next burst for P%d = %d (after 2 units IO)\n", i+1, nextBurst);
        p[i].burst += 2 + nextBurst;

        p[i].done=0;
    }

    float avgWT=0, avgTAT=0;
    printf("\nGantt Chart:\n");

    while(completed < n) {
        int idx=-1, bestPriority=INT_MAX;

        for(int i=0; i<n; i++) {
            if(p[i].arrival <= timee && !p[i].done && p[i].priority < bestPriority) {
                bestPriority=p[i].priority;
                idx=i;
            }
        }

        if(idx==-1) { timee++; continue; }

        
        p[idx].waiting = timee - p[idx].arrival;
        timee += p[idx].burst;
        p[idx].completion=timee;
        p[idx].turnaround = p[idx].completion - p[idx].arrival;
        if(!isFirstPrinted){
            printf("%d| P%d %d|", p[idx].arrival, p[idx].pid, p[idx].completion);
        } else {
            printf("P%d %d|", p[idx].pid, p[idx].completion);
        }
        p[idx].done=1;

        avgWT += p[idx].waiting;
        avgTAT += p[idx].turnaround;
        completed++;
    }
    printf("|\n");

    printf("\nProcess\tAT\tBT(total)\tPri\tWT\tTAT\tCT\n");
    for(int i=0; i<n; i++) {
        printf("P%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n",
            p[i].pid, p[i].arrival, p[i].burst, p[i].priority,
            p[i].waiting, p[i].turnaround, p[i].completion);
    }

    printf("\nAverage Waiting Time: %.2f", avgWT/n);
    printf("\nAverage Turnaround Time: %.2f\n", avgTAT/n);
    return 0;
}