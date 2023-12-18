#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define N 10
// #define INPUT_ROWS 14

#define N 750
#define INPUT_ROWS 618

char pool[N][N];
static FILE *fp;

void openFile();
void readInput();
void solvePartI();
void solvePartII();
void printPool();

int main() 
{
    openFile();

    readInput();

    solvePartI();
    solvePartII();

    fclose(fp);
    return 0;
}

void openFile()
{
    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        perror("The file could not be opened!\n");
        exit(1);
    }
    else
    {
        printf("Opened input file successfully!\n");
    }
}

void readInput()
{
    int maxi = 0;
    int maxj = 0;

    int curri = N/2;
    int currj = N/2;
    // int curri = 0;
    // int currj = 0;

    char rgb[10];

    for (int i = 0; i < INPUT_ROWS; i++) {
        char dir;
        int meters;
        fscanf(fp, "%1c %d", &dir, &meters);
        fscanf(fp, "%s\n", &rgb[0]);

        int di;
        int dj;

        switch (dir)
        {
            case 'R':
                dj = 1;
                di = 0;
                break;
            case 'U':
                di = -1;
                dj = 0;
                break;
            case 'L':
                dj = -1;
                di = 0;
                break;
            case 'D':
                dj = 0;
                di = 1;
                break;
        }
        for (int j = 0; j < meters; j++) {
            curri += di;
            currj += dj;
            pool[curri][currj] = dir;

            maxi = curri > maxi ? curri : maxi;
            maxj = currj > maxj ? currj : maxj;
        }
        printf("%1c %d -> (%d, %d)\n",dir, meters, maxi, maxj);
    }
    printPool();
    printf("Read input successfully!\n");
}

void solvePartI()
{
    int solutionI = 0;

    for (int i = 0; i < N; i++) {
        int inside = 0;
        int startAbove = -1;
        int endAbove = -1;

        int j = 0;
        while (j < N) {
            if (pool[i][j] == 'U') {
                printf("#");
                solutionI++;
                j++;
                while (pool[i][j] == 'R') {
                    printf("#");
                    solutionI++;
                    j++;
                }
                if (pool[i-1][j-1] == 'U') {
                    inside = inside ? 0 : 1;
                }
            } else if (pool[i][j] == 'L') {
                printf("#");
                startAbove = pool[i-1][j] == 'U' ? 1 : 0;
                solutionI++;
                j++;
                while (pool[i][j] == 'L') {
                    printf("#");
                    solutionI++;
                    j++;
                }
                if (pool[i][j] == 'D') {
                    endAbove = 1;
                } else if (pool[i][j] == 'U') {
                    endAbove = 0;
                }
                printf("#");
                solutionI++;
                j++;
                if (startAbove ^ endAbove) {
                    inside = inside ? 0 : 1;
                }
            } else if (pool[i][j] == 'D') {
                printf("#");
                solutionI++;
                j++;
                while (pool[i][j] == 'R') {
                    printf("#");
                    solutionI++;
                    j++;
                }
                if (pool[i+1][j-1] == 'D') {
                    inside = inside ? 0 : 1;
                }
            } else {
                solutionI += inside;
                j++;
                if (inside) {
                    printf("#");
                } else {
                    printf(".");
                }
            }

        }
        printf("\n");
    }
    printf("The solution to part I is: %d\n", solutionI);
}

void solvePartII()
{
    int solutionII = 0;
    printf("The solution to part II is: %d\n", solutionII);
}

void printPool() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (pool[i][j] != '\0') {
                printf("%1c", pool[i][j]);
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
    printf("\n");
}