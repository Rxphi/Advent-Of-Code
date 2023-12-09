#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINES 200
#define NUM_PER_LINES 21

// #define LINES 3
// #define NUM_PER_LINES 6

static FILE *fp;

void openFile();
void readInput();
long solvePartI();
long solvePartII();
void printArr(long *, int);
int allZeros(long *, int);
long nextNum(long *);
long prevNum(long *);

long input[LINES][NUM_PER_LINES];

int main() {
    openFile();

    readInput();

    long solutionI = solvePartI();
    long solutionII = solvePartII();

    printf("The solution to part I is %ld\n", solutionI);
    printf("The solution to part II is %ld\n", solutionII);

    fclose(fp);
    return 0;
}

void openFile() {
    fp = fopen("input.txt", "r");

    if (fp == NULL) {
        perror("The file could not be opened!\n");
        exit(1);
    }
    else
    {
        printf("Opened input file successfully!\n");
    }
}

void readInput() {
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < NUM_PER_LINES-1; j++) {
            fscanf(fp, "%ld ", &input[i][j]);
        }
        fscanf(fp, "%ld\n", &input[i][NUM_PER_LINES-1]);
    }

    printf("Read input successfully!\n");
}

long nextNum(long *line) {
    long lastNum[NUM_PER_LINES];

    int n = NUM_PER_LINES;
    long diff[NUM_PER_LINES];
    memcpy(diff, line, sizeof(long)*NUM_PER_LINES);

    while (!allZeros(diff, n)) {
        // printArr(diff, n);
        n--;
        lastNum[n] = diff[n];
        for (int i = 0; i < n; i++) {
            diff[i] = diff[i+1] - diff[i];
        }
    }
    n--;
    lastNum[n] = diff[n];
    
    // printf("n = %d, Last nums: ", n);
    // printArr(&lastNum[n], NUM_PER_LINES-n);

    long prediction = 0;

    for (int i = n; i < NUM_PER_LINES; i++) {
        prediction += lastNum[i];
    }

    // printf("Prediction = %ld\n", prediction);
    return prediction;
}

long prevNum(long *line) {
    long first[NUM_PER_LINES];

    int n = NUM_PER_LINES;
    long diff[NUM_PER_LINES];
    memcpy(diff, line, sizeof(long)*NUM_PER_LINES);

    while (!allZeros(diff, n)) {
        // printArr(diff, n);
        n--;
        first[n] = diff[0];
        for (int i = 0; i < n; i++) {
            diff[i] = diff[i+1] - diff[i];
        }
    }
    n--;
    first[n] = diff[n];
    
    // printf("n = %d, First nums: ", n);
    // printArr(&first[n], NUM_PER_LINES-n);

    long prediction = 0;

    for (int i = n; i < NUM_PER_LINES; i++) {
        prediction = first[i] - prediction;
    }

    // printf("Prediction = %ld\n", prediction);
    return prediction;
}

int allZeros(long *check, int n) {
    for (int i = 0; i < n; i++) {
        if (check[i] != 0) {
            return 0;
        }
    }
    return 1;
}

void printArr(long *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%6ld ", arr[i]);
    }
    printf("\n");
}

long solvePartI() {
    long solutionI = 0;

    for (int i = 0; i < LINES; i++) {
        // printf("\nLooking at line #%d\n", i+1);
        solutionI += nextNum(input[i]);
    }

    return solutionI;
}

long solvePartII() {
    long solutionII = 0;
    for (int i = 0; i < LINES; i++) {
        // printf("\nLooking at line #%d\n", i+1);
        solutionII += prevNum(input[i]);
    }
    return solutionII;
}