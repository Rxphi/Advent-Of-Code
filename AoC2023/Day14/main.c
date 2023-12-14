#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10
//#define N 100

#define PRINT 1
#define PRINT_ROTATIONS 0

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
        int free = -1;
        for (int i = 0; i < N; i++) {
            if (grid[i][j] == '.' && free == -1) {
                free = i;
            } else if (grid[i][j] == '#') {
                free = -1;
            } else if (grid[i][j] == 'O' && free != -1 && free < i) {
                grid[free][j] = 'O';
                grid[i][j] = '.';
                for (int k = free+1; k <= i; k++) {
                    if (grid[k][j] == '.') {
                        free = k;
                        break;
                    }
                }
            }
        }
    }
    printf("===Tilted North===\n");
    printGrid(&grid[0][0], N, N);
}

void tiltWest() {
    for (int i = 0; i < N; i++) {
        int free = -1;
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == '.' && free == -1) {
                free = j;
            } else if (grid[i][j] == '#') {
                free = -1;
            } else if (grid[i][j] == 'O' && free != -1 && free < j) {
                grid[i][free] = 'O';
                grid[i][j] = '.';
                for (int k = free+1; k < N; k++) {
                    if (grid[i][k] == '.') {
                        free = k;
                        break;
                    }
                }
            }
        }
    }
    printf("===Tilted West===\n");
    printGrid(&grid[0][0], N, N);
}

void tiltSouth() {
    for (int j = 0; j < N; j++) {
        int free = -1;
        for (int i = N-1; i >= 0; i--) {
            if (grid[i][j] == '.' && free == -1) {
                free = i;
            } else if (grid[i][j] == '#') {
                free = -1;
            } else if (grid[i][j] == 'O' && free != -1 && i < free) {
                grid[free][j] = 'O';
                grid[i][j] = '.';
                for (int k = free-1; k >= 0; k--) {
                    if (grid[k][j] == '.') {
                        free = k;
                        break;
                    }
                }
            }
        }
    }
    printf("===Tilted South===\n");
    printGrid(&grid[0][0], N, N);
}

void tiltEast() {
    /*
    for (int i = 0; i < N; i++) {
        int free = -1;
        for (int j = N-1; j >= 0; j--) {
            if (grid[i][j] == '.' && free == -1) {
                free = j;
            } else if (grid[i][j] == '#') {
                free = -1;
            } else if (grid[i][j] == 'O' && j < free) {
                grid[i][free] = 'O';
                grid[i][j] = '.';
                for (int k = free-1; k >= 0; k--) {
                    if (grid[i][k] == '.') {
                        free = k;
                        break;
                    }
                }
            }
        }
    }
    */
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
    printf("===Tilted East===\n");
    printGrid(&grid[0][0], N, N);
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
    solutionI = northSupportBeamLoad();
    
    //printGrid(&grid[0][0], N, N);
    printf("The solution to part I is: %d\n", solutionI);
}

void solvePartII() {
    int solutionII = 0;
    tiltWest();
    tiltSouth();
    tiltEast();
    
    /*
    printf("After cycle 1:\n");
    printGrid(&grid[0][0], N, N);
    //for (int i = 0; i < 1000000000-1; i++) {
    for (int i = 0; i < 2; i++) {
        cycle();
        printf("After cycle %d:\n", i+2);
        printGrid(&grid[0][0], N, N);
        if (i % 1000000 == 0) {
            printf("%d\n", i);
        }
    }
    */

    solutionII = northSupportBeamLoad();
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
