#include <stdio.h>

#define REF_LEN 17

int ref_string[REF_LEN] = {12,5,12,18,6,8,3,11,2,19,12,6,8,12,15,19,8};

int search(int frames[], int n, int page) {
    for (int i = 0; i < n; i++)
        if (frames[i] == page)
            return i;
    return -1;
}

void print_frames(int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1) printf(" - ");
        else                 printf("%2d ", frames[i]);
    }
}

void opt(int n) {
    int frames[20];
    int page_faults = 0;

    for (int i = 0; i < n; i++)
        frames[i] = -1;

    printf("\n===== OPT (Optimal) Page Replacement =====\n");
    printf("Ref\tFrames\t\t\tRemark\n");
    printf("---------------------------------------------\n");

    for (int i = 0; i < REF_LEN; i++) {
        int page = ref_string[i];
        int pos = search(frames, n, page);

        printf("%2d\t", page);

        if (pos != -1) {
            // Hit
            print_frames(frames, n);
            printf("\tHit\n");
            continue;
        }

        page_faults++;

        // Check for empty frame
        int replace_index = -1;
        for (int j = 0; j < n; j++) {
            if (frames[j] == -1) {
                replace_index = j;
                break;
            }
        }

        if (replace_index == -1) {
            // No empty frame -> choose victim by OPT
            int farthest_index = -1;
            int farthest_dist  = -1; // largest distance into future

            for (int j = 0; j < n; j++) {
                int curr_page = frames[j];
                int k;
                int next_pos = -1;

                for (k = i + 1; k < REF_LEN; k++) {
                    if (ref_string[k] == curr_page) {
                        next_pos = k;
                        break;
                    }
                }

                // If not used again, choose immediately
                if (next_pos == -1) {
                    farthest_index = j;
                    farthest_dist  = 100000;  // effectively "infinite"
                    break;
                } else {
                    int dist = next_pos - i;
                    if (dist > farthest_dist) {
                        farthest_dist  = dist;
                        farthest_index = j;
                    }
                }
            }

            replace_index = farthest_index;
        }

        frames[replace_index] = page;

        print_frames(frames, n);
        printf("\tPage Fault\n");
    }

    printf("---------------------------------------------\n");
    printf("Total Page Faults (OPT) = %d\n", page_faults);
}

int main() {
    int n;

    printf("Enter number of memory frames: ");
    scanf("%d", &n);

    if (n <= 0 || n > 20) {
        printf("Invalid number of frames.\n");
        return 0;
    }

    opt(n);

    return 0;
}