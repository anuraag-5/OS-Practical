#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/resource.h>

int main(){
    pid_t pid;

    pid = fork();

    if ( pid < 0){
        printf("Fork Failed");
        return 0;
    } else if(pid == 0){
        // Child process
        printf("I am a Child Process\n");
        printf("Child Process Priority before nice: %d\n", getpriority(PRIO_PROCESS, 0));
        nice(-5);
        printf("Child Process Priority after nice: %d\n", getpriority(PRIO_PROCESS, 0));
    } else {
        // Parent Process
        printf("I am a Parent Process\n");
        printf("Parent Process Priority: %d\n", getpriority(PRIO_PROCESS, 0));
    }
    
}