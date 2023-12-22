#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BRICKS 1258
// #define BRICKS 7

enum Axis {
    X,
    Y,
    Z
};

struct Brick {
    int x1;
    int y1;
    int z1;
    int x2;
    int y2;
    int z2;
    enum Axis axis;
};

struct Brick bricks[BRICKS];
int grid[10][10][300];
static FILE *fp;

void openFile();
void readInput();
void solvePartI();
void solvePartII();
void printBrick(struct Brick *);

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
    for (int i = 0; i < BRICKS; i++) {
        fscanf(fp, "%1d,%1d,%d~%1d,%1d,%d\n", &bricks[i].x1, &bricks[i].y1, &bricks[i].z1, &bricks[i].x2, &bricks[i].y2, &bricks[i].z2);
        if (bricks[i].x1 != bricks[i].x2) {
            bricks[i].axis = X;
        } else if (bricks[i].y1 != bricks[i].y2) {
            bricks[i].axis = Y;
        } else if (bricks[i].z1 != bricks[i].z2) {
            bricks[i].axis = Z;
        }

        printBrick(&bricks[i]);
    }
    printf("Read input successfully!\n");
}

int fallHeight(struct Brick *b) {
    // TODO
    int h = 0;
    if (b->axis == Z) {
        for (int z = b->z1-1; z >= 1; z--) {
            if (grid[b->x1][b->y1][z]) {
                break;
            }
            h++;
        }
    } else if (b->axis == Y) {

    } else {

    }

    return h;
}

void letFall(struct Brick *b, int amount) {
    // TODO
    if (b->axis == Z) {

    } else if (b->axis == Y) {
        
    } else {

    }
}

void solvePartI()
{
    int solutionI = 0;

    int bricksAreFalling = 1;
    while (bricksAreFalling) {
        bricksAreFalling = 0;
        for (int i = 0; i < BRICKS; i++) {
            int h = fallHeight(&bricks[i]);
            if (h > 0) {
                bricksAreFalling = 1;
                letFall(&bricks[i], h);
            }
        }
    }

    // TODO
    // determine the number of blocks that can be disintegrated
    printf("The solution to part I is: %d\n", solutionI);
}

void solvePartII()
{
    int solutionII = 0;
    printf("The solution to part II is: %d\n", solutionII);
}

void printBrick(struct Brick *b) {
    printf("%1d,%1d,%d~%1d,%1d,%d", b->x1, b->y1, b->z1, b->x2, b->y2, b->z2);
    switch (b->axis)
    {
        case X:
            printf(" X\n");
            break;
        case Y:
            printf(" Y\n");
            break;
        case Z:
            printf(" Z\n");
            break;
    }
}