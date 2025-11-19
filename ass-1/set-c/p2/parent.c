// exec_child.c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if(pid < 0){
        perror("fork failed");
        return 1;
    }

    if(pid == 0){
        printf("Child: Executing Set A (1) program using exec()\n");
        execl("/mnt/c/USers/ASUS/Downloads/OS-Practical/ass-1/p1", "p1", NULL);

        perror("exec failed");
    }
    else {
        printf("Parent: I am parent.\n");
    }

    return 0;
}