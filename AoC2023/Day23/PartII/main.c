#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 23
// #define N 141

enum Direction {
    RIGHT,
    DOWN,
    LEFT,
    UP
};

struct Node {
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
    fp = fopen("../test.txt", "r");

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
            fscanf(fp, "%1c", &grid[i][j]);
        }
        fscanf(fp, "\n");
    }

    // detect nodes (including start and end node)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == 0 && grid[i][j] == '.') {
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

            int slopes = 0;

            if (j+1 < N && (grid[i][j+1] == '>' || grid[i][j+1] == '<')) {
                slopes++;
            }

            if (j-1 >= 0 && (grid[i][j-1] == '>' || grid[i][j-1] == '<')) {
                slopes++;
            }

            if (i+1 < N && (grid[i+1][j] == 'v' || grid[i+1][j] == '^')) {
                slopes++;
            }

            if (i-1 >= 0 && (grid[i][j-1] == 'v' || grid[i-1][j] == '^')) {
                slopes++;
            }

            if (slopes >= 2) {
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

        // Case: Slope at (i, j)
        if (grid[i][j] == '>') {
            di = 0;
            dj = 1;
            continue;
        } else if (grid[i][j] == 'v') {
            di = 1;
            dj = 0;
            continue;
        } else if (grid[i][j] == '<') {
            di = 0;
            dj = -1;
            continue;
        } else if (grid[i][j] == '^') {
            di = -1;
            dj = 0;
            continue;
        }

        // Case: No slope at (i, j)
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

    } while (grid[i][j] != 'N' && grid[i][j] != 'E');

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

void solvePartII()
{
    int solutionII = 0;

    struct Node nodes[numOfNodes];
    memset(nodes, 0, sizeof(struct Node) * numOfNodes);

    // start node
    nodes[0].isStart = 1;
    nodes[0].i = 0;
    nodes[0].j = startj;

    // end node
    nodes[numOfNodes-1].isEnd = 1;
    nodes[numOfNodes-1].i = N-1;
    nodes[numOfNodes-1].j = endj;

    int nodeInd = 1;

    for (int i = 1; i < N-1; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 'N') {
                nodes[nodeInd].i = i;
                nodes[nodeInd].j = j;
                nodeInd++;
            }
        }
    }

    // calculate distance between the nodes
    walkToNextNode(&nodes[0], DOWN, nodes);

    for (int k = 1; k < numOfNodes-1; k++) {
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

    printGrid();

    for (int i = 0; i < numOfNodes; i++) {
        printNode(&nodes[i]);
    }
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
    if (node->isStart) {
        printf("START NODE at (%d, %d) and neigh1 (%d, %d) dist1 %d\n", node->i, node->j, node->node1->i, node->node1->j, node->dist1);
        return;
    } else if (node->isEnd) {
        printf("END NODE at (%d, %d)\n", node->i, node->j);
        return;
    } 
    printf("NODE at (%d, %d)", node->i, node->j);                                     
    if (node->node1 != NULL) {
        printf(" and neigh1 (%d, %d) dist1 %d", node->node1->i, node->node1->j, node->dist1);
    }
    if (node->node2 != NULL) {
        printf(" and neigh2 (%d, %d) dist2 %d", node->node2->i, node->node2->j, node->dist2);
    }
    if (node->node3 != NULL) {
        printf(" and neigh3 (%d, %d) dist3 %d", node->node3->i, node->node3->j, node->dist3);
    }
    if (node->node4 != NULL) {
        printf(" and neigh4 (%d, %d) dist4 %d", node->node4->i, node->node4->j, node->dist4);
    }
    
    printf("\n");
}