#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static FILE *fp;

void openFile();
void readInput();
void solvePartI();
void solvePartII();

struct Draw {
    int red, green, blue;
    struct Draw *next;
};

struct Game {
    int id;
    struct Draw *firstDraw;
};

struct Draw *createDraw(int, int, int);

struct Game games [100];
int numOfGames = 0;

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
    int maxLine = 300;
    char line[maxLine];
    int id;

    while (fscanf(fp, "Game %d: ", &id) == 1) {
        fgets(line , maxLine, fp);

        struct Game game = {id, NULL};

        struct Draw *currentDraw = NULL;

        int r, g, b;
        r = g = b = 0;

        int len = strlen(line);
        int num = 0;
        int i = 0;
        while (i < len-1) {
            if (isdigit(line[i])) {
                if (line[i+1] == ' ') {
                    num = (line[i] - 0x30);
                    i += 2;
                } else {
                    num = 10 * (line[i] - 0x30) + (line[i+1] - 0x30);
                    i += 3;
                }
            } else {
                char color = line[i];
                char del;
                int newDraw = 0;
                switch (color)
                {
                case 'r':
                    r = num;
                    del = line[i+3];
                    newDraw = (del == ';') || (del == '\n') || (del == '\0')? 1 : 0;
                    i += 5;
                    break;
                case 'g':
                    g = num;
                    del = line[i+5];
                    newDraw = (del == ';') || (del == '\n') || (del == '\0')? 1 : 0;
                    i += 7;
                    break;
                case 'b':
                    b = num;
                    del = line[i+4];
                    newDraw = (del == ';') || (del == '\n') || (del == '\0')? 1 : 0;
                    i += 6;
                    break;
                }

                if (newDraw) {
                    struct Draw *pDraw = createDraw(r, g, b);
                    if (game.firstDraw == NULL) {
                        game.firstDraw = pDraw;
                        currentDraw = game.firstDraw;
                    } else {
                        currentDraw->next = pDraw;
                        currentDraw = pDraw;
                    }
                    r = g = b = 0;
                }
            }
        }

        games[numOfGames++] = game;
    }

    printf("Read input successfully!\n");
}

int isDelimiter(char del) {
    return (del == ';') || (del == '\n') || (del == '\0');
}

struct Draw *createDraw(int r, int g, int b) {
    struct Draw *pDraw = (struct Draw *) malloc(sizeof(struct Draw));
    pDraw->red = r;
    pDraw->green = g;
    pDraw->blue = b;
    pDraw->next = NULL;
    return pDraw;
}

void solvePartI()
{
    int solutionI = 0;

    for (int i = 1; i <= numOfGames; i++) {
        struct Game currGame = games[i-1];

        int validGame = 1;

        for (struct Draw *currDraw = currGame.firstDraw; currDraw != NULL; currDraw = currDraw->next) {
            int r = currDraw->red;
            int g = currDraw->green;
            int b = currDraw->blue;

            if (r > 12 || g > 13 || b > 14) {
                validGame = 0;
                break;
            }
        }

        if (validGame) {
            solutionI += currGame.id;
        }
    }
    
    printf("The solution to part I is: %d\n", solutionI);
}

void solvePartII()
{
    int solutionII = 0;

    for (int i = 1; i <= numOfGames; i++) {
        struct Game currGame = games[i-1];

        int maxr, maxg, maxb;
        maxr = maxg = maxb = 0;

        for (struct Draw *currDraw = currGame.firstDraw; currDraw != NULL; currDraw = currDraw->next) {
            maxr = currDraw->red > maxr ? currDraw->red : maxr;
            maxg = currDraw->green > maxg ? currDraw->green : maxg;
            maxb = currDraw->blue > maxb ? currDraw->blue: maxb;
        }
 
        solutionII += maxr * maxb * maxg;
    }
    printf("The solution to part II is: %d\n", solutionII);
}