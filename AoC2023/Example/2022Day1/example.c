#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static FILE *fp;

void readInput();
void solvePartI();
void solvePartII();

struct Elf
{
    int calories;
    struct Elf *next;
};

struct Elf *createElf()
{
    struct Elf *newElf = (struct Elf *)malloc(sizeof(struct Elf));
    newElf->calories = 0;
    newElf->next = NULL;
    return newElf;
}

static struct Elf *firstElf;

int main()
{
    fp = fopen("example.txt", "r");

    if (fp == NULL)
    {
        perror("The file could not be opened!\n");
        exit(1);
    }
    else
    {
        printf("Opened input file successfully!\n");
    }

    readInput();

    solvePartI();
    solvePartII();

    fclose(fp);
    return 0;
}

void readInput()
{
    firstElf = createElf();
    struct Elf *currentElf = firstElf;

    char currentLine[10];
    while (fgets(currentLine, sizeof(currentLine), fp) != NULL)
    {
        if ((*currentLine) != '\n')
        {
            currentElf->calories += atoi(currentLine);
        }
        else
        {
            currentElf->next = createElf();
            currentElf = currentElf->next;
        }
    }
    printf("Read input successfully!\n");
}

void solvePartI()
{
    int solutionI = 0;
    for (struct Elf *currentElf = firstElf; currentElf != NULL; currentElf = currentElf->next)
    {
        solutionI = currentElf->calories > solutionI ? currentElf->calories : solutionI;
    }
    printf("The solution to part I is: %d\n", solutionI);
}

void solvePartII()
{
    int first, second, third;
    first = second = third = 0;

    for (struct Elf *currentElf = firstElf; currentElf != NULL; currentElf = currentElf->next)
    {
        int cal = currentElf->calories;

        if (cal > first)
        {
            third = second;
            second = first;
            first = cal;
        }
        else if (cal > second)
        {
            third = second;
            second = cal;
        }
        else if (cal > third)
        {
            third = cal;
        }
    }
    printf("The solution to part II is: %d\n", first + second + third);
}
