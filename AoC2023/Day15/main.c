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
    struct Lens *lastLens;
    int numOfLenses;
};

static FILE *fp;
struct Box boxes[256];

void openFile();
void readInput();
void solvePartI();
void solvePartII();
void printBoxes();

int main() {
    openFile();

    readInput();

    solvePartI();
    solvePartII();

    fclose(fp);
    return 0;
}

void openFile() {
    fp = fopen("input.txt", "r");

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
    // partI was straight forward
    int solutionI = 0;

    char curr;
    int hashValue = 0;
    while (fscanf(fp, "%1c", &curr) == 1) {
        if (curr == ',') {
            solutionI += hashValue;
            hashValue = 0;
        } else {
            hashValue += (int) curr;
            hashValue *= 17;
            hashValue %= 256;
        }
    }
    solutionI += hashValue;

    printf("The solution to part I is: %d\n", solutionI);
}

void removeLabelFromBox(struct Box *b, char * label) {
    //printf("Removing Lens with label: %s\n", label);
  
    struct Lens *prevLens = NULL;
    struct Lens *currentLens = b->firstLens;

    while (currentLens != NULL) {
        if (!strcmp(currentLens->label , label)) {
            if (b->numOfLenses == 1) {
              b->firstLens = NULL;
              b->lastLens = NULL;
            } else if (b->firstLens == currentLens) {
              b->firstLens = currentLens->next;
            } else if (b->lastLens == currentLens) {
              b->lastLens = prevLens;
            } else {
              prevLens->next = currentLens->next;
            }
            free(currentLens);
            b->numOfLenses--;
            return;
        }
        prevLens = currentLens;
        currentLens = currentLens->next;
    }

    //printf("Did not find label\n");
    return;
}

void addLensToBox(struct Box *b, struct Lens *newLens) {
    struct Lens *currentLens = b->firstLens;
    
    // try to find lens that has the same label in the box
    for (int i = 0; i < b->numOfLenses; i++) {
      if (!strcmp(newLens->label, currentLens->label)) {
        currentLens->focalLength = newLens->focalLength;
        free(newLens);
        return;
      }
      currentLens = currentLens->next;
    }
    
    // insert new lens at the end if we did not find anything before
    if (b->numOfLenses == 0) {
        b->firstLens = b->lastLens = newLens;
        b->numOfLenses++;
        return;
    }
    
    b->lastLens->next = newLens;
    b->lastLens = newLens;
    b->numOfLenses++;
    return;
}

void solvePartII() {
    openFile();
    long solutionII = 0;

    for (int i = 0; i < 256; i++) {
        boxes[i].firstLens = NULL;
        boxes[i].lastLens = NULL;
        boxes[i].numOfLenses = 0;
    }

    int hashValue = 0;
    int currentLabelInd = 0;
    char currentLabel[MAX_LABEL_LENGTH];
    char curr;
    
    // add and remove the lenses
    while (fscanf(fp, "%1c", &curr) == 1) {
        if (curr == ',') {
            hashValue = 0;
            currentLabelInd = 0;
            continue;
        } else if (curr == '-') {
            currentLabel[currentLabelInd++] = '\0';
            removeLabelFromBox(&boxes[hashValue], currentLabel);
            //printf("After \"%s-\":\n", currentLabel);
            //printBoxes();
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
            //printf("After \"%s=%d\":\n", currentLabel, focalLength);
            //printBoxes();
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
            //printf("%s: %d (box %d) * %d (slot #%d) * %d (focal length) = %d\n", currLens->label, i, i-1, j, j, currLens->focalLength, i*j*currLens->focalLength);
            currLens = currLens->next;
        }

    }
    printf("The solution to part II is: %ld\n", solutionII);
}

void printBoxes() {
  for (int i = 0; i < 256; i++) {
    struct Box *currBox = &boxes[i];
    if (currBox->numOfLenses == 0) {
      continue;
    }

    printf("Box %d: ", i);
    struct Lens *currLens = currBox->firstLens;

    for (int i = 0; i < currBox->numOfLenses; i++) {
      printf("[%s %d] ", currLens->label, currLens->focalLength);
      currLens = currLens->next;
    }
    printf("\n");
  }
  printf("\n");
}
