#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 30
#define MAX_M 30
#define MAX_NUM_OF_PATTERNS 300
// #define NUM_OF_ROWS 15
#define NUM_OF_ROWS 1367

struct Pattern {
    int n;
    int m;
    int grid[MAX_N][MAX_M];
    int smudgeFound;
    int smudge1i;
    int smudge1j;
    int smudge2i;
    int smudge2j;
};

int numOfPatterns;
struct Pattern *patterns[MAX_NUM_OF_PATTERNS];
static FILE *fp;

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
    fp = fopen("input.txt", "r");

    if (fp == NULL) {
        perror("The file could not be opened!\n");
        exit(1);
    }
    else {
        printf("Opened input file successfully!\n");
    }
}

void printPattern(struct Pattern * p) {
    printf("%d x %d\n", p->n, p->m);
    for (int i = 0; i < p->n; i++) {
        for (int j = 0; j < p->m; j++) {
            printf("%1d", p->grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void readInput() {
    int rowInd = 0;
    char row[MAX_M];
    int patternInd = 0;

    while (rowInd < NUM_OF_ROWS) {
        struct Pattern *newPattern = (struct Pattern *) calloc(sizeof(struct Pattern) , 1);
        
        fscanf(fp, "%s", row);
        rowInd++;
        newPattern->m = strlen(row);

        for (int j = 0; j < newPattern->m; j++) {
            newPattern->grid[0][j] = ((row[j] == '#') ? 1 : 0);
        }
        newPattern->n++;

        char check [2];
        while (fscanf(fp, "%2c", check) == 1 && check[1] != '\n' && check[1] != EOF) {
            row[0] = check[1];
            fscanf(fp, "%s", &row[1]);
            // printf("%s\n", row);
            rowInd++;

            for (int j = 0; j < newPattern->m; j++) {
                newPattern->grid[newPattern->n][j] = ((row[j] == '#') ? 1 : 0);
            }
            newPattern->n++;
        }
        rowInd++;
        // printf("n x m: %d x %d\n\n", newPattern->n, newPattern->m);
        // printPattern(newPattern);
        patterns[patternInd++] = newPattern;
    }

    numOfPatterns = patternInd;
    printf("Read input successfully!\n");
}

int checkRow(struct Pattern *p, int row1, int row2) {
    int diff = 0;
    for (int j = 0; j < p->m; j++) {
        if (p->grid[row1][j] != p->grid[row2][j]) {
            diff++;
            if (!p->smudgeFound) {
                p->smudge1i = row1;
                p->smudge2i = row2;
                p->smudge1j = p->smudge2j = j;
            }
        }
    }
    return diff;
}

int checkCol(struct Pattern *p, int col1, int col2) {
    int diff = 0;
    for (int i = 0; i < p->n; i++) {
        if (p->grid[i][col1] != p->grid[i][col2]) {
            diff++;
            if (!p->smudgeFound) {
                p->smudge1j = col1;
                p->smudge2j = col2;
                p->smudge1i = p->smudge2i = i;
            }
        }
    }
    return diff;
}

int colReflection(struct Pattern *p, int col1, int col2) {
    int diff = 0;
    while (0 <= col1 && col2 < p->m) {
        diff += checkCol(p, col1, col2);
        col1--;
        col2++;
    }

    if (diff == 1) {
        p->smudgeFound = 1;
    }

    return diff;
}

int rowReflection(struct Pattern *p, int row1, int row2) {
    int diff = 0;
    while (0 <= row1 && row2 < p->n) {
        diff += checkRow(p, row1, row2);
        row1--;
        row2++;
    }

    if (diff == 1) {
        p->smudgeFound = 1;
    }
    return diff;
}

void solvePartI() {
    int solutionI = 0;

    for (int i = 0; i < numOfPatterns; i++) {
        struct Pattern *currentPattern = patterns[i];
        printf("Pattern #%d: ", i+1);
        for (int j = 1; j < currentPattern->m; j++) {
            if (0 == colReflection(currentPattern, j-1, j)) {
                solutionI += j;
                printf("Column Reflection between %d and %d\n", j-1, j);
            }
        }

        for (int j = 1; j < currentPattern->n; j++) {
            if (0 == rowReflection(currentPattern, j-1, j)) {
                solutionI += j * 100;
                printf("Row Reflection between %d and %d\n", j-1, j);
            }
        }
    }
    printf("\nThe solution to part I is: %d\n\n", solutionI);
}

void solvePartII() {
    int solutionII = 0;

    for (int i = 0; i < numOfPatterns; i++) {
        struct Pattern *p = patterns[i];
        printf("Pattern #%d: Smudge at (%d, %d) or (%d, %d)\n", i+1, p->smudge1i, p->smudge1j, p->smudge2i, p->smudge2j);

        if (p->smudge1i == p->smudge2i) {
            solutionII += (p->smudge1j + p->smudge2j) / 2 + 1;
        } else {
            solutionII += ((p->smudge1i + p->smudge2i) / 2 + 1) * 100;
        }
    }
    printf("\nThe solution to part II is: %d\n", solutionII);
}