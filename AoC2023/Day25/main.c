#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define NUM_OF_ROWS 1241
// #define NUM_OF_ROWS 13

#define MAX_NEIGH 9

struct Component { 
    int id;
    int ind;
    int numOfNeigh;
    int prev;
    char name[4];
    int neighbors[MAX_NEIGH];
};

struct Node {
    int value;
    struct Node *next;
};

struct Queue {
    int size;
    struct Node *head;
    struct Node *tail;
};

struct Stack {
    int size;
    struct Node *head;
};

int numOfComponents;
struct Component *components;
static FILE *fp;

void openFile();
void readInput();
void solvePartI();
void solvePartII();
void printComp(struct Component *);
struct Node *newNode(int);
int dequeue(struct Queue *);
void enqueue(struct Queue *, int);
void push(struct Stack *, int);
int pop(struct Stack *);

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

int strToId(char *s) {
    // printf("%c%c%c\n", s[0], s[1], s[2]);
    return (s[0]-'a') + (s[1]-'a') * 26 + (s[2]-'a') * 26 * 26;
}

void readInput()
{
    // first pass to get the number of components
    numOfComponents = 0;
    int alreadySeen[26*26*26];
    memset(alreadySeen, 0, 26*26*26*sizeof(int));
    char name[4];
    for (int i = 0; i < NUM_OF_ROWS; i++) {
        fscanf(fp, "%s", name);
        int id = strToId(name);
        
        if (!alreadySeen[id]) {
            alreadySeen[id] = 1;
            numOfComponents++;
        }

        char c;
        while ((c = fgetc(fp)) != '\n' && c != EOF) {
            fscanf(fp, "%s", name);
            id = strToId(name);

            if (!alreadySeen[id]) {
                alreadySeen[id] = 1;
                numOfComponents++;
            }
        }
    }

    // second pass to create the components
    openFile();

    int compInd = 0;
    components = (struct Component *) calloc(numOfComponents, sizeof(struct Component));
    memset(alreadySeen, 0, 26*26*26*sizeof(int));

    for (int i = 0; i < NUM_OF_ROWS; i++) {
        fscanf(fp, "%s", name);
        int id = strToId(name);
        
        struct Component *currComp;

        if (!alreadySeen[id]) {
            alreadySeen[id] = 1;
            components[compInd].id = id;
            components[compInd].ind = compInd;
            memcpy(components[compInd].name, name, 3);
            components[compInd].name[3] = '\0';
            currComp = &components[compInd];
            compInd++;
        } else {
            for (int j = 0; j < compInd; j++) {
                if (components[j].id == id) {
                    currComp = &components[j];
                    break;
                }
            }
        }

        char c;
        while ((c = fgetc(fp)) != '\n' && c != EOF) {
            fscanf(fp, "%s", name);
            id = strToId(name);
            
            struct Component *neigh;

            if (!alreadySeen[id]) {
                alreadySeen[id] = 1;
                components[compInd].id = id;
                components[compInd].ind = compInd;
                memcpy(components[compInd].name, name, 3);
                components[compInd].name[3] = '\0';
                neigh = &components[compInd];
                compInd++;
            } else {
                for (int j = 0; j < compInd; j++) {
                    if (components[j].id == id) {
                        neigh = &components[j];
                        break;
                    }
                }
            }
            
            // TODO Debug
            currComp->neighbors[currComp->numOfNeigh++] = neigh->ind;
            neigh->neighbors[neigh->numOfNeigh++] = currComp->ind;
        }
    }

    // int maxNumOfNeigh = 0;
    for (int i = 0; i < numOfComponents; i++) {
        printComp(&components[i]);
        // maxNumOfNeigh = components[i].numOfNeigh > maxNumOfNeigh ? components[i].numOfNeigh : maxNumOfNeigh;
    }
    // printf("Max num of neigh: %d\n", maxNumOfNeigh);
    printf("num of components: %d\n", numOfComponents);
    printf("Read input successfully!\n");
}

void enqueue(struct Queue *q, int val) {
    struct Node *n = newNode(val);

    if (q->size == 0) {
        q->head = q->tail = n;
        q->size++;
        return;
    }

    q->tail->next = n;
    q->tail = n;
    q->size++;
}

int dequeue(struct Queue *q) {
    int out;
    if (q->size == 1) {
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

int pop(struct Stack *s) {
    int out;
    if (s->size == 1) {
        int out = s->head->value;
        free(s->head);
        s->head = NULL;
        s->size--;
        return out;
    }

    struct Node *top = s->head;
    int out = top->value;
    s->head = s->head->next;
    s->size--;
    free(top);
    return out;
}

void push(struct Stack *s, int val) {
    struct Node *n = newNode(val);
    
    if (s->size == 0) {
        s->head = n;
        s->size++;
        return;
    }

    n->next = s->head;
    s->head = n;
    s->size++;
}

struct Node *newNode(int val) {
    struct Node *n = malloc(sizeof(struct Node));
    n->value = val;
    n->next = NULL;
    return n;
}

// not used currently
void bfs(int start, int end, int *edgeCounter) {
    struct Queue q = {0};

    enqueue(&q, start);
    int visited[numOfComponents];
    memset(visited, 0, numOfComponents * sizeof(int));

    int dist = 0;

    while (q.size > 0) {
        int toProcess = q.size;
        dist++;
        for (int i = 0; i < toProcess; i++) {
            int curr = dequeue(&q);
            
            for (int j = 0; j < components[curr].numOfNeigh; j++) {
                int neigh = components[curr].neighbors[j];
                if (visited[neigh]) {
                    continue;
                }
                visited[neigh] = 1;
                if (dist > 10) {
                    edgeCounter[numOfComponents*i+j]++;
                    edgeCounter[numOfComponents*j+i]++;
                }
                if (neigh == end) {
                    return;
                }
                enqueue(&q, neigh);
            }
        }
    }
}

// checks if the graph has a bridge when we look at the graph without the edges {e11, e12} and {e21, e22}
int *findBridge(int e11, int e12, int e21, int e22) {
    int dfs[numOfComponents];
    memset(dfs, 0, numOfComponents * sizeof(int));
    int low[numOfComponents];
    memset(low, INT_MAX, numOfComponents * sizeof(int));

    struct Stack s = {0};
    push(&s, 0);

    int cnt = 0;

    while (s.size > 0) {
        int curr = pop(&s);
        dfs[curr] = ++cnt;

        for (int i = 0; i < components[curr].numOfNeigh; i++) {
            int neigh = components[curr].neighbors[i];
            if (dfs[neigh] > 0) { // already visited
                low[neigh] = dfs[curr] < low[neigh] ? dfs[curr] : low[neigh];
                continue;
            }
        }
    }

    // TODO use dfs- and low-values to check if a bridge was found and return it.
}

void solvePartI()
{

    // Idee: Wähle zwei Edges aus, die aus dem Graph gelöscht werden und checke dann ob der übrige Graph eine Brücke enthält.
    int solutionI = 0;

    int numOfEdges = 0;
    for (int i = 0; i < numOfComponents; i++) {
        numOfEdges += components[i].numOfNeigh;
    }
    numOfEdges /= 2;
    printf("Num of edges: %d\n", numOfEdges);

    printf("The solution to part I is: %d\n", solutionI);
}

void solvePartII()
{
    int solutionII = 0;
    printf("The solution to part II is: %d\n", solutionII);
}

void printComp(struct Component *comp) {
    printf("%s: ", comp->name);

    for (int i = 0; i < comp->numOfNeigh; i++) {
        printf("%s ", components[comp->neighbors[i]].name);
    }
    printf("\n");
}