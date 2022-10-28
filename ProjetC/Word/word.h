//
// Stolen by manoel on 21/10/2022.
//

#ifndef TEST5_WORD_H
#define TEST5_WORD_H

typedef struct LinkedListWord LinkedListWord;
struct LinkedListWord {
    char letter;
    int frequency;
    LinkedListWord *next;
};

typedef struct LinkedListRoot LinkedListRoot;
struct LinkedListRoot {
    LinkedListWord * start;
};
typedef struct Start Start;

struct Start {
    LinkedListWord * start;
};


Start * createRoot();
Start * createStaticStart();
void incrementFrequency(LinkedListWord * list, char letter);
void addElement(LinkedListWord * list, char letter);
int alrdyAdded(LinkedListWord * list, char letter);
void findLetterFrequency(LinkedListWord * list, char * word);
void sortLinkedListWord(LinkedListWord * list);
void addStack(LinkedListWord * list, int value);
#endif //TEST5_WORD_H
