#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define NUMS_IN_FIRST_LINE 2
// #define NUMS_IN_FIRST_LINE 6
#define NUM_OF_MAPS 7
// N should be at least 2 + max(num of intervals remapped in a map)
#define N 400

#define M 100


#define MAX (a, b) (a > b ? a : b)

// Structures
struct Map {
    long destinations[M];
    long sources[M];
    long lengths[M];
    int numOfIntervals;
};

struct SeedInterval {
    long start;
    long end;
    long length;
};

// Functions
void openFile();
void readInput();
void solvePartII();
struct Map* createNewMap();
struct SeedInterval* newSeedInterval(long, long);
void process(struct Map*);
void printInterval(struct SeedInterval *);


void printMap(struct Map *mapP);
void printArr(long *, int);
long min(long, long);
long max(long, long);

// Global variables
struct Map *maps[NUM_OF_MAPS];
long numOfSeedIntervals = NUMS_IN_FIRST_LINE / 2;
struct SeedInterval *seedIntervals[N*N];
struct SeedInterval *newIntervals[N*N];

static FILE *fp;

int main() {
    openFile();

    readInput();

    solvePartII();

    fclose(fp);
    return 0;
}

void openFile() {
    fp = fopen("../input.txt", "r");

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

void readInput() {
    fscanf(fp, "seeds: ");

    // read seed intervals in the first line
    for (int i = 0; i < NUMS_IN_FIRST_LINE/2; i++) {
        long start, len;
        fscanf(fp, "%ld %ld", &start, &len);
        seedIntervals[i] = newSeedInterval(start, len);
    }

    // read maps in the lines below
    char mapName[50];
    for (int i = 0; i < NUM_OF_MAPS; i++) {
        fscanf(fp, "%s map:\n", mapName);
        maps[i] = createNewMap();
    }

    printf("Read input successfully!\n");
}

void solvePartII() {
    long solutionII = LONG_MAX;

    printf("%ld\n", numOfSeedIntervals);

    for (int i = 0; i < NUM_OF_MAPS; i++) {
        process(maps[i]);
        printf("%ld\n", numOfSeedIntervals);
    }

    // get minimum
    for (int i = 0; i < numOfSeedIntervals; i++) {
        // printInterval(seedIntervals[i]);
        if (seedIntervals[i]->start < solutionII) {
            solutionII = seedIntervals[i]->start;
        }
    }
    
    printf("The solution to part II is: %ld\n", solutionII);
}

// changes the value of global variable "numOfSeedIntervals"
void process(struct Map* map) {
    int ind = 0;

    for (int i = 0; i < numOfSeedIntervals; i++) {
        struct SeedInterval* currInterval = seedIntervals[i];
        long startInt = currInterval->start;
        long endInt = currInterval->end;

        for (int j = 0; j < map->numOfIntervals-1; j++) {
            long startMap = map->sources[j];
            long endMap = map->sources[j] + map->lengths[j] - 1;

            if (endMap < startInt) {
                continue;
            } else if (endInt < startMap) {
                break;
            } else if (startMap <= startInt && endInt <= endMap) {
                // move entire interval
                newIntervals[ind++] = newSeedInterval(map->destinations[j] + (startInt - startMap), currInterval->length);
                break;
            } else if (startInt <= startMap && endMap <= endInt) {
                // move entire map
                newIntervals[ind++] = newSeedInterval(map->destinations[j], map->lengths[j]);
            } else if (startMap <= startInt) {
                // move left part of the interval
                newIntervals[ind++] = newSeedInterval(map->destinations[j] + (startInt - startMap), endMap - startInt + 1);
            } else if (endInt <= endMap) {
                // move right part of the interval
                newIntervals[ind++] = newSeedInterval(map->destinations[j], endInt - startMap + 1);
            }
        }

        if (currInterval->start >= map->sources[map->numOfIntervals-1]) {
            // create new interval
            newIntervals[ind++] = newSeedInterval(currInterval->start, currInterval->length);
        } else if (currInterval->end >= map->sources[map->numOfIntervals-1]) {
            // create new interval
            newIntervals[ind++] = newSeedInterval(map->sources[map->numOfIntervals-1], currInterval->end - map->sources[map->numOfIntervals-1] + 1);
        }

        free(currInterval);
    }
    numOfSeedIntervals = ind;
    memcpy(seedIntervals, newIntervals, N*N*sizeof(struct SeedInterval *));
}

struct Map* createNewMap() {
    printf("Creating new map\n");

    struct Map *newmap = (struct  Map *) calloc(sizeof(struct Map), 1);
    
    int ind = 0;
    long dest, source, len;

    long unsortedDestinations[M];
    long unsortedSources[M];
    long unsortedLengths[M];

    while (fscanf(fp, "%ld %ld %ld\n", &dest, &source, &len) == 3) {
        // printf("%ld %ld %ld\n", dest, source, len);
        unsortedDestinations[ind] = dest;
        unsortedSources[ind] = source;
        unsortedLengths[ind] = len;
        ind++;
    }

    int numOfRemappingIntervals = ind;
    int used[numOfRemappingIntervals];
    for (int i = 0; i < numOfRemappingIntervals; i++) used[i] = 0;

    long start = 0;
    long nextStart = 0;

    for (int i = 0; i < M; i++) {
        nextStart = LONG_MAX;
        int nextInd = -1;
        for (int j = 0; j < numOfRemappingIntervals; j++) {
            if (used[j]) {
                continue;
            } else if (unsortedSources[j] >= start && unsortedSources[j] < nextStart) {
                nextInd = j;
                nextStart = unsortedSources[j];
            }
        }

        // printf("Start: %ld, NextStart: %ld, nextInd: %d\n", start, nextStart, nextInd);

        if (nextInd == -1) {
            // printf("fill rest\n");
            int lastStart = newmap->sources[i-1] + newmap->lengths[i-1];
            newmap->destinations[i] = lastStart;
            newmap->sources[i] = lastStart;
            newmap->lengths[i] = LONG_MAX;
            newmap->numOfIntervals = i+1;
            for (int j = i+1; j < M; j++) {
                newmap->destinations[j] = -1;
                newmap->sources[j] = -1;
                newmap->lengths[j] = -1;
            }
            break;
        }

        if (start == unsortedSources[nextInd]) {
            // printf("Perfect ind: %d\n", nextInd);
            newmap->destinations[i] = unsortedDestinations[nextInd];
            newmap->sources[i] = unsortedSources[nextInd];
            newmap->lengths[i] = unsortedLengths[nextInd];
            used[nextInd] = 1;
        } else {
            // printf("Insert identity\n");
            newmap->destinations[i] = start;
            newmap->sources[i] = start;
            newmap->lengths[i] = nextStart-start;
        }
        start = newmap->sources[i] + newmap->lengths[i];
    }

    // printMap(newmap);
    return newmap;
}

struct SeedInterval* newSeedInterval(long start, long len) {
    //printf("Creating new seed interval with start: %ld, length: %ld\n", start, len);

    struct SeedInterval* output = (struct SeedInterval*) malloc(sizeof(struct SeedInterval));
    output->start = start;
    output->end = start+len-1;
    output->length = len;
} 

void printMap(struct Map *mapP) {
    printf("Destinations: ");
    printArr(mapP->destinations, M);
    printf("Sources:      ");
    printArr(mapP->sources, M);
    printf("Lengths:      ");
    printArr(mapP->lengths, M);
    printf("#intervals = %d\n\n", mapP->numOfIntervals);
}

void printArr(long *arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%5ld ", arr[i]);
    }
    printf("\n");
}

void printInterval(struct SeedInterval *p) {
    printf("[%ld <-> %ld]\n", p->start, p->end);
}

long min(long x, long y) {
    return x < y ? x : y;
}

long max(long x, long y) {
    return x > y ? x : y;
}