#include <stdio.h>
#include <stdbool.h>

int pageFaults = 0;
int hits = 0;

int main(){
    char str[100];
    char choice[5];

    int size = 0;


    printf("Enter a reference string. Separate them by a space or comma.\n");
    fgets(str, sizeof(str), stdin);

    printf("\nEnter the amount of frames:\n");
    scanf("%d", &size);

    getchar();

    printf("\nEnter the page replacement algorithm you would like to use (FIFO, LRU, OPT):\n");
    fgets(choice, sizeof(choice), stdin);

    printf("\n");

    printf("Reference String: %s", str);
    printf("Frame Size: %d\n", size);
    printf("Page Replacement Algorithm: %s\n", choice);

    return 0;
}

bool isHit(int page, char frames[], int frameCount){
    for (int i=0; i < frameCount; ++i){
        if(frames[i] == page){
            hits++;
            return true;
        }
    }
    pageFaults++;
    return false;
}

void FIFO(const char * refString, int maxFrames){
    char * memory[maxFrames];











}
