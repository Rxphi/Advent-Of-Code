#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 110
// #define N 10

enum Direction {
    LEFT,
    UP,
    RIGHT,
    DOWN
};

struct Grid {
    char mirrors[N][N];
    int energized[N][N];
    int visitedLEFT[N][N];
    int visitedUP[N][N];
    int visitedRIGHT[N][N];
    int visitedDOWN[N][N];
};

static FILE *fp;
struct Grid grid;


void openFile();
void readInput();
void solvePartI();
void solvePartII();
void printEnergized();
void resetGrid();
char *enumDirToText(enum Direction);

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
    char row[N+1];
    for (int i = 0; i < N; i++) {
        fscanf(fp, "%s", row);
        for (int j = 0; j < N; j++) {
            grid.mirrors[i][j] = row[j];
            grid.energized[i][j] = 0;
            grid.visitedDOWN[i][j] = grid.visitedLEFT[i][j] = grid.visitedRIGHT[i][j] = grid.visitedUP[i][j] = 0;
        }
        printf("%s\n", row);
    }
    printf("\n");
    printf("Read input successfully!\n");
}

// walks the beam along that direction from the start position until it hits a mirror or spiltter, then creates the new beams if necessary
void beam(int starti, int startj, enum Direction dir) {
    // printEnergized();
    int curri = starti;
    int currj = startj;
    int di = 0;
    int dj = 0;

    switch (dir) {
        case LEFT:
            dj = -1;
            break;
        case UP:
            di = -1;
            break;
        case RIGHT:
            dj = 1;
            break;
        case DOWN:
            di = 1;
            break;
    }

    int visitedNew = 0;

    char goThrough = (dir == LEFT || dir == RIGHT) ? '-' : '|';

    while (0 <= curri && curri < N && 0 <= currj && currj < N && (grid.mirrors[curri][currj] == '.' || grid.mirrors[curri][currj] == goThrough)) {
        if (dir == LEFT && !grid.visitedLEFT[curri][currj]) {
            grid.visitedLEFT[curri][currj] = 1;
            visitedNew = 1;
        } else if (dir == UP && !grid.visitedUP[curri][currj]) {
            grid.visitedUP[curri][currj] = 1;
            visitedNew = 1;
        } else if (dir == RIGHT && !grid.visitedRIGHT[curri][currj]) {
            grid.visitedRIGHT[curri][currj] = 1;
            visitedNew = 1;
        } else if (dir == DOWN && !grid.visitedDOWN[curri][currj]) {
            grid.visitedDOWN[curri][currj] = 1;
            visitedNew = 1;
        } 
        grid.energized[curri][currj]++;
        curri += di;
        currj += dj;
    }

    if (0 <= curri && curri < N && 0 <= currj && currj < N) {
        if (dir == LEFT && !grid.visitedLEFT[curri][currj]) {
            grid.visitedLEFT[curri][currj] = 1;
            visitedNew = 1;
        } else if (dir == UP && !grid.visitedUP[curri][currj]) {
            grid.visitedUP[curri][currj] = 1;
            visitedNew = 1;
        } else if (dir == RIGHT && !grid.visitedRIGHT[curri][currj]) {
            grid.visitedRIGHT[curri][currj] = 1;
            visitedNew = 1;
        } else if (dir == DOWN && !grid.visitedDOWN[curri][currj]) {
            grid.visitedDOWN[curri][currj] = 1;
            visitedNew = 1;
        } 
        grid.energized[curri][currj]++;
    }

    // no need to create new beam
    if (!visitedNew) {
        return;
    }

    // recursive call to create new beam
    if (0 <= curri && curri < N && 0 <= currj && currj < N) {
        switch(grid.mirrors[curri][currj]) {
            case '/':
                switch (dir) {
                    case LEFT:
                        beam(curri+1, currj, DOWN);
                        break;
                    case UP:
                        beam(curri, currj+1, RIGHT);
                        break;
                    case RIGHT:
                        beam(curri-1, currj, UP);
                        break;
                    case DOWN:
                        beam(curri, currj-1, LEFT);
                        break;
                }
                break;
            case '\\':
                switch (dir) {
                    case LEFT:
                        beam(curri-1, currj, UP);
                        break;
                    case UP:
                        beam(curri, currj-1, LEFT);
                        break;
                    case RIGHT:
                        beam(curri+1, currj, DOWN);
                        break;
                    case DOWN:
                        beam(curri, currj+1, RIGHT);
                        break;
                }
                break;
            case '-':
            case '|':
                switch (dir) {
                    case LEFT:
                    case RIGHT:
                        beam(curri-1, currj, UP);
                        beam(curri+1, currj, DOWN);
                        break;
                    case UP:
                    case DOWN:
                        beam(curri, currj-1, LEFT);
                        beam(curri, currj+1, RIGHT);
                        break;
                }
                break;
            default:
                printf("Error in reflection!");
                break;
        }
    }
}

