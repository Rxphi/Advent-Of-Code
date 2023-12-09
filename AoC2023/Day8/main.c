#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N 750
#define M 271

// #define N 8
// #define M 2

static FILE *fp;


struct Node {
    char name[4];
    short key;
    short left;
    short right;
    short isStart;
    short isEnd;
};

char directions[M];
struct Node *nodes[26*26*26];
struct Node *startNode = NULL;

int numOfStartNodes = 0;


void openFile();
void readInput();
struct Node * newNode(char *, char *, char *);
void printNode(struct Node *);
void solvePartI();
void solvePartII();
void analyzeNode(struct Node *);

int main() {
    openFile();

    readInput();

    solvePartI();
    solvePartII();

    fclose(fp);
    return 0;
}

void openFile() {
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

void readInput() {

    for (int i = 0; i < 26*26*26; i++) {
        nodes[i] = NULL;
    }

    fscanf(fp, "%s\n\n", directions);

    char keyString[4];
    char leftString[4];
    char rightString[4];

    for (int i = 0; i < N; i++) {
        fscanf(fp, "%3s = (%3s, %3s)", keyString, leftString, rightString);
        
        struct Node *newNodeP = newNode(keyString, leftString, rightString);
        nodes[newNodeP->key] = newNodeP;

        if (startNode == NULL && keyString[0] == 'A' && keyString[1] == 'A' && keyString[2] == 'A') {
            startNode = newNodeP;
        }
    }

    // printf("Directions: %s\n", directions);
    // for (int i = 0; i < 26*26*26; i++) {
    //     if (nodes[i] != NULL) {
    //         printNode(nodes[i]);
    //     }
    // }

    printf("Read input successfully!\n");
}

struct Node * newNode(char * keyString, char * leftString, char * rightString) {
    struct Node *nodeP = (struct Node *) calloc(sizeof(struct Node), 1);

    memcpy(nodeP->name, keyString, 4);
    nodeP->key = 26*26*(keyString[0] - 'A') + 26*(keyString[1] - 'A') + (keyString[2] - 'A');
    nodeP->left = 26*26*(leftString[0] - 'A') + 26*(leftString[1] - 'A') + (leftString[2] - 'A');
    nodeP->right = 26*26*(rightString[0] - 'A') + 26*(rightString[1] - 'A') + (rightString[2] - 'A');

    if (keyString[2] == 'A') {
        nodeP->isStart = 1;
        nodeP->isEnd = 0;
        numOfStartNodes++;
        // printNode(nodeP);
    } else if (keyString[2] == 'Z') {
        nodeP->isStart = 0;
        nodeP->isEnd = 1;
        // printNode(nodeP);
    } else {
        nodeP->isStart = 0;
        nodeP->isEnd = 0;
    }

    return nodeP;
}

void printNode(struct Node * nodeP) {
    printf("%s -> (%s, %s)", nodeP->name, nodes[nodeP->left]->name, nodes[nodeP->right]->name);
    if (nodeP->isStart) {
        printf(" - start node\n");
    } else if (nodeP->isEnd) {
        printf(" - end node\n");
    } else {
        printf("\n");
    }
}

struct Node * nextNode (struct Node * node, char dir) {
    if (dir == 'L') {
        return nodes[node->left];
    } else {
        return nodes[node->right];
    }
}

void solvePartI() {
    printf("\n=========PartI=========\n");
    int solutionI = 0;

    int directionInd = 0;
    struct Node * currNode = startNode;

    printNode(currNode);

    // while not found node 'ZZZ'
    while(currNode->key != 17575) {
        solutionI++;

        currNode = nextNode(currNode, directions[directionInd]);
        // printNode(currNode);

        directionInd = (directionInd + 1) % M;
    }

    printf("Solution: %d\n", solutionI);
}

void solvePartII() {
    printf("\n=========PartII=========\n");
    long solutionII = 0;

    struct Node *startNodes[numOfStartNodes];
    printf("NumOfStartNodes: %d\n", numOfStartNodes);

    // get start nodes
    for (int i = 0, j = 0; i < 26*26*26; i++) {
        if (nodes[i] != NULL && nodes[i]->isStart) {
            startNodes[j++] = nodes[i];
            // printf("Start Node: ");
            // printNode(startNodes[j-1]);
            if (j == numOfStartNodes) {
                break;
            }
        }
    }

    for (int i = 0; i < numOfStartNodes; i++) {
        analyzeNode(startNodes[i]);
    }

    printf("\nI used the information above to form a system of 6 equations in modular arithmetic, then I solved it by using the Chinese Remainder Theorem :)\n");
}

void analyzeNode(struct Node * node) {
    printf("\nAnalyzing node: ");
    printNode(node);

    long slowInd = 1 % M;
    long fastInd = 2 % M;
    struct Node *slow = nextNode(node, directions[0]);
    struct Node *fast = nextNode(slow, directions[1]);

    while (slow != fast || slowInd != fastInd) {
        // printNode(slow);
        // printNode(fast);
        // printf("slowInd = %d, fastInd = %d\n", slowInd, fastInd);

        slow = nextNode(slow, directions[slowInd]);
        slowInd = (slowInd + 1) % M;
        fast = nextNode(fast, directions[fastInd]);
        fastInd = (fastInd + 1) % M;
        fast = nextNode(fast, directions[fastInd]);
        fastInd = (fastInd + 1) % M;
    }
    // printNode(slow);
    // printNode(fast);
    // printf("slowInd = %d, fastInd = %d\n", slowInd, fastInd);
    // printf("Finished first step!\n");

    slowInd = 0;
    slow = node;
    long mu = 0;

    while (slow != fast || slowInd != fastInd) {
        // printNode(slow);
        // printNode(fast);
        // printf("slowInd = %d, fastInd = %d\n", slowInd, fastInd);

        slow = nextNode(slow, directions[slowInd]);
        slowInd = (slowInd + 1) % M;
        fast = nextNode(fast, directions[fastInd]);
        fastInd = (fastInd + 1) % M;
        mu++;
    }
    // printNode(slow);
    // printNode(fast);
    // printf("slowInd = %d, fastInd = %d\n", slowInd, fastInd);
    // printf("mu = %ld\n", mu);
    // printf("Finished second step\n");


    long lam = 1;
    fast = nextNode(fast, directions[fastInd]);
    fastInd = (fastInd + 1) % M;

    if (fast->isEnd) {
        printf("End node in cycle (ind 1 in cycle): ");
        printNode(fast);
    }

    while (slow != fast || slowInd != fastInd) {
        fast = nextNode(fast, directions[fastInd]);
        fastInd = (fastInd + 1) % M;
        lam++;

        if (fast->isEnd) {
            printf("End node in cycle (ind = %ld): ", lam);
            printNode(fast);
        }
    }

    if (fast->isEnd) {
        printf("End node in cycle (ind = 0): ");
        printNode(fast);
    }

    printf("mu = %ld, lam = %ld\n", mu, lam);
}