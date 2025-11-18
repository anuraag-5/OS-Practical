#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        // fork failed
        printf("Fork failed!\n");
        return 1;
    }
    else if (pid == 0) {
        // child process
        printf("I am child process.\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
    }
    else {
        // parent process
        printf("I am parent process.\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);
    }

    return 0;
}