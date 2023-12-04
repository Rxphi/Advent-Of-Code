#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define N 5
// #define M 8
// #define NUM_OF_CARDS 6

#define N 10
#define M 25
#define NUM_OF_CARDS 201

#define PRINT 1

static FILE *fp;

void openFile();
void readInput();
void solvePartI();
void solvePartII();
void printCard();
void printArr(int *, int);

struct Card {
    int id;
    int winningNums[N];
    int myNums[M];
    int matches;
    int points;
};

struct Card cards[NUM_OF_CARDS];

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
    } else {
        printf("Opened input file successfully!\n");
    }
}

void readInput() {
    for (int i = 0; i < NUM_OF_CARDS; i++) {

        struct Card *currentCard = &cards[i];
        currentCard->points = 0;

        fscanf(fp, "Card %d: ", &currentCard->id);

        for (int j = 0; j < N; j++) {
            fscanf(fp, "%d", &currentCard->winningNums[j]);
        }

        fscanf(fp, " | ");

        for (int j = 0; j < M; j++) {
            fscanf(fp, "%d", &currentCard->myNums[j]);
        }

        fscanf(fp, "\n");
    }
    printf("Read input successfully!\n");
}


void solvePartI() {
    int solutionI = 0;

    for (int i = 0; i < NUM_OF_CARDS; i++) {

        struct Card *currentCard = &cards[i];
        int numOfMatches = 0;

        for (int j = 0; j < M; j++) {

            int myCard = currentCard->myNums[j];
            int found = 0;

            for (int k = 0; k < N; k++) {
                int winningCard = currentCard->winningNums[k];
                if (myCard == winningCard) {
                    found = 1;
                    break;
                }
            }

            if (found) {
                numOfMatches++;
            }
        }

        currentCard->matches = numOfMatches;
        currentCard->points = numOfMatches > 0 ? 1 << (numOfMatches-1) : 0;
        solutionI += currentCard->points;

        if (PRINT) printCard(currentCard);
    }

    printf("The solution to part I is: %d\n", solutionI);
}

void solvePartII() {
    int solutionII = 0;
    int copies[NUM_OF_CARDS];

    for (int i = 0; i < NUM_OF_CARDS; i++) {
        copies[i] = 1;
    }

    for (int i = 0; i < NUM_OF_CARDS; i++) {

        struct Card *currentCard = &cards[i];
        int c = copies[i];

        for (int j = 1; j <= currentCard->matches; j++) {
            copies[i+j] += c;
        }

        if (PRINT) printf("#Copies of card %3d: %d\n", i+1, c);
        solutionII += c;
    }
    
    printf("The solution to part II is: %d\n", solutionII);
}

void printCard(struct Card *cardP) {
    printf("Card %d (%d matches, %d points): ", cardP->id, cardP->matches, cardP->points);

    for (int i = 0; i < N; i++) {
        printf("%3d", cardP->winningNums[i]);
    }

    printf(" |");

    for (int i = 0; i < N; i++) {
        printf("%3d", cardP->myNums[i]);
    }

    printf("\n");
}