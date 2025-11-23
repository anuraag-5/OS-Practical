#include<stdio.h>
#include<stdlib.h>

int refStr[] = { 12, 15, 12, 18, 6, 8, 11, 12, 19, 12, 6, 8, 12, 15, 19, 8 };
int refLen = 16;

void print_frames(int frames[], int n){
    for(int i = 0; i < n; i++){
        if(frames[i] == -1){
            printf(" - ");
        } else {
            printf(" %d ", frames[i]);
        }
    }
}

int search(int frame, int frames[], int n){
    for(int i = 0; i < n; i++){
        if(frames[i] == frame) return i;
    }
    return -1;
}

void lru(int n){
    int *frames = (int *)malloc(sizeof(int) * n), *last_used = (int *)malloc(sizeof(int) * n), time = 0, page_faults = 0;
    for(int i = 0; i < n; i++) { frames[i] = -1; last_used[i] = -1; };

    for(int i = 0; i < refLen; i++){
        int frame = refStr[i];

        int pos = search(frame, frames, n);

        if(pos != -1) {
            time++;
            last_used[pos] = time;

            print_frames(frames, n);
            printf("\n");
        } else {
            time++;
            page_faults++;

            int replace_index = -1;
            for (int j = 0; j < n; j++) {
                if (frames[j] == -1) {
                    replace_index = j;
                    break;
                }
            }

            if(replace_index != -1) {
                frames[replace_index] = frame;
                last_used[replace_index] = time;
                print_frames(frames, n);
                printf("\n");
                continue;
            }

            // Replace least recently used cause no empty frame available.
            int minLast = last_used[0];
            for(int k = 1; k < n; k++){
                if(last_used[k] < minLast){
                    minLast = last_used[k];
                    replace_index = k;
                }
            }

            frames[replace_index] = frame;
            last_used[replace_index] = time;
            print_frames(frames, n);
            printf("\n");
        }
    }
}

int main(){
    int n;
    printf("Enter number of frames: ");
    scanf("%d", &n);

    lru(n);
    printf("\n");
    return 0;
}