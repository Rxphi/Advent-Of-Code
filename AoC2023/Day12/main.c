#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OF_ROWS 6
#define MAX_NUM_CONDITIONS 20

// structs
struct RowOfSprings {
    int numOfGroups;
    int numOfConditions;
    char conditionRecords[MAX_NUM_CONDITIONS];
    int groupSize[MAX_NUM_CONDITIONS];
};

static FILE *fp;
struct RowOfSprings * field[NUM_OF_ROWS];


void openFile();
void readInput();
void solvePartI();
void solvePartII();
void printRowOfSprings(struct RowOfSprings *);

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
    for (int i = 0; i < NUM_OF_ROWS; i++) {
        struct RowOfSprings * newSpring = (struct RowOfSprings *) calloc(sizeof(struct RowOfSprings), 1);
        char curr = '-';

        int ind = 0;
        while (fscanf(fp, "%1c", &curr) == 1 && (curr == '.' || curr == '#' || curr == '?')) {
            // printf("%c", curr);
            newSpring->conditionRecords[ind++] = curr;
        }

        newSpring->numOfConditions = ind;
        ind = 0;

        int num = -1;
        fscanf(fp, "%1d", &num);
        newSpring->groupSize[ind++] = num;

        // printf(" %d", num);

        while (fscanf(fp, "%1c", &curr) == 1 && curr == ',') {
            fscanf(fp, "%1d", &num);
            newSpring->groupSize[ind++] = num;
            // printf(",%d", num);
        }
        // printf("\n");
        newSpring->numOfGroups = ind;
        field[i] = newSpring;
        printRowOfSprings(newSpring);
    }
    printf("Read input successfully!\n");
}

void solvePartI() {
    int solutionI = 0;
    printf("The solution to part I is: %d\n", solutionI);
}

void solvePartII() {
    int solutionII = 0;
    printf("The solution to part II is: %d\n", solutionII);
}

void printRowOfSprings(struct RowOfSprings * r) {
    for (int i = 0; i < r->numOfConditions; r++) {
        printf("%1c", r->conditionRecords[i]);
    }

    printf(" %1d", r->groupSize[0]);

    for (int i = 1; i < r->numOfGroups; r++) {
        printf(",%1d", r->groupSize[i]);
    }

    printf("#ConditionRecords = %d, #Groups = %d\n", r->numOfConditions, r->numOfGroups);
}