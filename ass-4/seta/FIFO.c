#include <stdio.h>

#define REF_LEN 17

// Given reference string from assignment
int ref_string[REF_LEN] = { 12 ,5 ,12 ,18 ,6 ,8 ,3 ,11 ,2 ,19 ,12 ,6 ,8 ,12 ,15 ,19 ,8 };

void print_frames(int frames[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (frames[i] == -1)
            printf(" - ");
        else
            printf("%2d ", frames[i]);
    }
}

int search(int frames[], int n, int page) {
    int i;
    for (i = 0; i < n; i++)
        if (frames[i] == page)
            return i;          // Return frame index (hit)
    return -1;                 // Miss
}

void fifo(int n) {
    int frames[20], i, front = 0, page_faults = 0;

    for (i = 0; i < n; i++)
        frames[i] = -1;        // Initially empty

    printf("\n===== FIFO Page Replacement =====\n");
    printf("Ref\tFrames\t\t\tRemark\n");
    printf("---------------------------------------------\n");

    for (i = 0; i < REF_LEN; i++) {
        int page = ref_string[i];

        printf("%2d\t", page);

        // Check if page already in any frame
        if (search(frames, n, page) == -1) {
            // Page fault: replace frame pointed by 'front'
            frames[front] = page;
            front = (front + 1) % n;
            page_faults++;

            print_frames(frames, n);
            printf("\tPage Fault\n");
        } else {
            // Hit: frames unchanged
            print_frames(frames, n);
            printf("\tHit\n");
        }
    }

    printf("---------------------------------------------\n");
    printf("Total Page Faults (FIFO) = %d\n", page_faults);
}

int main() {
    int n;

    printf("Enter number of memory frames: ");
    scanf("%d", &n);

    if (n <= 0 || n > 20) {
        printf("Invalid number of frames.\n");
        return 0;
    }

    fifo(n);

    return 0;
}