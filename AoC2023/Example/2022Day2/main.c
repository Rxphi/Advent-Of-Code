#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static FILE *fp;

void openFile();
void readInput();
void solvePartI();
void solvePartII();
int points(char, char);

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
    
}

void solvePartI()
{
    int solutionI = 0;

    char opponentShape, myShape;

    while (fscanf(fp, "%c %c\n", &opponentShape, &myShape) == 2) {
        int p = points(opponentShape, myShape);
        solutionI += p;
    }

    printf("The solution to part I is: %d\n", solutionI);
}

void solvePartII()
{
    openFile();
    int solutionII = 0;
    
    char opponentShape, outcome;

    while (fscanf(fp, "%c %c\n", &opponentShape, &outcome) == 2) {
        char myShape;

        switch (outcome)
        {
        case 'X':
            switch (opponentShape)
            {
            case 'A':
                myShape = 'Z';
                break;
            case 'B':
                myShape = 'X';
                break;
            case 'C':
                myShape = 'Y';
                break;
            }
            break;
        
        case 'Y':
            myShape = opponentShape - 'A' + 'X';
            break;
        
        case 'Z':
            switch (opponentShape)
            {
            case 'A':
                myShape = 'Y';
                break;
            case 'B':
                myShape = 'Z';
                break;
            case 'C':
                myShape = 'X';
                break;
            }
            break;
        }

        int p = points(opponentShape, myShape);
        solutionII += p;
    }

    printf("The solution to part II is: %d\n", solutionII);
}

int points(char opponentShape, char myShape) {
    int score = myShape - 'X' + 1;

    switch (opponentShape)
    {
    case 'A':
        switch (myShape)
        {
        case 'X':
            score += 3;
            break;

        case 'Y':
            score += 6;
            break;
        }   
        break;
    case 'B':
        switch (myShape)
        {
        case 'Y':
            score += 3;
            break;
        case 'Z':
            score += 6;
            break;
        }
        break;
    case 'C':
        switch (myShape)
        {
        case 'X':
            score += 6;
            break;
        case 'Z':
            score += 3;
            break;
        }   
        break;
    }
    return score;
}