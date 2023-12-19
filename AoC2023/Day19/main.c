#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define NUM_OF_WORKFLOWS 11
// #define NUM_OF_PARTS 5
// #define MAX_NUM_OF_DECISIONS 4

#define NUM_OF_WORKFLOWS 530
#define NUM_OF_PARTS 200
#define MAX_NUM_OF_DECISIONS 8

enum CompareOp {
    LESS,
    GREATER,
    NONE
};

struct Workflow {
    char label[4];
    int num_of_decisions;
    char variable[MAX_NUM_OF_DECISIONS];
    int value[MAX_NUM_OF_DECISIONS];
    enum CompareOp comparison[MAX_NUM_OF_DECISIONS];
    char nextLabel[MAX_NUM_OF_DECISIONS][4];
};

struct Part {
    int x;
    int m;
    int a;
    int s;
};

static FILE *fp;
struct Workflow workflows[NUM_OF_WORKFLOWS];
struct Part parts[NUM_OF_PARTS];



void openFile();
void readInput();
void solvePartI();
void solvePartII();
void printParts();
void printWorkflows();
struct Workflow *getWorkflow(char *);

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

void readInput()
{
    for (int i = 0; i < NUM_OF_WORKFLOWS; i++) {
        char row[80];
        fscanf(fp, "%s\n", row);

        // char * token = strtok(row, ",");

        char * currLabel = strtok(row, "{");
        memcpy(workflows[i].label, currLabel, 4);

        char * restRow = strtok(NULL, "{");


        char * token = strtok(restRow, ",");

        int j = 0;
        while (token != NULL) {
            int decisionLen = strlen(token);
            if (token[decisionLen-1] == '}') {
                token[decisionLen-1] = '\0';
                workflows[i].comparison[j] = NONE;
                sscanf(token, "%s", workflows[i].nextLabel[j]);
            } else {
                if (strstr(token, ">") == NULL) {
                    workflows[i].comparison[j] = LESS;
                } else {
                    workflows[i].comparison[j] = GREATER;
                }
                workflows[i].variable[j] = token[0];
                token += 2;
                sscanf(token, "%d:%s", &workflows[i].value[j], workflows[i].nextLabel[j]);
            }

            token = strtok(NULL, ",");
            j++;
        }
        workflows[i].num_of_decisions = j;
    }
    fscanf(fp, "\n");
    for (int i = 0; i < NUM_OF_PARTS; i++) {
        fscanf(fp, "{x=%d,m=%d,a=%d,s=%d}\n", &parts[i].x, &parts[i].m, &parts[i].a, &parts[i].s);
    }
    printWorkflows();
    printParts();
    printf("Read input successfully!\n");
}

int processPart(struct Part *p) {
    printf("Processing new part\n");

    char *currLabel = "in";

    int accepted = -1;

    while (1) {
        printf("%s\n", currLabel);
        struct Workflow *currWorkflow = getWorkflow(currLabel);

        for (int j = 0; j < currWorkflow->num_of_decisions; j++) {
            if (currWorkflow->comparison[j] == NONE) {
                switch (currWorkflow->nextLabel[j][0]) {
                    case 'A':
                        accepted = 1;
                        break;
                    case 'R':
                        accepted = 0;
                        break;
                    default:
                        currLabel = currWorkflow->nextLabel[j];
                        break;
                }
                break;
            } 
            
            int partVal;

            switch (currWorkflow->variable[j]) {
                case 'x':
                    partVal = p->x;
                    break;
                case 'm':
                    partVal = p->m;
                    break;
                case 'a':
                    partVal = p->a;
                    break;
                case 's':
                    partVal = p->s;
                    break;
            }

            int cmpVal = currWorkflow->value[j];
            
            if (currWorkflow->comparison[j] == LESS && partVal < cmpVal) {
                currLabel = currWorkflow->nextLabel[j];
                break;
            } else if (currWorkflow->comparison[j] == GREATER && partVal > cmpVal) {
                currLabel = currWorkflow->nextLabel[j];
                break;
            }

            if (accepted != -1) {
                break;
            }
        }

        if (currLabel[0] == 'A') {
            accepted = 1;
        } else if (currLabel[0] == 'R') {
            accepted = 0;
        }

        if (accepted != -1) {
            break;
        }
    }

    if (accepted == 1) {
        return p->x + p->m + p->a + p->s;
    }
    return 0;
}

struct Workflow * getWorkflow(char *label) {
    for (int i = 0; i < NUM_OF_WORKFLOWS; i++) {
        if (strncmp(label, workflows[i].label, 3) == 0) {
            return &workflows[i];
        }
    }
    return NULL;
}

void solvePartI()
{
    long solutionI = 0;
    for (int i = 0; i < NUM_OF_PARTS; i++) {
        int toAdd = processPart(&parts[i]);
        if (toAdd > 0) {
            printf("Accepted part #%d\n", i+1);
            solutionI += toAdd;
        } else {
            printf("Rejected part #%d\n", i+1);
        }
    }
    printf("The solution to part I is: %ld\n", solutionI);
}

void solvePartII()
{
    int solutionII = 0;
    printf("The solution to part II is: %d\n", solutionII);
}

void printWorkflows() {
    for (int i = 0; i < NUM_OF_WORKFLOWS; i++) {
        printf("Label %s (%d rules):\n", workflows[i].label, workflows[i].num_of_decisions);
        for (int j = 0; j < workflows[i].num_of_decisions; j++) {
            printf("Rule #%d ", j+1);
            if (workflows[i].comparison[j] == NONE) {
                printf("-> %s\n", workflows[i].nextLabel[j]);
            } else {
                printf("%c %c %d -> %s\n", workflows[i].variable[j], workflows[i].comparison[j] == GREATER ? '>' : '<', workflows[i].value[j], workflows[i].nextLabel[j]);
            }
        }
        printf("\n");
    }
}

void printParts() {
    for (int i = 0; i < NUM_OF_PARTS; i++) {
        printf("Part #%d: x = %d, m = %d, a = %d, s = %d\n", i+1, parts[i].x, parts[i].m, parts[i].a, parts[i].s);
    }
}