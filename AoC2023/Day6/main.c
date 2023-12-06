#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define RACES 4

// Global variables
static FILE *fp;
// int times[RACES] = {7, 15, 30};
// int distances[RACES] = {9, 40, 200};
int times[RACES] = {42, 68, 69, 85};
int distances[RACES] = {284, 1005, 1122, 1341};

// Structures

// Functions
void openFile();
void readInput();
void solvePartI();
void solvePartII();
long numOfWaysToWin(long, long);
double sqrt(double);

void solvePartI()
{
    int solutionI = 1;

    for (int i = 0; i < RACES; i++) {
        solutionI *= numOfWaysToWin(times[i], distances[i]);
    }

    printf("The solution to part I is: %d\n\n", solutionI);
}

long numOfWaysToWin(long time, long currentRecord) {
    long result;

    double det = time * time - 4.0 * currentRecord;
    double thalf = time / 2.0;

    if (det <= 0.0) {
        result = 0;
    } else {
        det = sqrt(det);
        det /= -2.0;
        double t1 = thalf + det;
        double t2 = thalf - det;

        printf("[%f, ... , %f]\n", t1, t2);

        long rt1 = (long) t1+1;
        long rt2 = (long) t2;
        result = rt2 - rt1 + 1;

        if (t2 == ((long) t2)) {
            result--;
        }
    }

    printf("T = %ld, d = %ld -> %ld\n\n", time, currentRecord, result);
    return result;
}

void solvePartII()
{
    int solutionII = 1;

    long t = 42686985;
    long d = 284100511221341;

    // test input
    // long t = 71530;
    // long d = 940200;

    solutionII = numOfWaysToWin(t, d);
    printf("The solution to part II is: %d\n", solutionII);
}

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
    printf("Read input successfully!\n");
}
