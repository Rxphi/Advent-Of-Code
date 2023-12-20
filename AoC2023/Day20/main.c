#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM_OF_CONNECTIONS 10
#define NUM_OF_MODULES 58
// #define NUM_OF_MODULES 5

#define BROADCAST_ID 20000

enum ModuleType {
    FLIPFLOP,
    CONJUNTION,
    BROADCAST,
};

enum SignalType {
    LOW,
    HIGH
};

struct Module {
    int id;
    int ind;
    enum ModuleType type;
    int numOfInputs;
    int *inputs;
    int numOfOutputs;
    int *outputs;
    enum SignalType *memory;
    enum SignalType state;
};

struct Signal {
    enum SignalType value;
    int sender;
    int receiver;
    struct Signal *next;
};

struct SignalQueue {
    int size;
    struct Signal *head;
    struct Signal *tail;
};

struct Module *broadcaster;
struct Module *modules[58];
static FILE *fp;

void openFile();
void readInput();
void solvePartI();
void solvePartII();
void printModule(struct Module *);
struct Signal *createNewSignal(enum SignalType, int, int);
void enqueueSignal(struct SignalQueue *, struct Signal *);
struct Signal * processNextSignal(struct SignalQueue *);
void printSignal(struct Signal *);

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

struct Module * getNewModule () {
    struct Module * newModule = calloc(sizeof(struct Module), 1);
    return newModule;
}

