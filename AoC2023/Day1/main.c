#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static FILE *fp;

void openFile();
void solvePartI();
void solvePartII();
int digitI(char *);
int digitII(char *);

int main() {
    openFile();

    solvePartI();
    solvePartII();

    fclose(fp);
    return 0;
}

void openFile() {
    fp = fopen("input.txt", "r");

    if (fp == NULL) {
        exit(1);
    }
}

void solvePartI() {
    int solutionI = 0;
    char line[100];

    while (fscanf(fp, "%s\n", line) == 1) {
        int len = strlen(line);
        int num = 0;

        for (int i = 0; i < len; i++) {
            int d = digitI(&line[i]);
            if (d != -1) {
                num += 10 * d;
                break;
            } 
        }

        for (int i = len-1; i >= 0; i--) {
            int d = digitI(&line[i]);
            if (d != -1) {
                num += d;
                break;
            } 
        }
        solutionI += num;
    }
    printf("The solution to part I is: %d\n", solutionI);
}

void solvePartII() {
    openFile();
    int solutionII = 0;

    char line[100];

    while (fscanf(fp, "%s\n", line) == 1) {
        int len = strlen(line);
        int num = 0;

        for (int i = 0; i < len; i++) {
            int d = digitII(&line[i]);
            if (d != -1) {
                num += 10 * d;
                break;
            } 
        }

        for (int i = len-1; i >= 0; i--) {
            int d = digitII(&line[i]);
            if (d != -1) {
                num += d;
                break;
            }
        }
        solutionII += num;
    }

    printf("The solution to part II is: %d\n", solutionII);
}

char* digits[10] = {"zero" ,"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int digitI(char * p) {
    if ('0' <= (*p) && (*p) <= '9') {
        return (*p) - '0';
    } else {
        return -1;
    }
}

int digitII(char * p) {
    int d = digitI(p);
    if (d != -1) {
        return d;
    }
    for (int i = 0; i < 10; i++) {
        if (strncmp(digits[i], p, strlen(digits[i])) == 0) {
            return i;
        }
    }
    return -1;
}