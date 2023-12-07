#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// number of hands
// #define N 5
#define N 1000

static FILE *fp;

enum Type {
    FiveOfAKind,
    FourOfAKind,
    FullHouse,
    ThreeOfAKind,
    TwoPair,
    OnePair,
    HighCard
};

struct Hand {
    char cards[5];
    enum Type type;
    int bid;
    int rank;
};

struct Hand *hands[N];

void openFile();
void readInput();
struct Hand * createNewHand(char *, int);
void solvePartII();
void printHand(struct Hand *);

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
    // fp = fopen("../test.txt", "r");
    fp = fp = fopen("../input.txt", "r");

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
    char currentCards[5];
    int currentBid;
    for (int i = 0; i < N; i++) {
        fscanf(fp, "%s %d\n", currentCards, &currentBid);
        hands[i] = createNewHand(currentCards, currentBid);
    }
    printf("Read input successfully!\n");
}

struct Hand * createNewHand(char *cards, int bid) {
    printf("Creating new cards, input: %5s, %d\n", cards, bid);
    struct Hand * pHand = (struct Hand *) calloc(sizeof(struct Hand), 1);
    memcpy(pHand->cards, cards, 5);
    pHand->bid = bid;

    // 0 -> 2, 1 -> 3, ..., 7 -> 9, 8 -> T, 9 -> J, 10 -> Q, 11 -> K, 12 -> A
    int cardsCount[13];
    for (int i = 0; i < 13; i++) cardsCount[i] = 0;

    for (int i = 0; i < 5; i++) {
        char currentCard = cards[i];

        if (isdigit(currentCard)) {
            cardsCount[currentCard-'2']++;
        } else {
            switch (currentCard) {
            case 'T':
                cardsCount[8]++;
                break;
            case 'J':
                cardsCount[9]++;
                break;
            case 'Q':
                cardsCount[10]++;
                break;
            case 'K':
                cardsCount[11]++;
                break;
            default:
                cardsCount[12]++;
                break;
            }
        }
    }

    int numOfJokers = cardsCount[9];
    int highestCount = 0;
    int secondHighest = 0;

    for (int i = 0; i < 13; i++) {
        if (i == 9) {
            continue;
        }
        if (highestCount < cardsCount[i]) {
            secondHighest = highestCount;
            highestCount = cardsCount[i];
        } else if (secondHighest < cardsCount[i]) {
            secondHighest = cardsCount[i];
        }
    }

    // determine Type
    switch (highestCount) {
    case 5:
        pHand->type = FiveOfAKind;
        break;
    case 4:
        pHand->type = numOfJokers == 1 ? FiveOfAKind : FourOfAKind;
        break;
    case 3:
        if (numOfJokers == 2) {
            pHand->type = FiveOfAKind;
        } else if (numOfJokers == 1) {
            pHand->type = FourOfAKind;
        } else if (secondHighest == 2) {
            pHand->type = FullHouse;
        } else {
            pHand->type = ThreeOfAKind;
        }
        break;
    case 2:
        if (numOfJokers == 3) {
            pHand->type = FiveOfAKind;
        } else if (numOfJokers == 2) {
            pHand->type = FourOfAKind;
        } else if (numOfJokers == 1) {
            pHand->type = secondHighest == 2 ? FullHouse : ThreeOfAKind;
        } else if (secondHighest == 2) {
            pHand->type = TwoPair;
        } else {
            pHand->type = OnePair;
        }
        break;
    default:
        switch (numOfJokers) {
        case 5:
            pHand->type = FiveOfAKind;
            break;
        case 4:
            pHand->type = FiveOfAKind;
            break;
        case 3:
            pHand->type = FourOfAKind;
            break;
        case 2:
            pHand->type = ThreeOfAKind;
            break;
        case 1:
            pHand->type = OnePair;
            break;
        default:
            pHand->type = HighCard;
            break;
        }
        break;
    }
    // printf("Created new card ");
    // printHand(pHand);
    return pHand;
}

// returns -1, 0 or 1 (hand1 wins, both hands are equal, hand2 wins)
int compare(struct Hand * hand1, struct Hand * hand2) {
    if (hand1->type != hand2->type) {
        return hand1->type < hand2->type ? -1 : 1;
    }

    for (int i = 0; i < 5; i++) {
        char c1 = hand1->cards[i];
        char c2 = hand2->cards[i];
        if (c1 != c2) {
            if (c1 == 'J') {
                return 1;
            } else if (c2 == 'J') {
                return -1;
            }

            if (isdigit(c1)) {
                if (isdigit(c2)) {
                    return c1 - c2 < 0 ? 1 : -1;
                } else {
                    return 1;
                }
            } else {
                if (isdigit(c2)) {
                    return -1;
                } else {
                    switch (c1) {
                    case 'A':
                        return -1;
                    case 'K':
                        return c2 == 'A' ? 1 : -1;
                    case 'Q':
                        return c2 == 'A' || c2 == 'K' ? 1 : -1;
                    case 'J':
                        return c2 == 'T' ? -1 : 1;
                    default:
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

void solvePartII()
{
    int solutionII = 0;

    for (int rank = 1; rank <= N; rank++) {
        struct Hand *currentHand = NULL;
        for (int i = 0; i < N; i++) {
            struct Hand *otherHand = hands[i];
            if (otherHand->rank != 0) {
                continue;
            } else if (currentHand == NULL) {
                currentHand = otherHand;
            } else if (compare(otherHand, currentHand) == 1) {
                currentHand = otherHand;
            }
        }
        currentHand->rank = rank;

        printf("Rank #%d ", rank);
        printHand(currentHand);

        solutionII += currentHand->bid * currentHand->rank;
    }

    printf("The solution to part II is: %d\n", solutionII);
}

void printHand(struct Hand * pHand) {
    printf("Cards: %5s, Type:%d, Bid: %d\n", pHand->cards, pHand->type, pHand->bid);
}