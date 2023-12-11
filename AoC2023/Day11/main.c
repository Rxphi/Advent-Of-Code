#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Test
// #define N 10
// Input
#define N 140

struct Galaxy {
    int id;
    int i;
    int j;
};

static FILE *fp;

// useful to compute the num of empty rows/cols between two given rows/columns
int prefixSumEmptyRows[N]; 
int prefixSumEmptyCols[N];
int universe[N][N]; // 1 for galaxy, 0 for empty space
struct Galaxy * galaxies[N*N];
int numOfGalaxies = 0;

// functions
void openFile();
void readInput();
void solvePartI();
void solvePartII();
long distanceBetween(struct Galaxy *, struct Galaxy *, long);
void printGalaxy(struct Galaxy *);
struct Galaxy * createNewGalaxy(int , int, int);

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

struct Galaxy * createNewGalaxy(int id, int i, int j) {
    struct Galaxy * galaxy = (struct Galaxy *) calloc(sizeof(struct Galaxy), 1);
    galaxy->id = id;
    galaxy->i = i;
    galaxy->j = j;
    return galaxy;
}

void printGalaxy(struct Galaxy *g) {
    printf("Galaxy #%d at (%d, %d)\n", g->id, g->i, g->j);
}

void readInput() {

    prefixSumEmptyRows[0] = 0;
    prefixSumEmptyCols[0] = 0;

    // read input universe and compute prefixSumEmptyRows
    for (int i = 0; i < N; i++) {
        int rowIsEmpty = 1;
        for (int j = 0; j < N; j++) {
            char cell;
            fscanf(fp, "%c", &cell);
            printf("%c", cell);
            
            if (cell == '#') {
                rowIsEmpty = 0;
                universe[i][j] = 1;
                galaxies[numOfGalaxies] = createNewGalaxy(numOfGalaxies+1, i, j);
                numOfGalaxies++;
            } else {
                universe[i][j] = 0;
            }
        }
        fscanf(fp, "\n");
        printf("\n");

        if (rowIsEmpty) {
            if (i != 0) {
                prefixSumEmptyRows[i] = prefixSumEmptyRows[i-1] + 1;
            } else {
                prefixSumEmptyRows[0]++;
            }
        } else if (i > 0) {
            prefixSumEmptyRows[i] = prefixSumEmptyRows[i-1];
        }
    }

    // compute prefixSumEmptyCols
    for (int j = 0; j < N; j++) {
        int colIsEmpty = 1;
        for (int i = 0; i < N; i++) {
            if (universe[i][j]) {
                colIsEmpty = 0;
                break;
            }
        }
        if (colIsEmpty) {
            if (j != 0) {
                prefixSumEmptyCols[j] = prefixSumEmptyCols[j-1] + 1;
            } else {
                prefixSumEmptyCols[0]++;
            }
        } else if (j > 0) {
            prefixSumEmptyCols[j] = prefixSumEmptyCols[j-1];
        }
    }
    printf("#Galaxy = %d\n", numOfGalaxies);
    printf("Read input successfully!\n");
}

// The expansionCoeff determines by how much an empty row or column gets larger
long distanceBetween(struct Galaxy *g1, struct Galaxy *g2, long expansionCoeff) {
    long dist = 0;
    // Compute manhattan distance
    dist += abs(g2->i - g1->i);
    dist += abs(g2->j - g1->j);
    // Compute num of empty rows and cols between g1 and g2 and inflate according to the expansionCoeff
    dist += abs(prefixSumEmptyRows[g2->i] - prefixSumEmptyRows[g1->i]) * (expansionCoeff - 1);
    dist += abs(prefixSumEmptyCols[g2->j] - prefixSumEmptyCols[g1->j]) * (expansionCoeff - 1);

    return dist;
}

void solvePartI() {
    long solutionI = 0;

    for (int i = 0; i < numOfGalaxies-1; i++) {
        for (int j = i+1; j < numOfGalaxies; j++) {
            long toAdd = distanceBetween(galaxies[i], galaxies[j], 2);
            // printf("Distance between:\n");
            // printGalaxy(galaxies[i]);
            // printGalaxy(galaxies[j]);
            // printf("-> %ld\n", toAdd);
            solutionI += toAdd;
        }
    }
    printf("The solution to part I is: %ld\n", solutionI);
}

void solvePartII() {
    long solutionII = 0;
    for (int i = 0; i < numOfGalaxies-1; i++) {
        for (int j = i+1; j < numOfGalaxies; j++) {
            // expansionCoeff is the only thing that changes in PartII :D
            long toAdd = distanceBetween(galaxies[i], galaxies[j], 1000000); 
            // printf("Distance between:\n");
            // printGalaxy(galaxies[i]);
            // printGalaxy(galaxies[j]);
            // printf("-> %ld\n", toAdd);
            solutionII += toAdd;
        }
    }
    printf("The solution to part II is: %ld\n", solutionII);
}