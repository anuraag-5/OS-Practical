#include <stdio.h>

#define REF_LEN 17

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

void lru(int n) {
    int frames[20], last_used[20];
    int i, j, time = 0, page_faults = 0;

    for (i = 0; i < n; i++) {
        frames[i] = -1;        // Empty frames
        last_used[i] = -1;
    }

    printf("\n===== LRU Page Replacement =====\n");
    printf("Ref\tFrames\t\t\tRemark\n");
    printf("---------------------------------------------\n");

    for (i = 0; i < REF_LEN; i++) {
        int page = ref_string[i];
        int pos = search(frames, n, page);

        printf("%2d\t", page);

        if (pos != -1) {
            // Hit: update last used time
            time++;
            last_used[pos] = time;

            print_frames(frames, n);
            printf("\tHit\n");
        } else {
            // Miss: page fault
            page_faults++;
            time++;

            // Find empty frame first
            int replace_index = -1;
            for (j = 0; j < n; j++) {
                if (frames[j] == -1) {
                    replace_index = j;
                    break;
                }
            }

            // If no empty frame, replace least recently used
            if (replace_index == -1) {
                int min_time = last_used[0];
                replace_index = 0;
                for (j = 1; j < n; j++) {
                    if (last_used[j] < min_time) {
                        min_time = last_used[j];
                        replace_index = j;
                    }
                }
            }

            frames[replace_index] = page;
            last_used[replace_index] = time;

            print_frames(frames, n);
            printf("\tPage Fault\n");
        }
    }

    printf("---------------------------------------------\n");
    printf("Total Page Faults (LRU) = %d\n", page_faults);
}

int main() {
    int n;

    printf("Enter number of memory frames: ");
    scanf("%d", &n);

    if (n <= 0 || n > 20) {
        printf("Invalid number of frames.\n");
        return 0;
    }

    lru(n);

    return 0;
}