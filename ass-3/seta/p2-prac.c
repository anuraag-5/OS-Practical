#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct Process {
    int pid, arrival, burst, waiting, completion, turnaround;
};

int main(){
    int n;
    srand(time(NULL));

    printf("Enter number of Processes: ");
    scanf("%d", &n);

    struct Process *p = (struct Process*)malloc(sizeof(struct Process) * n);

    for(int i = 0; i < n; i++){
        p[i].pid = i + 1;
        printf("Enter arrival time for P%d: ", i + 1);
        scanf("%d", &p[i].arrival);
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &p[i].burst);

        int randBurstTime = rand() % 10 + 1;
        p[i].burst += 2 + randBurstTime;
    }

    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            if(p[i].burst > p[j].burst){
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int time = 0;
    for(int i = 0; i < n; i++){
        if(p[i].arrival > time) time = p[i].arrival;

    }
}