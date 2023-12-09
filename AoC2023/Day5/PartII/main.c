#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OF_MAPS 7

#define NUMS_ON_FIRST_LINE 20
// #define NUMS_ON_FIRST_LINE 4

#define LARGEST_MAP 100

// global variables
static FILE *fp;
struct AllMaps allmaps; // stores the references to the 7 maps
struct IntervalLL intervalLL; // Linked List of all Intervals that need to be processed

// functions
void openFile();
void readInput();
void solvePartII();
struct Interval * createNewInterval(long, long);
void enqueue(struct IntervalLL *, struct Interval *);
struct Interval * pop(struct IntervalLL *);
void printInterval(struct Interval *);

// structs
struct Interval {
    // start and end are inclusive
    long start;
    long end;
    long length;
    struct Interval *next;
};

struct IntervalLL {
    struct Interval *first;
    struct Interval *last;
    long numOfIntervals;
};

struct Map {
    long numOfIntervalsMoved;
    long *destinationStarts;
    long *sourceRangeStarts;
    long *rangeLengths;
};

struct AllMaps {
    struct Map * maps[7];
};

void printInterval(struct Interval * interval) {
    printf("Interval of length %ld [%ld, ..., %ld]\n", interval->length, interval->start, interval->end);
}

struct Interval * createNewInterval(long start, long length) {
    struct Interval * newInterval = (struct Interval *) calloc(sizeof(struct Interval), 1);
    newInterval->start = start;
    newInterval->end = start + length - 1;
    newInterval->length = length;
    return newInterval;
}

struct Map * createNewMap() {
    struct Map * newMap = (struct Map *) calloc(sizeof(struct Map), 1);
    long dest, source, len;
    dest = source = len = 0;
    newMap->destinationStarts = (long *) calloc(sizeof(long), LARGEST_MAP);
    newMap->sourceRangeStarts = (long *) calloc(sizeof(long), LARGEST_MAP);
    newMap->rangeLengths = (long *) calloc(sizeof(long), LARGEST_MAP);
    int ind = 0;
    while(fscanf(fp, "%ld %ld %ld\n", &dest, &source, &len) == 3) {
        newMap->destinationStarts[ind] = dest;
        newMap->sourceRangeStarts[ind] = source;
        newMap->rangeLengths[ind] = len;
        ind++;
        // printf("%ld %ld %ld\n", dest, source, len);
    }
    newMap->numOfIntervalsMoved = ind;
    // printf("Created new map, size = %d!\n", ind);
    return newMap;
}

struct Interval * pop(struct IntervalLL * ll) {
    if (ll->numOfIntervals == 0) {
        printf("Cannot pop Interval from empty IntervalLL!");
        exit(1);
    } 
    struct Interval * output = ll->first;
    ll->numOfIntervals--;
    if (ll->numOfIntervals == 0) {
        ll->first = NULL;
        ll->last = NULL;
    } else {
        ll->first = output->next;
    }
    return output;
}

void enqueue(struct IntervalLL * ll, struct Interval * toAdd) {
    if (ll->numOfIntervals == 0) {
        ll->first = toAdd;
        ll->last = toAdd;
        ll->numOfIntervals++;
        return;
    }
    ll->numOfIntervals++;
    ll->last->next = toAdd;
    ll->last = toAdd;
}

