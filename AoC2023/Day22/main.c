#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

//#define BRICKS 1258
#define BRICKS 7

#define XLEN 10
#define YLEN 10
#define ZLEN 300

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
    int numOfSupports;
};

struct Brick bricks[BRICKS];
int grid[XLEN][YLEN][ZLEN];
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
    fp = fopen("test.txt", "r");

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

int rayCastDown(int startx, int starty, int startz, int maxh) {
    int h = 0;
    int z = startz-1;

    while (z > 0 && !grid[startx][starty][z] && h < maxh) {
        z--;
        h++;
    }

    return h;
}

int fallHeight(struct Brick *b) {
    // TODO
    int h = INT_MAX;
    if (b->axis == Z) {
        h = rayCastDown(b->x1, b->y1, b->z1, ZLEN);
    } else if (b->axis == Y) {
        for (int y = b->y1; y <= b->y2; y++) {
            int currh = rayCastDown(b->x1, y, b->z1, h);
            h = currh < h ? currh : h;
        }
    } else {
        for (int x = b->x1; x <= b->x2; x++) {
            int currh = rayCastDown(x, b->y1, b->z1, h);
            h = currh < h ? currh : h;
        }
    }

    return h;
}

void letFall(struct Brick *b, int amount) {
    for (int x = b->x1; x <= b->x2; x++) {
        for (int y = b->y1; y <= b->y2; y++) {
            for (int z = b->z1; z <= b->z2; z++) {
                grid[x][y][z] = 0;
            }
        }
    }

    b->z1 -= amount;
    b->z2 -= amount;

    for (int x = b->x1; x <= b->x2; x++) {
        for (int y = b->y1; y <= b->y2; y++) {
            for (int z = b->z1; z <= b->z2; z++) {
                grid[x][y][z] = 1;
            }
        }
    }
}

// returns true if b2 is a support of b1
int isSupport(struct Brick *b1, struct Brick *b2) {
    return b2->z2 + 1 == b1->z1 && !(b1->x2 < b2->x1 || b2->x2 < b1->x1) && !(b1->y2 < b2->y1 || b2->y2 < b1->y1);
}

void numOfSupports(struct Brick *b1) {
    if (b1->z1 == 1) {
        b1->numOfSupports = INT_MAX;
        return;
    }

    int n = 0;
    for (int i = 0; i < BRICKS; i++) {
        struct Brick *b2 = &bricks[i];

        if (isSupport(b1, b2)) {
            n++;
        }
    }
    b1->numOfSupports = n;
}

int safeToDisintegrate(struct Brick *b1) {
    for (int i = 0; i < BRICKS; i++) {
        struct Brick *b2 = &bricks[i];
        if (isSupport(b2, b1) && b2->numOfSupports == 1) {
            return 0;
        }
    }
    return 1;
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

    // calculate numOfSupports for every brick
    for (int i = 0; i < BRICKS; i++) {
        numOfSupports(&bricks[i]);
        printBrick(&bricks[i]);
    }

    // find the bricks that are safe to disintegrate
    for (int i = 0; i < BRICKS; i++) {
        if (safeToDisintegrate(&bricks[i])) {
            printf("Brick #%d is safe to disintegrate!\n", i+1);
            solutionI++;
        }
    }

    printf("The solution to part I is: %d\n", solutionI);
}

void solvePartII()
{
    int solutionII = 0;
    printf("The solution to part II is: %d\n", solutionII);
}

void printBrick(struct Brick *b) {
    printf("%1d,%1d,%d~%1d,%1d,%d %d", b->x1, b->y1, b->z1, b->x2, b->y2, b->z2, b->numOfSupports);
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