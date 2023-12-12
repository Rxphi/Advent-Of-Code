#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OF_ROWS 1000
// #define NUM_OF_ROWS 6
#define MAX_NUM_CONDITIONS 30

// structs
struct RowOfSprings {
    int id;
    int numQuestionMarks;
    int numHashTags;
    int numOfGroups;
    int numOfConditions;
    char conditionRecords[MAX_NUM_CONDITIONS];
    int groupSize[MAX_NUM_CONDITIONS];
};

static FILE *fp;
struct RowOfSprings *field[NUM_OF_ROWS];

void openFile();
void readInput();
void solvePartI();
void printRowOfSprings(struct RowOfSprings *);

int main() {
    openFile();

    readInput();

    solvePartI();

    fclose(fp);
    return 0;
}

void openFile() {
    fp = fopen("../input.txt", "r");

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
        int questionMarks = 0;
        int hashtags = 0;
        // SCAN SYMBOLS
        while (fscanf(fp, "%1c", &curr) == 1 && (curr == '.' || curr == '#' || curr == '?')) {
            newSpring->conditionRecords[ind++] = curr;
            if (curr == '?') {
                questionMarks++;
            } else if (curr == '#') {
                hashtags++;
            }
        }

        newSpring->id = i+1;
        newSpring->numOfConditions = ind;
        newSpring->numQuestionMarks = questionMarks;
        newSpring->numHashTags = hashtags;

        ind = 0;

        // SCAN NUMBERS
        int num;
        fscanf(fp, "%d", &num);
        newSpring->groupSize[ind++] = num;

        while (fscanf(fp, "%1c", &curr) == 1 && curr == ',') {
            fscanf(fp, "%d", &num);
            newSpring->groupSize[ind++] = num;
        }
        newSpring->numOfGroups = ind;
        field[i] = newSpring;
    }
    printf("Read input successfully!\n");
}

int valid(char * current, int * groupSizes, int numOfGroups, int len) {
    int ind = 0;
    int currentGroupSize = 0;
    int inGroup = 0;
    int numOfGroupsFound = 0;

    for (int i = 0; i < len; i++) {
        if (current[i] == '.') {
            if (inGroup) {
                numOfGroupsFound++;
                inGroup = 0;
                if (groupSizes[ind] != currentGroupSize) {
                    return 0;
                }
                currentGroupSize = 0;
                ind++;
            }
        } else {
            currentGroupSize++;
            inGroup = 1;
        }
    }

    if (inGroup) {
        if (groupSizes[ind] != currentGroupSize) {
            return 0;
        }
        numOfGroupsFound++;
    }

    if (numOfGroups != numOfGroupsFound) {
        return 0;
    }

    return 1;
}

long numOfArrangements(struct RowOfSprings * r) {
    long arrangements = 0;

    char current[r->numOfConditions];
    memcpy(current, r->conditionRecords, r->numOfConditions);

    for (int i = 0; i < r->numOfConditions; i++) {
        if (current[i] == '?') {
            current[i] = '.';
        }
    }

    if (valid(current, r->groupSize, r->numOfGroups, r->numOfConditions)) {
        arrangements++;
    }

    int possibilities = r->numQuestionMarks == 0 ? 0 : 1 << r->numQuestionMarks;

    for (int i = 0; i < possibilities-1; i++) {
        // incr
        for (int j = r->numOfConditions; j >= 0; j--) {
            if (r->conditionRecords[j] == '?') {
                if (current[j] == '.') {
                    current[j] = '#';
                    break;
                } else {
                    current[j] = '.';
                }
            } 
        }

        // validate
        if (valid(current, r->groupSize, r->numOfGroups, r->numOfConditions)) {
            arrangements++;
        }
    }
    return arrangements;
}

void solvePartI() {
    long solutionI = 0;

    for (int i = 0; i < NUM_OF_ROWS; i++) {
        solutionI += numOfArrangements(field[i]);
    }

    printf("The solution to part I is: %ld\n", solutionI);
}

void printRowOfSprings(struct RowOfSprings * r) {
    printf("ID(%d) ", r->id);
    for (int i = 0; i < r->numOfConditions; i++) {
        printf("%c", r->conditionRecords[i]);
    }

    printf(" %d", r->groupSize[0]);

    for (int i = 1; i < r->numOfGroups; i++) {
        printf(",%d", r->groupSize[i]);
    }

    printf(" #ConditionRecords = %d, #Groups = %d, ?-Count = %d, #-Count = %d\n", r->numOfConditions, r->numOfGroups, r->numQuestionMarks, r->numHashTags);
}