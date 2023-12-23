#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define N 23
#define N 141

#define MAX(a, b) (a > b ? a : b)

enum Direction {
    RIGHT,
    DOWN,
    LEFT,
    UP
};

struct Node {
    int ind;
    int i;
    int j;
    int dist1;
    int dist2;
    int dist3;
    int dist4;
    int isStart;
    int isEnd;
    struct Node *node1;
    struct Node *node2;
    struct Node *node3;
    struct Node *node4;
};

int numOfNodes;
int startj;
int endj;
char grid[N][N];
static FILE *fp;

void openFile();
void readInput();
void solvePartII();
void printGrid();
void printNode(struct Node *);

int main()
{
    openFile();

    readInput();

    solvePartII();

    fclose(fp);
    return 0;
}

void openFile()
{
    fp = fopen("../input.txt", "r");

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

void readInput() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(fp, "%1c", &grid[i][j]);
        }
        fscanf(fp, "\n");
    }

    // detect nodes (including start and end node)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == '#') {
                continue;
            } else if (i == 0 && grid[i][j] == '.') {
                grid[i][j] = 'S';
                numOfNodes++;
                startj = j;
                break;
            } else if (i == N-1 && grid[i][j] == '.') {
                grid[i][j] = 'E';
                numOfNodes++;
                endj = j;
                break;
            }

            int freeNeigh = 0;

            if (j+1 < N && grid[i][j+1] != '#') {
                freeNeigh++;
            }

            if (j-1 >= 0 && grid[i][j-1] != '#') {
                freeNeigh++;
            }

            if (i+1 < N && grid[i+1][j] != '#') {
                freeNeigh++;
            }

            if (i-1 >= 0 && grid[i-1][j] != '#') {
                freeNeigh++;
            }

            if (freeNeigh > 2) {
                grid[i][j] = 'N';
                numOfNodes++;
            }
        }
    }

    printf("Read input successfully!\n");
}

void walkToNextNode(struct Node *start, enum Direction startDir, struct Node *nodes) {
    int d = 0;
    int i = start->i;
    int j = start->j;
    int di;
    int dj;
    int previ;
    int prevj;

    // printf("Start at (%d, %d) ", i, j);

    switch (startDir)
    {
        case RIGHT:
            di = 0;
            dj = 1;
            break;
        case DOWN:
            di = 1;
            dj = 0;
            break;
        case LEFT:
            di = 0;
            dj = -1;
            break;
        case UP:
            di = -1;
            dj = 0;
            break;
    }

    do {
        previ = i;
        prevj = j;
        i += di;
        j += dj;
        d++;

        // No slope at any (i, j)
        if (j != N-1 && prevj != j+1 && grid[i][j+1] != '#') {
            di = 0;
            dj = 1;
        } else if (i != N-1 && previ != i+1 && grid[i+1][j] != '#') {
            di = 1;
            dj = 0;
        } else if (j != 0 && prevj != j-1 && grid[i][j-1] != '#') {
            di = 0;
            dj = -1;
        } else if (i != 0 && previ != i-1 && grid[i-1][j] != '#') {
            di = -1;
            dj = 0;
        }

    } while (grid[i][j] != 'N' && grid[i][j] != 'E' && grid[i][j] != 'S');

    struct Node *arrival;
    for (int k = 0; k < numOfNodes; k++) {
        struct Node *curr = &nodes[k];
        if (curr->i == i && curr->j == j) {
            arrival = curr;
            break;
        }
    }

    if (start->node1 == NULL) {
        start->node1 = arrival;
        start->dist1 = d;
    } else if (start->node2 == NULL) {
        start->node2 = arrival;
        start->dist2 = d;
    } else if (start->node3 == NULL) {
        start->node3 = arrival;
        start->dist3 = d;
    } else if (start->node4 == NULL) {
        start->node4 = arrival;
        start->dist4 = d;
    }

    // printf("Arrival at (%d, %d) and dist = %d\n", arrival->i, arrival->j, d);
}

int longestPath(struct Node *startNode, int *visited) {
    // printf("(%d, %d)\n", startNode->i, startNode->j);
    if (startNode->isEnd) {
        return 0;
    } else if (startNode->isStart) {
        visited[startNode->ind] = 1;
        int d = startNode->dist1 + longestPath(startNode->node1, visited);
        visited[startNode->ind] = 0;
        return d;
    }

    visited[startNode->ind] = 1;

    int d, opt1, opt2, opt3, opt4;
    opt1 = opt2 = opt3 = opt4 = 0;

    if (startNode->node1 != NULL && !visited[startNode->node1->ind]) {
        opt1 = startNode->dist1 + longestPath(startNode->node1, visited);
    }

    if (startNode->node2 != NULL && !visited[startNode->node2->ind]) {
        opt2 = startNode->dist2 + longestPath(startNode->node2, visited);
    }

    if (startNode->node3 != NULL && !visited[startNode->node3->ind]) {
        opt3 = startNode->dist3 + longestPath(startNode->node3, visited);
    }

    if (startNode->node4 != NULL && !visited[startNode->node4->ind]) {
        opt4 = startNode->dist4 + longestPath(startNode->node4, visited);
    }

    d = MAX(MAX(opt1, opt2), MAX(opt3, opt4));

    visited[startNode->ind] = 0;
    return d;
}

void solvePartII()
{
    int solutionII = 0;

    struct Node nodes[numOfNodes];
    memset(nodes, 0, sizeof(struct Node) * numOfNodes);

    // start node
    nodes[0].ind = 0;
    nodes[0].isStart = 1;
    nodes[0].i = 0;
    nodes[0].j = startj;

    // end node
    nodes[numOfNodes-1].ind = numOfNodes-1;
    nodes[numOfNodes-1].isEnd = 1;
    nodes[numOfNodes-1].i = N-1;
    nodes[numOfNodes-1].j = endj;

    int nodeInd = 1;

    for (int i = 1; i < N-1; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 'N') {
                nodes[nodeInd].i = i;
                nodes[nodeInd].j = j;
                nodes[nodeInd].ind = nodeInd;
                nodeInd++;
            }
        }
    }

    for (int k = 0; k < numOfNodes; k++) {
        int i = nodes[k].i;
        int j = nodes[k].j;

        if (j+1 < N && grid[i][j+1] != '#') {
            walkToNextNode(&nodes[k], RIGHT, nodes);
        }

        if (j-1 >= 0 && grid[i][j-1] != '#') {
            walkToNextNode(&nodes[k], LEFT, nodes);
        }

        if (i+1 < N && grid[i+1][j] != '#') {
            walkToNextNode(&nodes[k], DOWN, nodes);
        }

        if (i-1 >= 0 && grid[i-1][j] != '#') {
            walkToNextNode(&nodes[k], UP, nodes);
        }
    }


    int visited[numOfNodes];
    memset(visited, 0, sizeof(int) * numOfNodes);

    solutionII = longestPath(&nodes[0], visited);

    printGrid();
    for (int i = 0; i < numOfNodes; i++) {
        printNode(&nodes[i]);
    }
    printf("Number of nodes: %d\n", numOfNodes);

    printf("The solution to part II is: %d\n", solutionII);
}

void printGrid() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%1c", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printNode(struct Node *node) {
    printf("(%d, %d) %d %d %d %d\n", node->i, node->j, node->dist1, node->dist2, node->dist3, node->dist4);
}