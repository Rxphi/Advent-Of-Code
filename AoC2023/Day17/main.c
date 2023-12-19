#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

//#define N 141
#define N 13

enum Direction {
    LEFT, 
    RIGHT, 
    UP, 
    DOWN, 
    NONE
};

int grid[N][N];
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
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(fp, "%1d", &grid[i][j]);
            printf("%1d", grid[i][j]);
        }
        fscanf(fp, "\n");
        printf("\n");
    }
    printf("\n");
    printf("Read input successfully!\n");
}

void dirConvert(enum Direction dir, int *arr) {
    switch (dir) {
        case LEFT:
            arr[0] = 0;
            arr[1] = -1;
            break;
        case RIGHT:
            arr[0] = 0;
            arr[1] = 1;
            break;
        case UP:
            arr[0] = -1;
            arr[1] = 0;
            break;
        case DOWN:
            arr[0] = 1;
            arr[1] = 0;
            break;
        default:
            arr[0] = arr[1] = 0;
            break;
    }
}

enum Direction invertDir(enum Direction dir) {
    switch (dir) {
        case LEFT:
            return RIGHT;
        case RIGHT:
            return LEFT;
        case UP:
            return DOWN;
        case DOWN:
            return UP;
        default:
            return NONE;
    }
}

int shortestPath(int starti, int startj, int startk) {
 
    enum Direction prev[N][N];
    int visited[N][N][16];
    int dist[N][N][16];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < 16; k++) {
                visited[i][j][k] = 0;
                dist[i][j][k] = INT_MAX; 
            }
        }
    }

    int i = starti;
    int j = startj;
    int k = startk;
    dist[i][j][k] = grid[i][j];

    while (1) {
        // get node with smallest distance that is not visited
        int smallest = INT_MAX;
        for (int u = 0; u < N; u++) {
            for (int v = 0; v < N; v++) {
                for (int w = 0; w < 16; w++) {
                    if (!visited[u][v][w] && dist[u][v][w] < smallest) {
                        i = u;
                        j = v;
                        k = w;
                        smallest = dist[u][v][w];
                    }
                }
            }
        }
        visited[i][j][k] = 1;
        if (i == N-1 && j == N-1) {
            break;
        }
        // update neighbors
        for (int dir = LEFT; dir <= DOWN; dir++) {
            if (dir == invertDir(k / 4) || (k % 4 == 3 && k / 4 == dir)) {
                continue;
            }
            int dirVals[] = {0, 0};
            dirConvert(dir, dirVals);
            int di = dirVals[0];
            int dj = dirVals[1];
            int newk = dir * 4; 
            newk += dir == k / 4 ? k % 4 + 1: 0;

            if (i + di < 0 || i + di >= N || j + dj < 0 || j + dj >= N) {
                continue;
            } else if (dist[i][j][k] + grid[i+di][j+dj] < dist[i+di][j+dj][newk]) {
                dist[i+di][j+dj][newk] = dist[i][j][k] + grid[i+di][j+dj];
                prev[i+di][j+dj] = invertDir(dir);
            }
        }
    }

    int ans = INT_MAX;
    for (int l = 0; l < 16; l++) {
        ans = dist[N-1][N-1][l] < ans ? dist[N-1][N-1][l] : ans;
    }
    return ans;
}

void solvePartI()
{
    int option1 = shortestPath(1, 0, 9); 
    int option2 = shortestPath(0, 1, 5);
    int solutionI = option1 < option2 ? option1 : option2;
    
    printf("The solution to part I is: %d\n", solutionI);
}

void solvePartII()
{
    int solutionII = 0;
    printf("The solution to part II is: %d\n", solutionII);
}
