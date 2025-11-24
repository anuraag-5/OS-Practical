#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct Process {
    int pid, arrival, burst, remaining, tat, wt, completion;
};

int main(){
    int n;
    srand(time(NULL));
    printf("Enter number of Processes: ");
    scanf("%d", &n);

    struct Process *p = (struct Process*)malloc(sizeof(struct Process) * n);

    for(int i = 0; i < n; i++){
        p[i].pid = i + 1;
        printf("\nEnter arrival time for P%d: ", i + 1);
        scanf("%d", &p[i].arrival);
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &p[i].burst);

        int randomTime = rand() % 10 + 1;
        printf("Randomly generated CPU burst for P%d: %d", i + 1, randomTime);

        // p[i].burst += 2 + randomTime;
        p[i].remaining = p[i].burst;
    }

    int completed = 0, timee = 0, pointer = 0, prevInx = -1;
    int *pArr = (int*)malloc(sizeof(int) * 30), *pStart = (int*)malloc(sizeof(int) * 30), *pEnd = (int*)malloc(sizeof(int) * 30);
    float avgTAT = 0, avgWT = 0;

    while(completed < n){
        int inx = -1, minBurst = 111111;
        for(int i = 0; i < n; i++){
            if(p[i].arrival <= timee && p[i].remaining > 0 && p[i].remaining < minBurst){
                inx = i;
                minBurst = p[i].remaining;
            }
        }

        if(inx == -1) { timee++; continue; }

        if(!(prevInx == inx)){
            if(pointer > 0) {
                pEnd[pointer - 1] = timee;
            }
            pStart[pointer] = timee;
            pArr[pointer] = inx;

            prevInx = inx;
            pointer++;
        }

        p[inx].remaining--;
        timee++;

        if(p[inx].remaining == 0) {
            p[inx].completion = timee;
            p[inx].tat = p[inx].completion - p[inx].arrival;
            p[inx].wt = p[inx].tat - p[inx].burst;

            avgTAT += p[inx].tat;
            avgWT += p[inx].wt;
            completed++;
        }
    }

    pEnd[pointer - 1] = timee;

    printf("\n\nGantt Chart\n");

    int firstPrinted = 0;
    for(int i = 0; i < pointer; i++){
        if(!firstPrinted) printf("%d|\tP%d\t%d|", pStart[i], pArr[i] + 1, pEnd[i]);
        else printf("%d\tP%d\t%d|", pStart[i], pArr[i] + 1, pEnd[i]);

        firstPrinted = 1;
    }
    printf("\n");

    printf("Average Waiting Time: %.2f\nAverage Turnaround Time: %.2f\n", avgWT/n, avgTAT/n);
    return 0;
}