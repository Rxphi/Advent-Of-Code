#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static FILE *fp;

void openFile();
void readInput();
void solvePartI();
void solvePartII();

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

void solvePartI()
{
    int solutionI = 0;
    printf("The solution to part I is: %d\n", solutionI);
}

void solvePartII()
{
    int solutionII = 0;
    printf("The solution to part II is: %d\n", solutionII);
}