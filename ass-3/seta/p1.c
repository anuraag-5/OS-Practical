#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Process {
    int pid, arrival, burst, waiting, turnaround, completion;
};

int main() {
    int n;
    srand(time(NULL)); // seed random

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process *p = (struct Process *)malloc(sizeof(struct Process) * n);

    for(int i=0; i<n; i++) {
        p[i].pid = i+1;
        printf("Enter Arrival Time for P%d: ", i+1);
        scanf("%d", &p[i].arrival);
        printf("Enter First CPU Burst for P%d: ", i+1);
        scanf("%d", &p[i].burst);

        // simulate random next burst + IO wait
        int nextBurst = rand() % 10 + 1;
        printf("Random next burst for P%d = %d (after 2 units IO)\n", i+1, nextBurst);
        p[i].burst += 2 + nextBurst; 
    }

    // Sort by arrival
    for(int i=0; i<n-1; i++) {
        for(int j=i+1; j<n; j++) {
            if(p[i].arrival > p[j].arrival) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int time=0;
    float avgWT=0, avgTAT=0;

    printf("\nGantt Chart:\n");
    for(int i=0; i<n; i++) {
        if(time < p[i].arrival) time = p[i].arrival;

        p[i].waiting = time - p[i].arrival;
        time += p[i].burst;
        p[i].completion = time;
        p[i].turnaround = p[i].completion - p[i].arrival;

        avgWT += p[i].waiting;
        avgTAT += p[i].turnaround;

        if(i == 0)
        printf("%d| P%d %d", p[i].completion - p[i].burst, p[i].pid, p[i].completion);
        else
        printf("| P%d %d", p[i].pid, p[i].completion);
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