void readInput()
{
    for (int i = 0; i < NUM_OF_MODULES; i++) {
        struct Module *newModule = getNewModule();
        char c;
        fscanf(fp, "%1c", &c);
        switch (c) {
            case 'b':
                newModule->type = BROADCAST;
                broadcaster = newModule;
                break;
            case '%':
                newModule->type = FLIPFLOP;
                break;
            case '&':
                newModule->type = CONJUNTION;
                break;
            default:
                printf("Cannot read module that starts with %1c!!!", c);
                break;
        }

        char temp[20];
        fscanf(fp, "%s", temp);

        if (newModule->type == BROADCAST) {
            newModule->id = BROADCAST_ID;
        } else {
            for (int j = 0, base = 1; j < strlen(temp); j++, base *= 26) {
                newModule->id += (temp[j] - 'a') * base;
            }
        }
        fscanf(fp, " -> ");

        newModule->numOfOutputs = 0;

        char restRow[40];
        fgets(restRow, 40, fp);
        char *tok = strtok(restRow, ", ");

        int outputIDs[MAX_NUM_OF_CONNECTIONS];
        while(tok != NULL) {
            int newID = 0;
            for (int j = 0, base = 1; j < strlen(tok); j++, base *= 26) {
                if (tok[j] == '\n' || tok[j] == EOF) {
                    break;
                }
                newID += (tok[j] - 'a') * base;
            }
            outputIDs[newModule->numOfOutputs++] = newID;
            tok = strtok(NULL, ", ");
        }
        newModule->outputs = (int *) calloc(sizeof(int) , newModule->numOfOutputs);
        memcpy(newModule->outputs, outputIDs, sizeof(int) * newModule->numOfOutputs);

        if (newModule->type == CONJUNTION) {
            newModule->memory = (enum SignalType *) calloc(sizeof(enum SignalType), newModule->numOfInputs);
        }

        newModule->ind = i;
        modules[i] = newModule;
    }

    for (int i = 0; i < NUM_OF_MODULES; i++) {
        for (int j = 0; j < modules[i]->numOfOutputs; j++) {
            for (int k = 0; k < NUM_OF_MODULES; k++) {
                if (modules[i]->outputs[j] == modules[k]->id) {
                    modules[i]->outputs[j] = modules[k]->ind;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < NUM_OF_MODULES; i++) {
        if (modules[i]->type != CONJUNTION) {
            continue;
        }
        int inputInd = 0;
        int inputs[MAX_NUM_OF_CONNECTIONS];
        for (int j = 0; j < NUM_OF_MODULES; j++) {
            if (i == j) {
                continue;
            }
            for (int k = 0; k < modules[j]->numOfOutputs; k++) {
                if (modules[i]->ind == modules[j]->outputs[k]) {
                    inputs[inputInd++] = modules[j]->ind;
                    break;
                }
            }
        }
        modules[i]->numOfInputs = inputInd;
        modules[i]->inputs = calloc(sizeof(int), inputInd);
        memcpy(modules[i]->inputs, inputs, sizeof(int) * inputInd);
    }
    

    for (int i = 0; i < NUM_OF_MODULES; i++) {
        printModule(modules[i]);
    }

    printf("Read input successfully!\n");
}

void enqueueSignal(struct SignalQueue *sq, struct Signal *s) {
    if (sq->size == 0) {
        sq->head = sq->tail = s;
    } else {
        sq->tail->next = s;
        sq->tail = s;
    }
    sq->size++;
}

struct Signal *popSignal(struct SignalQueue *sq) {
    if (sq->size == 0) {
        printf("Can't pop from empty queue!!!\n");
        exit(1);
    }

    struct Signal *s = sq->head;

    sq->head = sq->head->next;
    if (sq->size == 1) {
        sq->tail = NULL;
    }
    sq->size--;
    return s;
}

struct Signal * processNextSignal(struct SignalQueue *sq) {
    struct Signal *s = popSignal(sq);
    // printSignal(s);

    // process
    if (s->receiver < 0 || s->receiver >= NUM_OF_MODULES) {
        return s;
    }

    struct Module * m = modules[s->receiver];
    if (m->type == BROADCAST) {
        for (int i = 0; i < m->numOfOutputs; i++) {
            enqueueSignal(sq, createNewSignal(s->value, m->ind, m->outputs[i]));
        }
    } else if (m->type == FLIPFLOP && s->value == LOW) {
        m->state = m->state == LOW ? HIGH : LOW;
        for (int i = 0; i < m->numOfOutputs; i++) {
            enqueueSignal(sq, createNewSignal(m->state, m->ind, m->outputs[i]));
        }
    } else if (m->type == CONJUNTION) {
        // update memory
        int allHigh = 1;
        for (int i = 0; i < m->numOfInputs; i++) {
            if (s->sender == m->inputs[i]) {
                m->memory[i] = s->value;
            }
            allHigh = allHigh && (m->memory[i] == HIGH);
        }
        // send signal
        enum SignalType valToSend = allHigh ? LOW : HIGH;
        for (int i = 0; i < m->numOfOutputs; i++) {
            enqueueSignal(sq, createNewSignal(valToSend, m->ind, m->outputs[i]));
        }
    }

    return s;
}

struct Signal *createNewSignal(enum SignalType value, int sender, int receiver) {
    struct Signal *newSignal = calloc(sizeof(struct Signal), 1);
    newSignal->value = value;
    newSignal->sender = sender;
    newSignal->receiver = receiver;
    newSignal->next = NULL;
    return newSignal;
}

void pushButton(struct SignalQueue *sq) {
    enqueueSignal(sq, createNewSignal(LOW, -1, broadcaster->ind));
}

void solvePartI()
{
    long solutionI = 0;
    long lowSignals = 0;
    long highSignals = 0;
    struct SignalQueue sq = {0};

    for (int i = 0; i < 1000; i++) {
        // printf("Button push #%d\n", i+1);
        pushButton(&sq);
        while(sq.size > 0) {
            struct Signal *s = processNextSignal(&sq);
            if (s->value == LOW) {
                lowSignals++;
            } else {
                highSignals++;
            }
            free(s);
        }
    }

    solutionI = lowSignals * highSignals;
    printf("#Low = %ld, #High = %ld\n", lowSignals, highSignals);
    printf("The solution to part I is: %ld\n", solutionI);
}

long firstLow(struct Module *m) {
    return 0;
}

void solvePartII()
{
    long solutionII = 0;
    
    printf("The solution to part II is: %ld\n", solutionII);
}

void printModule(struct Module *m) {
    switch (m->type)
    {
    case BROADCAST:
        printf("BROADCAST ");
        break;
    case FLIPFLOP:
        printf("FLIPFLOP ");
        break;
    case CONJUNTION:
        printf("CONJUNTION ");
        break;
    }

    printf("%d -> ", m->ind);
    for (int i = 0; i < m->numOfOutputs; i++) {
        printf("%d ", m->outputs[i]);
    }

    if (m->type == CONJUNTION) {
        printf("Inputs -> ");
    }
    for (int i = 0; i < m->numOfInputs; i++) {
        printf("%d ", m->inputs[i]);
    }
    printf("\n");
}

void printSignal(struct Signal *s) {
    printf("%d -%s> %d\n", s->sender, s->value == LOW ? "low" : "high", s->receiver);
}