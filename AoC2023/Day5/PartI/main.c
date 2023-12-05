#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define NUM_OF_SEEDS 20
// #define NUM_OF_SEEDS 4

#define NUM_OF_MAPS 7

struct ListNode {
    long val;
    struct ListNode* next;
};

struct Map {
    struct ListNode *destinationRanges;
    struct ListNode *sourceRanges;
    struct ListNode *rangesLength;
};

struct SeedInterval {
    long start;
    long end;
    struct SeedInterval *next;
};

void openFile();
void readInput();
void solvePartI();
struct Map* createNewMap();
struct ListNode* append(struct ListNode *, long);
long convert(struct Map *, long);


struct Map *maps[NUM_OF_MAPS];
long seeds[NUM_OF_SEEDS];

static FILE *fp;


int main() {
    openFile();

    readInput();

    solvePartI();

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

    for (int i = 0; i < NUM_OF_SEEDS; i++) {
        fscanf(fp, "%ld", &seeds[i]);
        // printf("Seed #%d: %ld\n", i+1, seeds[i]);
    }

    char mapName[50];

    for (int i = 0; i < NUM_OF_MAPS; i++) {
        fscanf(fp, "%s map:\n", mapName);
        maps[i] = createNewMap();
    }
    printf("Read input successfully!\n");
}

void solvePartI() {
    long solutionI = LONG_MAX;

    long seedLocations[NUM_OF_SEEDS];

    for (int i = 0; i < NUM_OF_SEEDS; i++) {
        seedLocations[i] = seeds[i];
    }

    // pass every seed through every map
    for (int m = 0; m < NUM_OF_MAPS; m++) {
        // printf("Using map #%d\n", m+1);
        for (int s = 0; s < NUM_OF_SEEDS; s++) {
            seedLocations[s] = convert(maps[m], seedLocations[s]);
        }
    }

    for (int i = 0; i < NUM_OF_SEEDS; i++) {
        solutionI = seedLocations[i] < solutionI ? seedLocations[i] : solutionI;
    }

    printf("The solution to part I is: %ld\n", solutionI);
}

struct Map* createNewMap() {
    // printf("Creating new map\n");
    long dest, source, len;
    fscanf(fp, "%ld %ld %ld\n", &dest, &source, &len);
    
    struct ListNode *destinationRanges = (struct ListNode*) malloc(sizeof(struct ListNode));
    destinationRanges->val = dest;
    struct ListNode *currDestinationRange = destinationRanges;

    struct ListNode *sourceRanges = (struct ListNode*) malloc(sizeof(struct ListNode));
    sourceRanges->val = source;
    struct ListNode *currSourceRanges = sourceRanges;

    struct ListNode *rangesLength = (struct ListNode*) malloc(sizeof(struct ListNode));
    rangesLength->val = len;
    struct ListNode *currRangeLength = rangesLength;
    
    // printf("%ld %ld %ld\n", dest, source, len);
    while (fscanf(fp, "%ld %ld %ld\n", &dest, &source, &len) == 3) {
        currDestinationRange = append(currDestinationRange, dest);
        currSourceRanges = append(currSourceRanges, source);
        currRangeLength = append(currRangeLength, len);

        // printf("%ld %ld %ld\n", dest, source, len);
    }

    struct Map *newmap = (struct  Map *) malloc(sizeof(struct Map));
    newmap->destinationRanges = destinationRanges;
    newmap->sourceRanges = sourceRanges;
    newmap->rangesLength = rangesLength;

    return newmap;
}

struct ListNode* append(struct ListNode *listNodeP, long val) {
    struct ListNode *newNode = (struct ListNode*) malloc(sizeof(struct ListNode));
    newNode->val = val;

    if (listNodeP != NULL) {
        listNodeP->next = newNode;
    }

    return newNode;
}

long convert(struct Map *mapP, long key) {
    long output = key;

    struct ListNode *destinationRange = mapP->destinationRanges;
    struct ListNode *sourceRange = mapP->sourceRanges;
    struct ListNode *rangeLength = mapP->rangesLength;

    while (sourceRange != NULL && ((key < sourceRange->val) || ((sourceRange->val + rangeLength->val) <= key))) {
        destinationRange = destinationRange->next;
        sourceRange = sourceRange->next;
        rangeLength = rangeLength->next;
    }

    if (sourceRange != NULL) {
        //printf("Applying %ld %ld %ld\n", destinationRange->val, sourceRange->val, rangeLength->val);
        output = destinationRange->val + (key - sourceRange->val);
    }

    //printf("%ld -> %ld\n", key, output);
    return output;
}