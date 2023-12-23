#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define N 23
#define N 141

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
    int isStart;
    int isEnd;
    struct Node *node1;
    struct Node *node2;
};

int numOfNodes;
int startj;
int endj;
char grid[N][N];
static FILE *fp;

void openFile();
void readInput();
void solvePartI();
void printGrid();
void printNode(struct Node *);

int main()
{
    openFile();

    readInput();

    solvePartI();

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

            int outgoingSlopes = 0;

            if (j+1 < N && grid[i][j+1] == '>') {
                outgoingSlopes++;
            }

            if (j-1 >= 0 && grid[i][j-1] == '<') {
                outgoingSlopes++;
            }

            if (i+1 < N && grid[i+1][j] == 'v') {
                outgoingSlopes++;
            }

            if (i-1 >= 0 && grid[i-1][j] == '^') {
                outgoingSlopes++;
            }

            if (outgoingSlopes >= 2) {
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
        if (j != N-1 && prevj != j+1 && grid[i][j+1] != '<' && grid[i][j+1] != '#') {
            di = 0;
            dj = 1;
        } else if (i != N-1 && previ != i+1 && grid[i+1][j] != '^' && grid[i+1][j] != '#') {
            di = 1;
            dj = 0;
        } else if (j != 0 && prevj != j-1 && grid[i][j-1] != '>' && grid[i][j-1] != '#') {
            di = 0;
            dj = -1;
        } else if (i != 0 && previ != i-1 && grid[i-1][j] != 'v' && grid[i-1][j] != '#') {
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
    }

    // printf("Arrival at (%d, %d) and dist = %d\n", arrival->i, arrival->j, d);
}

int longestPath(struct Node *startNode) {
    if (startNode->isEnd) {
        return 0;
    } else if (startNode->isStart) {
        return startNode->dist1 + longestPath(startNode->node1);
    } else {
        int opt1 = startNode->dist1 + longestPath(startNode->node1);
        int opt2 = startNode->dist2 + longestPath(startNode->node2);
        return opt1 > opt2 ? opt1 : opt2;
    }
}

void solvePartI()
{
    int solutionI = 0;

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

        if (j+1 < N && grid[i][j+1] == '>') {
            walkToNextNode(&nodes[k], RIGHT, nodes);
        }

        if (j-1 >= 0 && grid[i][j-1] == '<') {
            walkToNextNode(&nodes[k], LEFT, nodes);
        }

        if (i+1 < N && grid[i+1][j] == 'v') {
            walkToNextNode(&nodes[k], DOWN, nodes);
        }

        if (i-1 >= 0 && grid[i-1][j] == '^') {
            walkToNextNode(&nodes[k], UP, nodes);
        }
    }

    /*
    printGrid();
    for (int i = 0; i < numOfNodes; i++) {
        printNode(&nodes[i]);
    }
    */

    solutionI = longestPath(&nodes[0]);

    printf("The solution to part I is: %d\n", solutionI);
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
        printf("START NODE at (%d, %d) and dist = %d\n", node->i, node->j, node->dist1);
        return;
    } else if (node->isEnd) {
        printf("END NODE at (%d, %d)\n", node->i, node->j);
        return;
    } else {
        printf("NODE at (%d, %d) and neigh1 at (%d, %d) dist1 = %d and neigh2 at (%d, %d) dist2 = %d\n", node->i, node->j, node->node1->i, node->node1->j, node->dist1, node->node2->i, node->node2->j, node->dist2);                                     
    }
}