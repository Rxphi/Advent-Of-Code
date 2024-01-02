#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define NUM_OF_ROWS 1241
// #define NUM_OF_ROWS 13
#define MAX_NEIGH 9

// Structs: Component, Node, Queue, Stack
struct Component
{
    int id;
    int ind;
    int numOfNeigh;
    int prev;
    char name[4];
    int neighbors[MAX_NEIGH];
};

struct Node
{
    int value;
    struct Node *next;
};

struct Queue
{
    int size;
    struct Node *head;
    struct Node *tail;
};

struct Stack
{
    int size;
    struct Node *head;
};

// global variables
int numOfComponents;
struct Component *components;
static FILE *fp;

// functions
void openFile();
void readInput();
void solvePartI();
void printComp(struct Component *);
struct Node *newNode(int);
int dequeue(struct Queue *);
void enqueue(struct Queue *, int);
void push(struct Stack *, int);
int pop(struct Stack *);
int dfs(int, int *, int *, int *, int, int, int, int);

int main()
{
    printf("===Make sure the program is compiled with -O3 to make it run faster===\n");
    openFile();
    readInput();
    solvePartI();
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

int strToId(char *s)
{
    return (s[0] - 'a') + (s[1] - 'a') * 26 + (s[2] - 'a') * 26 * 26;
}

void readInput()
{
    // first pass to get the number of components
    numOfComponents = 0;
    int alreadySeen[26 * 26 * 26];
    memset(alreadySeen, 0, 26 * 26 * 26 * sizeof(int));
    char name[4];
    for (int i = 0; i < NUM_OF_ROWS; i++)
    {
        fscanf(fp, "%s", name);
        int id = strToId(name);
        if (!alreadySeen[id])
        {
            alreadySeen[id] = 1;
            numOfComponents++;
        }
        char c;
        while ((c = fgetc(fp)) != '\n' && c != EOF)
        {
            fscanf(fp, "%s", name);
            id = strToId(name);

            if (!alreadySeen[id])
            {
                alreadySeen[id] = 1;
                numOfComponents++;
            }
        }
    }

    // second pass to create the components
    openFile();
    int compInd = 0;
    components = (struct Component *)calloc(numOfComponents, sizeof(struct Component));
    memset(alreadySeen, 0, 26 * 26 * 26 * sizeof(int));
    for (int i = 0; i < NUM_OF_ROWS; i++)
    {
        fscanf(fp, "%s", name);
        int id = strToId(name);
        struct Component *currComp;
        if (!alreadySeen[id])
        {
            alreadySeen[id] = 1;
            components[compInd].id = id;
            components[compInd].ind = compInd;
            memcpy(components[compInd].name, name, 3);
            components[compInd].name[3] = '\0';
            currComp = &components[compInd];
            compInd++;
        }
        else
        {
            for (int j = 0; j < compInd; j++)
            {
                if (components[j].id == id)
                {
                    currComp = &components[j];
                    break;
                }
            }
        }
        char c;
        while ((c = fgetc(fp)) != '\n' && c != EOF)
        {
            fscanf(fp, "%s", name);
            id = strToId(name);

            struct Component *neigh;

            if (!alreadySeen[id])
            {
                alreadySeen[id] = 1;
                components[compInd].id = id;
                components[compInd].ind = compInd;
                memcpy(components[compInd].name, name, 3);
                components[compInd].name[3] = '\0';
                neigh = &components[compInd];
                compInd++;
            }
            else
            {
                for (int j = 0; j < compInd; j++)
                {
                    if (components[j].id == id)
                    {
                        neigh = &components[j];
                        break;
                    }
                }
            }
            currComp->neighbors[currComp->numOfNeigh++] = neigh->ind;
            neigh->neighbors[neigh->numOfNeigh++] = currComp->ind;
        }
    }

    // for (int i = 0; i < numOfComponents; i++)
    // {
    //     printComp(&components[i]);
    // }
    printf("num of components: %d\n", numOfComponents);
    printf("Read input successfully!\n");
}

// Helper functions for Stack and Queue
void enqueue(struct Queue *q, int val)
{
    struct Node *n = newNode(val);
    if (q->size == 0)
    {
        q->head = q->tail = n;
        q->size++;
        return;
    }
    q->tail->next = n;
    q->tail = n;
    q->size++;
}

int dequeue(struct Queue *q)
{
    int out;
    if (q->size == 1)
    {
        out = q->head->value;
        free(q->head);
        q->head = q->tail = NULL;
        q->size--;
        return out;
    }
    struct Node *oldHead = q->head;
    out = oldHead->value;
    q->head = q->head->next;
    q->size--;
    free(oldHead);
    return out;
}

int pop(struct Stack *s)
{
    int out;
    if (s->size == 1)
    {
        int out = s->head->value;
        free(s->head);
        s->head = NULL;
        s->size--;
        return out;
    }

    struct Node *top = s->head;
    out = top->value;
    s->head = s->head->next;
    s->size--;
    free(top);
    return out;
}

void push(struct Stack *s, int val)
{
    struct Node *n = newNode(val);

    if (s->size == 0)
    {
        s->head = n;
        s->size++;
        return;
    }

    n->next = s->head;
    s->head = n;
    s->size++;
}

struct Node *newNode(int val)
{
    struct Node *n = malloc(sizeof(struct Node));
    n->value = val;
    n->next = NULL;
    return n;
}

// Checks if the graph has a bridge when we look at the graph without the edges {e11, e12} and {e21, e22}
int *findBridge(int e11, int e12, int e21, int e22)
{
    int *dfsVal = calloc(numOfComponents, sizeof(int)); // number assigned during DFS to every node in the order that the nodes are visited
    int *lowVal = calloc(numOfComponents, sizeof(int)); // lowVal[v] := smallest dfsVal that can be reached from v using only DFS-Tree-edges and a non-DFS-Tree edge at the end of the path
    int currDfsVal = 0;
    dfs(0, dfsVal, lowVal, &currDfsVal, e11, e12, e21, e22);

    for (int i = 0; i < numOfComponents; i++)
    {
        int curr = components[i].ind;
        for (int j = 0; j < components[curr].numOfNeigh; j++)
        {
            int neigh = components[curr].neighbors[j];

            // ignore "removed" edges
            if ((curr == e11 && neigh == e12) || (curr == e12 && neigh == e11) || (curr == e21 && neigh == e22) || (curr == e22 && neigh == e21))
            {
                continue;
            }

            // use dfs- and lowVal to check if a bridge was found
            if (dfsVal[curr] < lowVal[neigh] || dfsVal[neigh] < lowVal[curr])
            {
                int *e3 = calloc(2, sizeof(int));
                e3[0] = curr;
                e3[1] = neigh;
                free(dfsVal);
                free(lowVal);
                return e3;
            }
        }
    }
    free(dfsVal);
    free(lowVal);
    return NULL;
}

// used by findBridge
int dfs(int curr, int *dfsVal, int *lowVal, int *currDfsVal, int e11, int e12, int e21, int e22)
{
    lowVal[curr] = dfsVal[curr] = ++(*currDfsVal);
    for (int i = 0; i < components[curr].numOfNeigh; i++)
    {
        int neigh = components[curr].neighbors[i];

        // ignore "removed" edges
        if ((curr == e11 && neigh == e12) || (curr == e12 && neigh == e11) || (curr == e21 && neigh == e22) || (curr == e22 && neigh == e21))
        {
            continue;
        }

        // compute new lowVal for curr
        int potLowVal = INT_MAX;
        if (dfsVal[neigh] > 0 && dfsVal[curr] - 1 != dfsVal[neigh])
        {
            potLowVal = dfsVal[neigh];
        }
        else if (dfsVal[neigh] == 0)
        {
            potLowVal = dfs(neigh, dfsVal, lowVal, currDfsVal, e11, e12, e21, e22); // recursive call
        }
        lowVal[curr] = potLowVal < lowVal[curr] ? potLowVal : lowVal[curr];
    }

    return lowVal[curr];
}

// Uses a BFS to find the nodes that are in one connected component and calculates result
int disconnectedGroups(int e11, int e12, int e21, int e22, int e31, int e32)
{
    int *visited = calloc(numOfComponents, sizeof(int));
    struct Queue q = {0};
    enqueue(&q, 0);
    visited[0] = 1;
    while (q.size > 0)
    {
        int curr = dequeue(&q);
        for (int i = 0; i < components[curr].numOfNeigh; i++)
        {
            int neigh = components[curr].neighbors[i];

            // ignore "removed" edges
            if ((curr == e11 && neigh == e12) || (neigh == e11 && curr == e12) || (curr == e21 && neigh == e22) || (neigh == e21 && curr == e22) || (curr == e31 && neigh == e32) || (neigh == e31 && curr == e32))
            {
                continue;
            }

            if (!visited[neigh])
            {
                visited[neigh] = 1;
                enqueue(&q, neigh);
            }
        }
    }
    int groupSize1 = 0;
    for (int i = 0; i < numOfComponents; i++)
    {
        if (visited[i])
        {
            groupSize1++;
        }
    }
    free(visited);
    return (numOfComponents - groupSize1) * groupSize1; // return result of partI
}

void solvePartI()
{
    int solutionI = 0;

    // calculate the number of edges in the graph (not used)
    int numOfEdges = 0;
    for (int i = 0; i < numOfComponents; i++)
    {
        numOfEdges += components[i].numOfNeigh;
    }
    numOfEdges /= 2;
    printf("Num of edges: %d\n", numOfEdges);
    printf("This takes some minutes, let the programm run in the background :-D\n");

    // Main idea/algorithm: Choose two edges that will be "removed" and check if the resulting graph has a bridge using a version of DFS
    // that computes dfs and low values
    int e11, e12, e21, e22, e31, e32;

    for (int i = 0; i < numOfComponents; i++)
    {
        e11 = components[i].ind;
        for (int j = 0; j < components[i].numOfNeigh; j++)
        {
            e12 = components[i].neighbors[j];
            for (int k = 0; k < numOfComponents; k++)
            {
                e21 = components[k].ind;
                for (int l = 0; l < components[k].numOfNeigh; l++)
                {
                    e22 = components[k].neighbors[l];

                    if ((e11 == e21 && e12 == e22) || (e11 == e22 && e12 == e21))
                    {
                        continue;
                    }

                    int *e3 = findBridge(e11, e12, e21, e22);

                    if (e3 == NULL)
                    {
                        continue;
                    }
                    else
                    {
                        e31 = e3[0];
                        e32 = e3[1];
                        free(e3);
                        goto foundBridges;
                    }
                }
            }
        }
    }
foundBridges:
    printf("Found bridges: (%s, %s), (%s, %s), (%s, %s)\n", components[e11].name, components[e12].name, components[e21].name, components[e22].name, components[e31].name, components[e32].name);

    solutionI = disconnectedGroups(e11, e12, e21, e22, e31, e32);

    printf("The solution to part I is: %d\n", solutionI);
}

// helper function to print components (not used)
void printComp(struct Component *comp)
{
    printf("%s: ", comp->name);

    for (int i = 0; i < comp->numOfNeigh; i++)
    {
        printf("%s ", components[comp->neighbors[i]].name);
    }
    printf("\n");
}