int getEnergyLevel() {
    int result = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result += grid.energized[i][j] ? 1 : 0;
        }
    }
    return result;
}

void solvePartI() {
    int solutionI = 0;
    beam(0, 0, RIGHT);
    solutionI = getEnergyLevel();
    printf("The solution to part I is: %d\n", solutionI);
}

void resetGrid() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grid.energized[i][j] = 0;
            grid.visitedDOWN[i][j] = grid.visitedLEFT[i][j] = grid.visitedRIGHT[i][j] = grid.visitedUP[i][j] = 0;
        }
    }
}

void solvePartII() {
    int solutionII = 0;

    int besti, bestj;
    enum Direction bestdir;

    resetGrid();
    // start beam at the top row going DOWN
    for (int j = 0; j < N; j++) {
        beam(0, j, DOWN);
        int energy = getEnergyLevel();
        // printf("Start at (%d, %d) going DOWN -> %d\n", 0, j, energy);
        if (solutionII < energy) {
            solutionII = energy;
            besti = 0;
            bestj = j;
            bestdir = DOWN;
        }  
        resetGrid();
    }
    // start beam at the bottom row going UP
    for (int j = 0; j < N; j++) {
        beam(N-1, j, UP);
        int energy = getEnergyLevel();
        // printf("Start at (%d, %d) going UP -> %d\n", N-1, j, energy);
        if (solutionII < energy) {
            solutionII = energy;
            besti = N-1;
            bestj = j;
            bestdir = UP;
        }  
        resetGrid();
    }
    // start beam at the left column going RIGHT
    for (int i = 0; i < N; i++) {
        beam(i, 0, RIGHT);
        int energy = getEnergyLevel();
        // printf("Start at (%d, %d) going RIGHT -> %d\n", i, 0, energy);
        if (solutionII < energy) {
            solutionII = energy;
            besti = i;
            bestj = 0;
            bestdir = RIGHT;
        }  
        resetGrid();
    }
    // start beam at the right column going LEFT
    for (int i = 0; i < N; i++) {
        beam(i, N-1, LEFT);
        int energy = getEnergyLevel();
        // printf("Start at (%d, %d) going LEFT -> %d\n", i, N-1, energy);
        if (solutionII < energy) {
            solutionII = energy;
            besti = i;
            bestj = N-1;
            bestdir = LEFT;
        }  
        resetGrid();
    }
    printf("Best starting position at (%d, %d) going %s\n", besti, bestj, enumDirToText(bestdir));
    printf("The solution to part II is: %d\n", solutionII);
}

void printEnergized() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid.energized[i][j]) {
                printf("%1d", grid.energized[i][j]);
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
    printf("\n");
}

char * enumDirToText(enum Direction dir) {
    switch (dir) {
        case LEFT:
            return "LEFT";
        case RIGHT:
            return "RIGHT";
        case DOWN:
            return "DOWN";
        case UP:
            return "UP";
    }
    return NULL;
}