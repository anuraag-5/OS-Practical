// child_search.c
#include <stdio.h>
#include <stdlib.h>

int binary_search(int arr[], int n, int key){
    int low = 0, high = n - 1;

    while(low <= high){
        int mid = (low + high)/2;

        if(arr[mid] == key) return mid;
        else if(arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int main(int argc, char *argv[]) {
    int n = argc - 1;
    int *arr = (int*)malloc(sizeof(int) * n);

    for(int i=1;i<argc;i++)
        arr[i-1] = atoi(argv[i]);

    printf("\nChild received sorted array: ");
    for(int i=0;i<n;i++) printf("%d ", arr[i]);
    printf("\n");

    int key;
    printf("Enter key to search: ");
    scanf("%d", &key);

    int pos = binary_search(arr, n, key);

    if(pos == -1)
        printf("Element NOT found.\n");
    else
        printf("Element found at index %d\n", pos);

    return 0;
}
