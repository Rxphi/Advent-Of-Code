#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// #define N 141
#define N 13

#define MAX_NUM_OF_NODES 300

enum Direction {
    LEFT, 
    RIGHT, 
    UP, 
    DOWN, 
    NONE
};

struct Node {
    int i;
    int j;
    int k;
    int dist;
};

struct minheap {
    int size;
    struct Node * nodes[MAX_NUM_OF_NODES];
};


int grid[N][N];
static FILE *fp;

void openFile();
void readInput();
void solvePartI();
void solvePartII();
void minHeapInsert(struct minheap *, struct Node *);
void minHeapBubbleUp(struct minheap *, int);
struct Node * minHeapPop(struct minheap *);
void minHeapTrickleDown(struct minheap *, int);

void minHeapInsert(struct minheap *h, struct Node *n) {
    h->nodes[h->size] = n;
    h->size++;
    minHeapBubbleUp(h, h->size-1);
}

void minHeapBubbleUp(struct minheap *h, int i) {
    if (i == 0) {
        return;
    }
    int parent = (i-1) / 2;

    if (h->nodes[parent]->dist > h->nodes[i]->dist) {
        struct Node *remember = h->nodes[parent];
        h->nodes[parent] = h->nodes[i];
        h->nodes[i] = remember;
        minHeapBubbleUp(h, parent);
    }
}

void minHeapTrickleDown(struct minheap *h, int i) {
    int left = i*2+1;
    int right = i*2+2;

    struct Node *remember = h->nodes[i];

    if (right < h->size) {
        int smaller = h->nodes[right]->dist < h->nodes[left]->dist ? right : left;

        if (h->nodes[i]->dist > h->nodes[smaller]->dist) {
            h->nodes[i] = h->nodes[smaller];
            h->nodes[smaller] = remember;
            minHeapTrickleDown(h, right);
        }
    } else if (left < h->size && h->nodes[left]->dist < remember->dist) {
        h->nodes[i] = h->nodes[left];
        h->nodes[left] = remember;
        minHeapTrickleDown(h, left);
    }
}

struct Node *minHeapPop(struct minheap *h) {
    if (h->size == 0) {
        printf("Can't pop from empty heap!!!\n");
    }
    struct Node * minNode = h->nodes[0];

    h->nodes[0] = h->nodes[h->size-1];
    h->nodes[h->size-1] = NULL;
    h->size--;
    minHeapTrickleDown(h, 0);

    return minNode;
}

int main() {
    openFile();

    readInput();

    solvePartI();
    solvePartII();

    fclose(fp);
    return 0;
}

void openFile() {
    fp = fopen("test.txt", "r");

    if (fp == NULL)
    {
        perror("The file could not be opened!\n");
        exit(1);
    }
    else {
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

struct Node *createNode(int i, int j, int k, int dist) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->i = i;
    newNode->j = j;
    newNode->k = k;
    newNode->dist = dist;
    return newNode;
}

int shortestPath(int starti, int startj, int startk) {
 
    struct minheap h = {0};
    int visited[N][N][12];
    int dist[N][N][12];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < 12; k++) {
                visited[i][j][k] = 0;
                dist[i][j][k] = INT_MAX;
            }
        }
    }

    visited[starti][startj][startk] = 1;
    minHeapInsert(&h, createNode(starti, startj, startk, grid[starti][startj]));

    while (h.size > 0) {
        printMinheap(&h);
        // get node with smallest distance that is not visited
        struct Node *smallestNode = minHeapPop(&h);
        int i = smallestNode->i;
        int j = smallestNode->j;
        int k = smallestNode->k;
        int d = smallestNode->dist;

        visited[i][j][k] = 1;
        if (i == N-1 && j == N-1) {
            break;
        }
        // update neighbors
        for (int dir = LEFT; dir <= DOWN; dir++) {
            if (dir == invertDir(k / 3) || (k % 3 == 2 && k / 3 == dir)) {
                continue;
            }
            int dirVals[] = {0, 0};
            dirConvert(dir, dirVals);
            int di = dirVals[0];
            int dj = dirVals[1];
            int newk = dir * 3; 
            newk += dir == k / 3 ? k % 3 + 1 : 0;

            if (i + di < 0 || i + di >= N || j + dj < 0 || j + dj >= N) {
                continue;
            } else if (d + grid[i+di][j+dj] < dist[i+di][j+dj][newk]) {
                int newd = d + grid[i+di][j+dj];
                dist[i+di][j+dj][newk] = newd;
                minHeapInsert(&h, createNode(i+di, j+dj, newk, newd));
            }
        }
    }

    int ans = INT_MAX;
    for (int l = 0; l < 12; l++) {
        ans = dist[N-1][N-1][l] < ans ? dist[N-1][N-1][l] : ans;
    }

    return ans;
}

void solvePartI()
{
    printf("Calculating PartI... this takes some time :-)\n");
    int option1 = shortestPath(1, 0, 9); 
    int option2 = shortestPath(0, 1, 3);
    int solutionI = option1 < option2 ? option1 : option2;
    
    printf("The solution to part I is: %d\n", solutionI);
}

void solvePartII()
{
    int solutionII = 0;
    printf("The solution to part II is: %d\n", solutionII);
}

printMinheap(struct minheap *h) {
    printf("Size = %d; ", h->size);
    for (int i = 0; i < h->size; i++) {
        printf("(%d, %d, %d, %d) ", h->nodes[i]->i, h->nodes[i]->j, h->nodes[i]->k, h->nodes[i]->dist);
    }
    printf("\n");
}