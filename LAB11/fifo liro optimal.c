#include <stdio.h>

void printFrames(int frames[], int f) {
    for (int i = 0; i < f; i++) {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}

void fifo(int pages[], int n, int f) {
    int frames[f], index = 0, pageFaults = 0;
    for (int i = 0; i < f; i++)
        frames[i] = -1;

    printf("FIFO Page Replacement\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            frames[index] = pages[i];
            index = (index + 1) % f;
            pageFaults++;
        }
        printFrames(frames, f);
    }
    printf("Total Page Faults (FIFO): %d\n", pageFaults);
}

void lru(int pages[], int n, int f) {
    int frames[f], time[f], pageFaults = 0, counter = 0;
    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("LRU Page Replacement\n");
    for (int i = 0; i < n; i++) {
        int found = 0, pos = 0, minTime = counter;

        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                time[j] = counter++;
                break;
            }
        }
        if (!found) {
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
                if (time[j] < minTime) {
                    minTime = time[j];
                    pos = j;
                }
            }
            frames[pos] = pages[i];
            time[pos] = counter++;
            pageFaults++;
        }
        printFrames(frames, f);
    }
    printf("Total Page Faults (LRU): %d\n", pageFaults);
}

void optimal(int pages[], int n, int f) {
    int frames[f], pageFaults = 0;
    for (int i = 0; i < f; i++)
        frames[i] = -1;

    printf("Optimal Page Replacement\n");
    for (int i = 0; i < n; i++) {
        int found = 0, pos = 0, farthest = i;

        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
                int nextUse = n;
                for (int k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k]) {
                        nextUse = k;
                        break;
                    }
                }
                if (nextUse > farthest) {
                    farthest = nextUse;
                    pos = j;
                }
            }
            frames[pos] = pages[i];
            pageFaults++;
        }
        printFrames(frames, f);
    }
    printf("Total Page Faults (Optimal): %d\n", pageFaults);
}

int main() {
    int n, f;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter the page reference sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    fifo(pages, n, f);
    printf("\n");
    lru(pages, n, f);
    printf("\n");
    optimal(pages, n, f);

    return 0;
}
