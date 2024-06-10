#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void FIFO(char * refString, int maxFrames);

int pageFaults = 0;
int hits = 0;

int main(){
    //char str[100];
    char str[] = "12311453";
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

    FIFO(str,size);
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

void FIFO(char * refString, int maxFrames){
    char * memoryPtr[maxFrames];

    // Initialize memory frames to NULL.
    for (int i = 0; i < maxFrames; i++) {
        memoryPtr[i] = NULL;
    }
    int counter = 0;

    // Loop through reference string and check if a hit/page faults occurs.
    // Computer the new string that fits into the specified frame amount.
    for (int i=0; i < strlen(refString);++i){

        if(isHit(refString[i], memoryPtr, maxFrames) == false){
            memoryPtr[counter] = &refString[i];
            counter++;
            if (counter == maxFrames){          //Reset counter.
                    counter = 0;
            }
            pageFaults++;

        }
        else {
            hits++;
        }

        static char result[3];
        for (int i = 0; i < maxFrames; i++) {
            if (memoryPtr[i] != NULL) {
                result[i] = *memoryPtr[i];
                printf("%c",result[i]);
            }
            else if (isHit(refString[i], memoryPtr, maxFrames) == true){
                    printf("-");
            }
            //===========================================================
                // make it so that on hit you get - in the output
                // Finish LRU and OPT tomorrow.
            //===========================================================
            else {
                printf("-");
            }
        }
        printf("\n");
    }
}


