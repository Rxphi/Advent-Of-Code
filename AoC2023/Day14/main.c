#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

char grid[N][N];
static FILE *fp;

void openFile();
void readInput();
void solvePartI();
void solvePartII();
void printGrid(char *, int, int);

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
            grid[i][j] = row[j];
        }
    }
    printf("Read input successfully!\n");
}

void tiltNorth() {
    for (int j = 0; j < N; j++) {
        int i = N-1;
        int roundedRocks = 0;
        while (i >= 0) {
            if (grid[i][j] == '#') {
                for (int k = 0; k < roundedRocks; k++) {
                    grid[i+k+1][j] = 'O';  
                }
                roundedRocks = 0; 
            } else if (grid[i][j] == 'O') {
                grid[i][j] = '.';
                roundedRocks++; 
            } 
            i--;
        }
        
        for (int k = 0; k < roundedRocks; k++) {
            grid[i+k+1][j] = 'O';  
        }
    }
}

void tiltWest() {
    for (int i = 0; i < N; i++) {
        int j = N-1;
        int roundedRocks = 0;
        while (j >= 0) {
            if (grid[i][j] == '#') {
                for (int k = 0; k < roundedRocks; k++) {
                    grid[i][j+k+1] = 'O';  
                }
                roundedRocks = 0; 
            } else if (grid[i][j] == 'O') {
                grid[i][j] = '.';
                roundedRocks++; 
            } 
            j--;
        }
        
        for (int k = 0; k < roundedRocks; k++) {
            grid[i][j+k+1] = 'O';  
        }
    }
}

void tiltSouth() {
    for (int j = 0; j < N; j++) {
        int i = 0;
        int roundedRocks = 0;
        while (i < N) {
            if (grid[i][j] == '#') {
                for (int k = 0; k < roundedRocks; k++) {
                    grid[i-k-1][j] = 'O';  
                }
                roundedRocks = 0; 
            } else if (grid[i][j] == 'O') {
                grid[i][j] = '.';
                roundedRocks++; 
            } 
            i++;
        }
        
        for (int k = 0; k < roundedRocks; k++) {
            grid[i-k-1][j] = 'O';  
        }
    }
}

void tiltEast() {
    for (int i = 0; i < N; i++) {
      int j = 0;
      int roundedRocks = 0;
      while (j < N) {
        if (grid[i][j] == '#') {
            for (int k = 0; k < roundedRocks; k++) {
                grid[i][j-k-1] = 'O';  
            }
            roundedRocks = 0; 
        } else if (grid[i][j] == 'O') {
            grid[i][j] = '.';
            roundedRocks++; 
        } 
        j++;
      }
      for (int k = 0; k < roundedRocks; k++) {
        grid[i][j-k-1] = 'O';  
      }
    }
}

void cycle() {
    tiltNorth();
    tiltWest();
    tiltSouth();
    tiltEast();
}

int northSupportBeamLoad() {
    int load = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 'O') {
                load += N - i;
            }
        }
    }
    return load;
}

void solvePartI() {
    int solutionI = 0;

    tiltNorth();
    printGrid(&grid[0][0], N, N);
    printf("===Tilted North===\n\n");
    solutionI = northSupportBeamLoad();
    
    printf("The solution to part I is: %d\n", solutionI);
}

void solvePartII() {
    int solutionII = 0;
    tiltWest();
    tiltSouth();
    tiltEast();
    
    int cyclesDoneBefore = 1;

    int totalCylces = 1000000000;

    // enter loop
    // 1000 is a random choice but the first few iterations are not yet in the loop
    // I don't record the first 1000 to make sure that all iterations after that are part
    // of the loop
    for (int i = 0; i < 1000; i++) {
        cycle();
        // printf("Load after cycle #%d: %d\n", i+2, northSupportBeamLoad());
        cyclesDoneBefore++;
    }
    
    // Found this value by inspection of the beamLoad after each cycle
    int loadCycleLength = 38; // this value only holds for my input.txt file
    int loadCycle[loadCycleLength];

    for (int i = 0; i < loadCycleLength; i++) {
        loadCycle[i] = northSupportBeamLoad();
        cycle();
        // printf("loadCycle[%d] = %d\n", i, loadCycle[i]);
    }
    
    solutionII = loadCycle[(totalCylces-cyclesDoneBefore) % loadCycleLength];
    printf("The solution to part II is: %d\n", solutionII);
}

void printGrid(char *arr, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%1c", *(arr+j+width*i));
        }
        printf("\n");
    }
    printf("\n");
}