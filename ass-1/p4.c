// file: orphan_demo.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void){
    pid_t pid = fork();
    if(pid < 0){
        perror("fork");
        return 1;
    }

    if(pid > 0){
        /* parent */
        printf("[Parent] PID=%d. Parent exiting now.\n", getpid());
        /* parent exits immediately -> child becomes orphan */
        exit(0);
    } else {
        /* child */
        printf("[Child] PID=%d. My parent PID initially: %d\n", getpid(), getppid());
        printf("[Child] Doing some work (sleeping)...\n");
        sleep(5); /* allow parent to exit and init to adopt child */
        printf("[Child] After sleep: PID=%d, New PPID=%d (adopted)\n", getpid(), getppid());
        /* show child finished work */
        printf("[Child] Child finishing now.\n");
    }
    return 0;
}
