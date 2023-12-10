#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 140
#define M 140
// #define N 10
// #define M 20

enum Type {
    LOOP,
    INSIDE,
    OUTSIDE,
    NONE
};

// structs
struct Node {
    char symbol;
    int visited;
    int i, j;
    struct Node * neighbor1;
    struct Node * neighbor2;
    enum Type type;
};

// global variables
static FILE *fp;
struct Node grid[N][M];
struct Node *startNode = NULL;

// functions
void openFile();
void readInput();
void solvePartI();
void solvePartII();

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

    if (fp == NULL) {
        perror("The file could not be opened!\n");
        exit(1);
    }
    else {
        printf("Opened input file successfully!\n");
    }
}

void readInput() {
    int starti, startj;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            char shape;
            fscanf(fp, "%c", &shape);
            struct Node * node = &grid[i][j];
            node->symbol = shape;
            node->visited = 0;
            node->i = i;
            node->j = j;
            node->type = NONE;
            switch (shape) {
                case '|':
                    if (i == 0) {
                        node->neighbor1 = &grid[i+1][j];
                        node->neighbor2 = NULL;
                    } else if (i == N-1) {
                        node->neighbor1 = &grid[i-1][j];
                        node->neighbor2 = NULL;
                    } else {
                        node->neighbor1 = &grid[i-1][j];
                        node->neighbor2 = &grid[i+1][j];
                    }
                    break;
                case '-':
                    if (j == 0) {
                        node->neighbor1 = &grid[i][j+1];
                        node->neighbor2 = NULL;
                    } else if (j == M-1) {
                        node->neighbor1 = &grid[i][j-1];
                        node->neighbor2 = NULL;
                    } else {
                        node->neighbor1 = &grid[i][j-1];
                        node->neighbor2 = &grid[i][j+1];
                    }
                    break;
                case 'L':
                    if (i == 0 && j == M-1) {
                        node->neighbor1 = NULL;
                        node->neighbor2 = NULL;
                    } else if (i == 0) {
                        node->neighbor1 = &grid[i][j+1];
                        node->neighbor2 = NULL;
                    } else if (j == M-1) {
                        node->neighbor1 = &grid[i-1][j];
                        node->neighbor2 = NULL;
                    } else {
                        node->neighbor1 = &grid[i-1][j];
                        node->neighbor2 = &grid[i][j+1];
                    }
                    break;
                case 'J':
                    if (i == 0 && j == 0) {
                        node->neighbor1 = NULL;
                        node->neighbor2 = NULL;
                    } else if (i == 0) {
                        node->neighbor1 = &grid[i][j-1];
                        node->neighbor2 = NULL;
                    } else if (j == 0) {
                        node->neighbor1 = &grid[i-1][j];
                        node->neighbor2 = NULL;
                    } else {
                        node->neighbor1 = &grid[i][j-1];
                        node->neighbor2 = &grid[i-1][j];
                    }
                    break;
                case '7':
                    if (i == N-1 && j == 0) {
                        node->neighbor1 = NULL;
                        node->neighbor2 = NULL;
                    } else if (i == N-1) {
                        node->neighbor1 = &grid[i][j-1];
                        node->neighbor2 = NULL;
                    } else if (j == 0) {
                        node->neighbor1 = &grid[i+1][j];
                        node->neighbor2 = NULL;
                    } else {
                        node->neighbor1 = &grid[i][j-1];
                        node->neighbor2 = &grid[i+1][j];
                    }
                    break;
                case 'F':
                    if (i == N-1 && j == M-1) {
                        node->neighbor1 = NULL;
                        node->neighbor2 = NULL;
                    } else if (i == N-1) {
                        node->neighbor1 = &grid[i][j+1];
                        node->neighbor2 = NULL;
                    } else if (j == M-1) {
                        node->neighbor1 = &grid[i+1][j];
                        node->neighbor2 = NULL;
                    } else {
                        node->neighbor1 = &grid[i][j+1];
                        node->neighbor2 = &grid[i+1][j];
                    }
                    break;
                case '.':
                    node->neighbor1 = NULL;
                    node->neighbor2 = NULL;
                    break;
                case 'S':
                    startNode = &grid[i][j];
                    starti = i;
                    startj = j;
                    break;
                case '\n':
                    break;
                default:
                    printf("Wrong input format at (%d, %d)!!!", i, j);
                    break;
            }
            printf("%c", shape);
        }

        fscanf(fp, "\n");
        printf("\n");
    }

    // connect start node
    if (starti-1 >= 0 && (grid[starti-1][startj].symbol == '|' || grid[starti-1][startj].symbol == '7' || grid[starti-1][startj].symbol == 'F')) {
        startNode->neighbor1 = &grid[starti-1][startj];
    }

    if (starti+1 < N && (grid[starti+1][startj].symbol == '|' || grid[starti+1][startj].symbol == 'L' || grid[starti+1][startj].symbol == 'J')) {
        if (startNode->neighbor1 == NULL) {
            startNode->neighbor1 = &grid[starti+1][startj];
        } else {
            startNode->neighbor2 = &grid[starti+1][startj];
        }
    }

    if (startj-1 >= 0 && (grid[starti][startj-1].symbol == '-' || grid[starti][startj-1].symbol == 'L' || grid[starti][startj-1].symbol == 'F')) {
        if (startNode->neighbor1 == NULL) {
            startNode->neighbor1 = &grid[starti][startj-1];
        } else {
            startNode->neighbor2 = &grid[starti][startj-1];
        }
    }

    if (startj+1 < M && (grid[starti][startj+1].symbol == '-' || grid[starti][startj+1].symbol == 'J' || grid[starti][startj+1].symbol == '7')) {
        if (startNode->neighbor1 == NULL) {
            startNode->neighbor1 = &grid[starti][startj+1];
        } else {
            startNode->neighbor2 = &grid[starti][startj+1];
            return;
        }
    }

    printf("\nRead input successfully!\n");
}

