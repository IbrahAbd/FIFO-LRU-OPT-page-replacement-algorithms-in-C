#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void FIFO(char * refString, int maxFrames);
void LRU(char * refString, int maxFrames);

int pageFaults = 0;
int hits = 0;

int main(){
    //char str[100];
    char str[] = "70120304230321201701";
    //char choice[5];
    char choice[] = "FIFO";
    int size = 0;
    //printf("Enter a reference string with no spaces or commas.\n");
    //fgets(str, sizeof(str), stdin);

    //printf("\nEnter the amount of frames:\n");
    //scanf("%d", &size);
    size = 3;
    //getchar();
    //printf("\nEnter the page replacement algorithm you would like to use (FIFO, LRU, OPT):\n");
    //fgets(choice, sizeof(choice), stdin);

    printf("\n");
    printf("Reference String: %s\n", str);
    printf("Frame Size: %d\n", size);
    printf("Page Replacement Algorithm: %s\n", choice);
    printf("\n");

    LRU(str,size);
    printf("Page faults: %d\n", pageFaults);
    printf("Hits: %d\n", hits);
    return 0;
}

bool isHit(char page, char * frames[], int frameCount){
    // If a hit occurs nothing is changed.
    // If a page fault occurs, frames need to be updated to reflect new change.
    for (int i=0; i < frameCount; ++i){
        if(frames[i] != NULL && *frames[i] == page){
            return true;
        }
    }
    return false;
}

void LRU(char * refString, int maxFrames){

    char * memoryPtr[maxFrames];
    for (int i = 0; i < maxFrames; i++) {
        memoryPtr[i] = NULL;
    }

    char * hitDetection[maxFrames];                       // Array to store hit bits.
    for (int i = 0; i < maxFrames; i++) {
        hitDetection[i] = 0;
    }

    int time = 0;                                         // Simulate time to get the LRU index.

    for (int i = 0; i < strlen(refString); ++i) {
        time++;
        char currentPage = refString[i];                                // Get current page ref.

        if (!isHit(currentPage, memoryPtr, maxFrames)) {                // On page fault.
            int lruIndex = 0;
            for (int j = 1; j < maxFrames; j++) {
                if (hitDetection[j] < hitDetection[lruIndex]) {         // Check for the shortest time and get the matching index.
                    lruIndex = j;
                }
            }

            memoryPtr[lruIndex] = &refString[i];                        // Store address of ref in refstring in memoryPtr with index lruIndex.
            hitDetection[lruIndex] = time;                              // Assign new time to index.
            pageFaults++;

        } else {
            printf("----HIT----\n");                                    // On hit
            for (int t = 0; t < maxFrames; t++) {
                if (memoryPtr[t] != NULL && *memoryPtr[t] == currentPage) {
                    hitDetection[t] = time;
                    break;
                }
            }
            hits++;
        }

        char result[maxFrames];                                     // Temporary array to be returned.
        for (int c = 0; c < maxFrames; c++) {                       // Loop through frames and return their result.
            if (memoryPtr[c] != NULL ) {
                result[c] = *memoryPtr[c];
                printf("%c",result[c]);
            }

        }
        printf("\n");

    }

}


void FIFO(char * refString, int maxFrames){
    char * memoryPtr[maxFrames];

    // Initialize memory frames to NULL.
    for (int i = 0; i < maxFrames; i++) {
        memoryPtr[i] = NULL;
    }
    int counter = 0;
    // Loop through reference string and check if a hit/page faults occurs.
    // Compute the new string that fits into the specified frame amount.
    for (int i=0; i < strlen(refString);++i){
        if(isHit(refString[i], memoryPtr, maxFrames) == false){     // On page fault.
            memoryPtr[counter] = &refString[i];
            counter++;
            if (counter == maxFrames){                              // Reset counter.
                    counter = 0;
            }
            pageFaults++;

        }
        else {                                                      // On hit.
            printf("----HIT----\n");
            hits++;
        }

        static char result[3];                                      // Temporary array to be returned.
        for (int i = 0; i < maxFrames; i++) {                       // Loop through frames and return their result.
            if (memoryPtr[i] != NULL ) {
                result[i] = *memoryPtr[i];
                printf("%c",result[i]);
            }
        }
        printf("\n");
    }
}


