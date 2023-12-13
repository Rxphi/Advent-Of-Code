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
};

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
        printPattern(newPattern);
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