void printNode(struct Node * node) {
    printf("Node %c at (%d, %d), visited: %d\n", node->symbol, node->i, node->j, node->visited);
}

void solvePartI() {
    int solutionI = 0;

    startNode->visited = 1;
    startNode->type = LOOP;
    printf("Start Node: ");
    printNode(startNode);

    struct Node * curr = startNode->neighbor1;
    curr->visited = 1;

    int cycleLength = 1;
    
    while (curr->symbol != 'S') {
        cycleLength++;
        curr->type = LOOP;
        // printNode(curr);
        if (curr->neighbor1 != NULL && !curr->neighbor1->visited) {
            curr = curr->neighbor1;
            curr->visited = 1;
        } else if (curr->neighbor2 != NULL && !curr->neighbor2->visited){
            curr = curr->neighbor2;
            curr->visited = 1;
        } else {
            break;
        }
    }

    solutionI = cycleLength / 2;
    printf("Cycle Length: %d\n", cycleLength);
    printf("The solution to part I is: %d\n", solutionI);
}

void solvePartII() {
    int solutionII = 0;
     
    // replace symbol of start node
    printf("Replaced Start symbol with ");
    if (startNode->neighbor1->i != startNode->i && startNode->neighbor2->i != startNode->i) {
        startNode->symbol = '|';
    } else if (startNode->neighbor1->j != startNode->j && startNode->neighbor2->j != startNode->j) {
        startNode->symbol = '-';
    } else if ((startNode->neighbor1->i+1 == startNode->i && startNode->neighbor2->j-1 == startNode->j) || (startNode->neighbor2->i+1 == startNode->i && startNode->neighbor1->j-1 == startNode->j)) {
        startNode->symbol = 'L';
    } else if ((startNode->neighbor1->i+1 == startNode->i && startNode->neighbor2->j+1 == startNode->j) || (startNode->neighbor2->i+1 == startNode->i && startNode->neighbor1->j+1 == startNode->j)) {
        startNode->symbol = 'J';
    } else if ((startNode->neighbor1->i-1 == startNode->i && startNode->neighbor2->j+1 == startNode->j) || (startNode->neighbor2->i-1 == startNode->i && startNode->neighbor1->j+1 == startNode->j)) {
        startNode->symbol = '7';
    } else if ((startNode->neighbor1->i-1 == startNode->i && startNode->neighbor2->j-1 == startNode->j) || (startNode->neighbor2->i-1 == startNode->i && startNode->neighbor1->j-1 == startNode->j)) {
        startNode->symbol = 'F';
    }
    printf("%c\n", startNode->symbol);

    for (int i = 0; i < N; i++) {
        enum Type currentType = OUTSIDE;
        int j = 0;
        while (j < M) {
            if (grid[i][j].type == LOOP) {
                if (grid[i][j].symbol == '|') {
                    currentType = currentType == INSIDE ? OUTSIDE : INSIDE;
                    j++;
                    continue;
                }
                char startSymbol = grid[i][j].symbol;
                j++;
                while (grid[i][j].symbol != 'J' && grid[i][j].symbol != '7') {
                    j++;
                }
                char endSymbol = grid[i][j].symbol;
                int startPointsUp = startSymbol == 'L';
                int endPointsUp = endSymbol == 'J';
                if (startPointsUp ^ endPointsUp) {
                    currentType = currentType == INSIDE ? OUTSIDE : INSIDE;
                }
                j++;
            } else {
                grid[i][j].type = currentType;
                j++;
            }
        }
        // printf("\n");
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j].type == INSIDE) {
                printf("I");
                solutionII++;
            } else if (grid[i][j].type == OUTSIDE) {
                printf("O");
            } else {
                printf("%c", grid[i][j].symbol);
            }
        }
        printf("\n");
    }

    printf("The solution to part II is: %d\n", solutionII);
}