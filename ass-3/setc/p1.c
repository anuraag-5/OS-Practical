#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

struct Process {
    int pid, arrival, burst, start, remaining, priority;
    int waiting, turnaround, completion;
};

int main() {
    int n, timee = 0, completed = 0, arr[30];
    for(int i = 0; i < 30; i++) arr[i] = -1;
    srand(time(NULL));

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process *p = (struct Process *)malloc(sizeof(struct Process) * n);
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time for P%d: ", i + 1);
        scanf("%d", &p[i].arrival);
        printf("Enter First CPU Burst for P%d: ", i + 1);
        scanf("%d", &p[i].burst);
        printf("Enter Priority for P%d (Lower number = Higher priority): ", i + 1);
        scanf("%d", &p[i].priority);

        int nextBurst = rand() % 10 + 1; // random burst
        printf("Random next burst for P%d = %d (after 2 units IO)\n", i + 1, nextBurst);
        // p[i].burst += 2 + nextBurst;

        p[i].remaining = p[i].burst;
        p[i].waiting = p[i].turnaround = p[i].completion = 0;
        p[i].start = -1;
    }

    
    float avgWT = 0, avgTAT = 0;
    int prevIndex = -1, pointer = 0, isFirstPrinted = 0;
    while (completed < n) {
        int idx = -1, bestPriority = INT_MAX;

        // find process with highest priority (lowest number)
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= timee && p[i].remaining > 0) {
                if (p[i].priority < bestPriority) {
                    bestPriority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) { // no process ready
            timee++;
            continue;
        }

        if(!(idx == prevIndex)){
            arr[pointer++] = idx;
            if(p[idx].start == -1)
            p[idx].start = timee;
            prevIndex = idx;
        }

        p[idx].remaining--;
        timee++;

        if (p[idx].remaining == 0) {
            p[idx].completion = timee;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;

            avgWT += p[idx].waiting;
            avgTAT += p[idx].turnaround;
            completed++;
        }
    }

    printf("\nGantt Chart:\n");
    for(int i = 0; i < 30; i++){
        if(arr[i] == -1) break;
        if(!isFirstPrinted){
            printf("%d| P%d %d|", p[arr[i]].start, p[arr[i]].pid, p[arr[i]].completion);
            isFirstPrinted = 1;
        } else {
            printf(" P%d %d|", p[arr[i]].pid, p[arr[i]].completion);
        }
    }

    printf("|\n");

    printf("\nProcess\tAT\tBT(total)\tPri\tWT\tTAT\tCT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival, p[i].burst, p[i].priority,
               p[i].waiting, p[i].turnaround, p[i].completion);
    }

    printf("\nAverage Waiting Time: %.2f", avgWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", avgTAT / n);

    return 0;
}