// file: sort_fork.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/* insertion sort */
void insertion_sort(int a[], int n){
    for(int i = 1; i < n; ++i){
        int key = a[i];
        int j = i - 1;
        while(j >= 0 && a[j] > key){
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

/* bubble sort */
void bubble_sort(int a[], int n){
    for(int i = 0; i < n - 1; ++i)
        for(int j = 0; j < n - 1 - i; ++j)
            if(a[j] > a[j+1]){
                int t = a[j]; 
                a[j] = a[j + 1]; 
                a[j + 1] = t;
            }
}

void print_array(int a[], int n){
    for(int i = 0; i < n; ++i) printf("%d ", a[i]);
    printf("\n");
}

int main(void){
    int n;
    printf("Enter number of integers: ");
    scanf("%d", &n);

    int *arr = malloc(sizeof(int)*n);

    
    for(int i = 0; i < n; ++i) {
        printf("Enter %d integer:\n", i + 1);
        scanf("%d", &arr[i]);
    }

    pid_t pid = fork();

    if(pid < 0){
        printf("Fork Error");
        free(arr);
        return 1;
    }

    if(pid == 0){
        /* child: insertion sort */
        insertion_sort(arr, n);
        printf("\n[Child] PID=%d, PPID=%d\n", getpid(), getppid());
        printf("[Child] Sorted array (insertion sort): ");
        print_array(arr, n);
        free(arr);
        exit(0);
    } else {
        /* parent: bubble sort, then wait for child */
        bubble_sort(arr, n);
        /* wait for child to finish */
        wait(NULL);
        printf("\n[Parent] PID=%d, PPID=%d\n", getpid(), getppid());
        printf("[Parent] Sorted array (bubble sort): ");
        print_array(arr, n);
        free(arr);
    }
    return 0;
}
