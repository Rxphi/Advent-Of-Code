#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)
#define N 200

static FILE *fp;

void openFile();
void readInput();
void solve();
int getNum(int, int);
void printGrid();


char grid[N][N];
int visited[N][N];
int rows = 0;
int cols = 0;

int main()
{
    openFile();

    readInput();

    solve();

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
    int finished = 0;
    char c;
    for (int i = 0; i < N; i++) {
        rows++;

        int countCols = cols == 0;
        for (int j = 0; j < N; j++) {
            c = fgetc(fp);
            if (c == EOF) {
                finished = 1;
                break;
            } else if (c == '\n') {
                grid[i][j] = '\0';
                break;
            } else {
                if (countCols) {cols++;}
                grid[i][j] = c;
            }
        }
        //printf("%s\n", grid[i]);
        if (finished) {
            break;
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            visited[i][j] = 0;
        }
    }
    //printf("rows = %d, cols = %d\n", rows, cols);
    printf("Read input successfully!\n");
}

void solve()
{
    int solutionI = 0;
    long solutionII = 0;

    int finished = 1;
    char c;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            c = grid[i][j];
            if (c == '\0') {
                break;
            } else if ((!isdigit(c)) && (c != '.')){
                int isGear = c == '*';
                int partNum = 0;
                int first = 0;
                int second = 0;
                for (int l = MAX(0, i-1); l < MIN(rows, i+2); l++) {
                    for (int k = MAX(0, j-1); k < MIN(cols, j+2); k++) {
                        if (isdigit(grid[l][k])) {
                            int v = visited[l][k];
                            int num = getNum(l, k);
                            if (!v) {
                                solutionI += num;
                            }

                            if (isGear) {
                                if (first == 0) {
                                    first = num;
                                }
                                second = num;
                                partNum++;
                            }
                        }
                    }
                }

                // adjust partNum
                if (isGear) {
                    int partNumBefore = partNum;
                    if (i == 0) {
                        if (j == 0) {
                            partNum -= isdigit(grid[i+1][j]) && isdigit(grid[i+1][j+1]);
                        } else if (j == cols-1) {
                            partNum -= isdigit(grid[i+1][j]) && isdigit(grid[i+1][j-1]);
                        } else {
                            partNum -= isdigit(grid[i+1][j-1]) && isdigit(grid[i+1][j]);
                            partNum -= isdigit(grid[i+1][j]) && isdigit(grid[i+1][j+1]);
                        }
                    } else if (i == rows-1) {
                        if (j == 0) {
                            partNum -= isdigit(grid[i-1][j]) && isdigit(grid[i-1][j+1]);
                        } else if (j == cols-1) {
                            partNum -= isdigit(grid[i-1][j]) && isdigit(grid[i-1][j-1]);
                        } else {
                            partNum -= isdigit(grid[i-1][j-1]) && isdigit(grid[i-1][j]);
                            partNum -= isdigit(grid[i-1][j]) && isdigit(grid[i-1][j+1]);
                        }
                    } else {
                        if (j == 0) {
                            partNum -= isdigit(grid[i-1][j]) && isdigit(grid[i-1][j+1]);
                            partNum -= isdigit(grid[i+1][j]) && isdigit(grid[i+1][j+1]);
                        } else if (j == cols-1) {
                            partNum -= isdigit(grid[i-1][j]) && isdigit(grid[i-1][j-1]);
                            partNum -= isdigit(grid[i+1][j]) && isdigit(grid[i+1][j-1]);
                        } else {
                            partNum -= isdigit(grid[i-1][j-1]) && isdigit(grid[i-1][j]);
                            partNum -= isdigit(grid[i-1][j]) && isdigit(grid[i-1][j+1]);
                            partNum -= isdigit(grid[i+1][j-1]) && isdigit(grid[i+1][j]);
                            partNum -= isdigit(grid[i+1][j]) && isdigit(grid[i+1][j+1]);
                        }
                    }
                    if (partNum == 2) {
                        solutionII += first * second;
                        //printf("Found gear at (%d, %d), adjusted from %d, adding %d * %d -> %ld\n", i, j, partNumBefore, first, second, solutionII);
                        //grid[i][j] = 'G';
                    } else {
                        //printf("Part (%d, %d), partNum = %d (from %d), is not a gear\n", i, j, partNum, partNumBefore);
                    }
                }

            }
        }
    }

    //printGrid();
    printf("The solution to part I is: %d\n", solutionI);
    printf("The solution to part II is: %ld\n", solutionII);
}


int getNum(int i, int j) {
    int result = 0;
    int startInd = j;

    while (isdigit(grid[i][startInd]) && startInd < cols) {
        startInd++;
    }
    startInd--;
    
    int base = 1;

    for (int l = startInd; l >= 0 && isdigit(grid[i][l]); l--) {
        result += (grid[i][l] - '0') * base;
        visited[i][l] = 1;
        base *= 10;
    }

    return result;
}

void printGrid() {
    printf("Current Grid:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
}