void applyMap(struct IntervalLL * ll, struct Map * map) {
    int numToProcess = ll->numOfIntervals;

    for (int i = 0; i < numToProcess; i++) {
        struct Interval * interval = pop(ll);

        struct IntervalLL * intervalsToProcess = (struct IntervalLL *) calloc(sizeof(struct IntervalLL), 1);

        enqueue(intervalsToProcess, interval);

        // printf("Processing: ");
        while(intervalsToProcess->numOfIntervals > 0) {
            struct Interval * toProcess = pop(intervalsToProcess);
            // printInterval(toProcess);

            long startInt = toProcess->start;
            long endInt = toProcess->end;
            long length = toProcess->length;

            int mapped = 0;
            // check if this interval gets mapped somewhere else
            for (int j = 0; j < map->numOfIntervalsMoved; j++) {
                long startMap = map->sourceRangeStarts[j];
                long endMap = startMap + map->rangeLengths[j] - 1;

                // Case 1. Map is to the left of the interval
                if (endMap < startInt) {
                    continue;
                // Case 2. Map overlaps the left part of the interval
                } else if (startMap <= startInt && startInt <= endMap && endMap < endInt) {
                    long overlap = endMap - startInt + 1;
                    enqueue(ll, createNewInterval(map->destinationStarts[j] + startInt - startMap, overlap));
                    // printf("Case 2-> ");
                    // printInterval(ll->last);
                    enqueue(intervalsToProcess, createNewInterval(startInt+overlap, length-overlap));
                    mapped = 1;
                    break;
                // Case 3. Map is entirely inside the interval
                } else if (startInt < startMap && endMap < endInt) {
                    enqueue(ll, createNewInterval(map->destinationStarts[j], map->rangeLengths[j]));
                    // printf("Case 3-> ");
                    // printInterval(ll->last);
                    enqueue(intervalsToProcess, createNewInterval(startInt, startMap - startInt));
                    enqueue(intervalsToProcess, createNewInterval(startMap + map->rangeLengths[j], endInt - endMap));
                    mapped = 1;
                    break;
                // Case 4. Interval is entirely inside the map
                } else if (startMap <= startInt && endInt <= endMap) {
                    enqueue(ll, createNewInterval(map->destinationStarts[j] + startInt - startMap, length));
                    // printf("Case 4-> ");
                    // printInterval(ll->last);
                    mapped = 1;
                    break; 
                // Case 5. Map overlaps with the right part of the interval
                } else if (startInt < startMap && startMap <= endInt && endInt <= endMap) {
                    long overlap = endInt - startMap + 1;
                    enqueue(ll, createNewInterval(map->destinationStarts[j], overlap));
                    // printf("Case 5 -> ");
                    // printInterval(ll->last);
                    enqueue(intervalsToProcess, createNewInterval(startInt, length - overlap));
                    mapped = 1;
                    break;
                } else if (endInt < startMap) {
                    continue;
                } else {
                    printf("Don't know where to put this interval!!!\n");
                }
            }

            if (!mapped) {
                // map to the same interval
                enqueue(ll, toProcess);
                // printf("Case Identity -> ");
                // printInterval(ll->last);
            } else {
                free(toProcess);
            }
        }
    }
}

int main() {
    openFile();

    readInput();

    solvePartII();

    fclose(fp);
    return 0;
}

void openFile() {
    fp = fopen("../input.txt", "r");

    if (fp == NULL) {
        perror("The file could not be opened!\n");
        exit(1);
    } else {
        printf("Opened input file successfully!\n");
    }
}

void readInput() {
    // read and create seed-intervals
    fscanf(fp, "seeds: ");
    for (int i = 0; i < NUMS_ON_FIRST_LINE; i += 2) {
        long start, length;
        start = length = 0;

        fscanf(fp, "%ld %ld", &start, &length);
        struct Interval * newInterval = createNewInterval(start, length);
        enqueue(&intervalLL, newInterval);
    }
    fscanf(fp, "\n\n");

    // read and create maps
    char mapName[30];
    for (int i = 0; i < NUM_OF_MAPS; i++) {
        fscanf(fp, "%s map:\n", mapName);
        struct Map * newMap = createNewMap();
        allmaps.maps[i] = newMap;
    }

    printf("Read input successfully!\n");
}

void solvePartII() {
    long solutionII = __LONG_MAX__;

    // apply all the maps to the intervals
    for (int i = 0; i < NUM_OF_MAPS; i++) {
        printf("\nApplying map #%d\n", i+1);
        applyMap(&intervalLL, allmaps.maps[i]);
    }

    // get minimum start value of Interval in intervalLL
    while (intervalLL.numOfIntervals > 0) {
        struct Interval * curr = pop(&intervalLL);

        if (curr->start < solutionII) {
            solutionII = curr->start;
        }
    }

    printf("\nThe solution to part II is: %ld\n", solutionII);
}