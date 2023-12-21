#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define N 11
#define N 131

struct Position {
    int i;
    int j;
    struct Position *next;
};

struct PositionLL {
    int size;
    struct Position *head;
    struct Position *tail;
};

int grid[N][N];
int starti;
int startj;
static FILE *fp;

void openFile();
void readInput();
void solvePartI();
void solvePartII();
struct Position *createNewPosition(int, int);
void insertPosition(struct PositionLL *, struct Position *);
struct Position *popPosition(struct PositionLL *);
void printGridAndVisited(int *, int, int);

struct Position *createNewPosition(int i, int j) {
    struct Position *p = calloc(sizeof(struct Position), 1);
    p->i = i;
    p->j = j;
    return p;
}

void insertPosition(struct PositionLL *ll, struct Position *p) {
    if (ll->size == 0) {
        ll->head = ll->tail = p;
    } else {
        ll->tail->next = p;
        ll->tail = p;
    }
    ll->size++;
}

struct Position *popPosition(struct PositionLL *ll) {
    if (ll->size == 0) {
        printf("Can't pop from empty queue");
        exit(1);
    }

    struct Position *p = ll->head;

    if (ll->size == 1) {
        ll->head = ll->tail = NULL;
    } else {
        ll->head = p->next;
    }

    ll->size--;
    return p;
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
    char c;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(fp, "%1c", &c);
            grid[i][j] = '#' == c ? 1 : 0;

            if ('S' == c) {
                starti = i;
                startj = j;
            }

            // printf("%1c", c);
        }
        fscanf(fp, "\n");
        // printf("\n");
    }
    // printf("\n");
    printf("Read input successfully!\n");
}

void reset2dArray(int *arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            *(arr+i*cols+j) = 0;
        }
    }
}

void solvePartI()
{
    int solutionI = 0;

    struct PositionLL ll = {0};
    insertPosition(&ll, createNewPosition(starti, startj));

    int visited[N][N];

    for (int step = 0; step < 64; step++) {
        reset2dArray(&visited[0][0], N, N);
        int nodesToProcess = ll.size;

        for (int k = 0; k < nodesToProcess; k++) {
            struct Position *p = popPosition(&ll);
            int i = p->i;
            int j = p->j;

            for (int di = -1; di <= 1; di += 2) {
                if (i + di < 0|| i + di >= N || visited[i+di][j] || grid[i+di][j]) {
                    continue;
                }
                visited[i+di][j] = 1;
                insertPosition(&ll, createNewPosition(i+di, j));
            }

            for (int dj = -1; dj <= 1; dj += 2) {
                if (j + dj < 0|| j + dj >= N || visited[i][j+dj] || grid[i][j+dj]) {
                    continue;
                }
                visited[i][j+dj] = 1;
                insertPosition(&ll, createNewPosition(i, j+dj));
            }
            free(p);
        }

        // printGridAndVisited(&visited[0][0], N, N);
    }

    solutionI = ll.size;

    printf("The solution to part I is: %d\n", solutionI);
}

void solvePartII()
{
    long solutionII = 0;
    long steps = 26501365;
    struct PositionLL ll = {0};
    insertPosition(&ll, createNewPosition(starti, startj));

    int visited[N][N];

    long fullGrid;
    long insideGrid;

    // Zum Glück gilt steps % N == N-1 / 2
    for (int step = 0; step < N; step++) {
        reset2dArray(&visited[0][0], N, N);
        int nodesToProcess = ll.size;
        

        for (int k = 0; k < nodesToProcess; k++) {
            struct Position *p = popPosition(&ll);
            int i = p->i;
            int j = p->j;

            for (int di = -1; di <= 1; di += 2) {
                if (i + di < 0|| i + di >= N || visited[i+di][j] || grid[i+di][j]) {
                    continue;
                }
                visited[i+di][j] = 1;
                insertPosition(&ll, createNewPosition(i+di, j));
            }

            for (int dj = -1; dj <= 1; dj += 2) {
                if (j + dj < 0|| j + dj >= N || visited[i][j+dj] || grid[i][j+dj]) {
                    continue;
                }
                visited[i][j+dj] = 1;
                insertPosition(&ll, createNewPosition(i, j+dj));
            }
            free(p);
        }

        if (step == 64) {
            insideGrid = ll.size;
        }
    }

    // printGridAndVisited(&visited[0][0], N, N);
    fullGrid = ll.size;

    solutionII = (steps / N + 1) * (steps / N + 1) * fullGrid - (fullGrid - insideGrid); 

    printf("steps/N = %ld, steps \% N = %ld, fullGrid = %ld, insideGrid = %ld\n", steps / N, steps % N, fullGrid, insideGrid);
    printf("The solution to part II is: %ld\n", solutionII);
}

void printGridAndVisited(int *visited, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (*(visited+i*cols+j)) {
                printf("O");
            } else if (grid[i][j]) {
                printf("#");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
    printf("\n");
}