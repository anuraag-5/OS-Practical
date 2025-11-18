// parent_sort.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void bubble_sort(int a[], int n) {
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-i-1;j++)
            if(a[j] > a[j+1]){
                int t = a[j]; a[j] = a[j+1]; a[j+1] = t;
            }
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers:\n", n);
    for(int i=0;i<n;i++) scanf("%d", &arr[i]);

    bubble_sort(arr, n);

    printf("Parent sorted array: ");
    for(int i=0;i<n;i++) printf("%d ", arr[i]);
    printf("\n");

    // Convert sorted array to strings
    char *args[n+2];
    args[0] = "./child";     // program name

    for(int i=0;i<n;i++) {
        args[i+1] = malloc(10);
        sprintf(args[i+1], "%d", arr[i]);
    }
    args[n+1] = NULL;

    pid_t pid = fork();

    if(pid == 0) {
        // CHILD CODE: execute child_search program
        execve("./child", args, NULL);
        exit(1);
    }
    else if(pid > 0) {
        // PARENT CODE
        wait(NULL);
        printf("Parent: Child finished execution.\n");
    }

    return 0;
}
