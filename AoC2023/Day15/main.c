#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LABEL_LENGTH 20
struct Lens {
    char label[MAX_LABEL_LENGTH];
    int hashValue;
    int focalLength;
    struct Lens *next;
};

struct Box {
    struct Lens *firstLens;
    int numOfLenses;
};

static FILE *fp;
struct Box boxes[256];

void openFile();
void readInput();
void solvePartI();
void solvePartII();

int main() {
    openFile();

    readInput();

    solvePartI();
    solvePartII();

    fclose(fp);
    return 0;
}

void openFile() {
    fp = fopen("test.txt", "r");

    if (fp == NULL) {
        perror("The file could not be opened!\n");
        exit(1);
    }
    else {
        printf("Opened input file successfully!\n");
    }
}

void readInput() {
    printf("Read input successfully!\n");
}

void solvePartI() {
    int solutionI = 0;

    char curr;
    int hashValue = 0;
    while (fscanf(fp, "%1c", &curr) == 1) {
        if (curr == ',') {
            solutionI += hashValue;
            // printf("%d\n", hashValue);
            hashValue = 0;
        } else {
            hashValue += (int) curr;
            hashValue *= 17;
            hashValue %= 256;
        }
    }
    solutionI += hashValue;
    // printf("%d\n", hashValue);

    printf("The solution to part I is: %d\n", solutionI);
}

void removeLabelFromBox(struct Box *b, char * label) {
    struct Lens *prevLens = NULL;
    struct Lens *currentLens = b->firstLens;

    while (currentLens != NULL) {
        if (!strcmp(currentLens->label , label)) {
            if (prevLens == NULL) {
                b->firstLens = NULL;
            } else {
                prevLens->next = currentLens->next;
            }
            b->numOfLenses--;
            return;
        }
        prevLens = currentLens;
        currentLens = currentLens->next;
    }

    return;
}

void addLensToBox(struct Box *b, struct Lens *newLens) {
    if (b->firstLens == NULL) {
        b->firstLens = newLens;
        b->numOfLenses++;
        return;
    }

    struct Lens *prevLens = NULL;
    struct Lens *currentLens = b->firstLens;

    while (currentLens != NULL) {
        if (!strcmp(currentLens->label, newLens->label)) {
            return;
        }
        prevLens = currentLens;
        currentLens = currentLens->next;
    }

    prevLens->next = newLens;
    b->numOfLenses++;
    return;
}

void solvePartII() {
    openFile();
    long solutionII = 0;

    for (int i = 0; i < 256; i++) {
        boxes[i].firstLens = NULL;
        boxes[i].numOfLenses = 0;
    }

    int hashValue = 0;
    int currentLabelInd = 0;
    char currentLabel[MAX_LABEL_LENGTH];
    char curr;

    while (fscanf(fp, "%1c", &curr) == 1) {
        if (curr == ',') {
            hashValue = 0;
            currentLabelInd = 0;
            continue;
        } else if (curr == '-') {
            currentLabel[currentLabelInd++] = '\0';
            removeLabelFromBox(&boxes[hashValue], currentLabel);
            continue;
        } else if (curr == '=') {
            currentLabel[currentLabelInd++] = '\0';
            
            int focalLength = 0;
            fscanf(fp, "%d", &focalLength);
            
            struct Lens *newLens = (struct Lens *) calloc(sizeof(struct Lens), 1);
            memcpy(newLens->label, currentLabel, currentLabelInd);
            newLens->focalLength = focalLength;
            newLens->hashValue = hashValue;
            newLens->next = NULL;

            addLensToBox(&boxes[hashValue], newLens);

        } else {
            hashValue += (int) curr;
            hashValue *= 17;
            hashValue %= 256;
            currentLabel[currentLabelInd++] = curr;
        }
    }

    // calculate result
    for (int i = 1; i <= 256; i++) {
        struct Box *currBox = &boxes[i-1];

        struct Lens *currLens = currBox->firstLens;
        for (int j = 1; j <= currBox->numOfLenses; j++) {
            solutionII += i * j * currLens->focalLength;
            printf("%s: %d (box %d) * %d (slot #%d) * %d (focal length) = %d\n", currLens->label, i, i-1, j, j, currLens->focalLength, i*j*currLens->focalLength);
            currLens = currLens->next;
        }

    }
    printf("The solution to part II is: %ld\n", solutionII);
}