#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct Process {
    int pid, arrival, burst, turnaround, completion, remaining, waiting, start;
};

int main(){
    int n, tq;
    srand(time(NULL));
    printf("Enter number of Processes: ");
    scanf("%d", &n);

    printf("Enter time Quantum: ");
    scanf("%d", &tq);

    struct Process *p = (struct Process*)malloc(sizeof(struct Process) * n);
    for(int i = 0; i < n; i++){
        p[i].pid = i + 1;
        printf("Enter arrival time for P%d: ", i + 1);
        scanf("%d", &p[i].arrival);
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &p[i].burst);

        int randomBurst = rand() % 10 + 1;
        printf("Random Burst for P%d: %d\n", i + 1, randomBurst);
        p[i].burst += 2 + randomBurst;
        p[i].remaining = p[i].burst;
        p[i].waiting = 0;
    }

    int completed = 0, timee = 0, isFirstPrinted = 0;
    float avgTAT = 0, avgWT = 0;

    printf("Gantt Chart\n");

    while(completed < n){
        int allDone = 1;

        for(int i = 0; i < n; i++){            
            if(p[i].remaining > 0 && p[i].arrival <= timee){
                allDone = 0;

                if(!isFirstPrinted) {
                    isFirstPrinted = 1;
                    printf("%d| P%d ", p[i].arrival, p[i].pid);
                } else {
                    printf("P%d ", p[i].pid);
                }

                if(p[i].remaining > tq){
                    timee += tq;
                    p[i].remaining -= tq;
                    printf("%d|", timee);
                } else {
                    timee += p[i].remaining;
                    printf("%d|", timee);
                    p[i].completion = timee;
                    p[i].start = p[i].completion - p[i].burst;
                    p[i].turnaround = p[i].completion - p[i].arrival;
                    p[i].waiting = (p[i].completion - p[i].burst) - p[i].arrival;
                    p[i].remaining = 0;

                    avgTAT += p[i].turnaround;
                    avgWT += p[i].waiting;
                    completed++;
                }
            }
        }

        if(allDone) timee++;
    }

    printf("\n");

    return 0;
}