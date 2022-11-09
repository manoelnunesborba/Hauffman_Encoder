/**
* Structure et prototype de creation de la table de frequence
*
* @author  Nunes Borba Manoel / Quitman Lucas / Mozet Jacques-Arno
* @version 1.0
* @since   2022-09-11
*/


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

void standardizedFrequency(LinkedListWord *list, int size);
LinkedListRoot * createStaticRoot();
LinkedListRoot * createDynammicRoot();
void incrementFrequency(LinkedListWord * list, char letter);
void addElement(LinkedListWord * list, char letter);
int alrdyAdded(LinkedListWord * list, char letter);
void findLetterFrequency(LinkedListWord * list, char * word);
void sortLinkedListWord(LinkedListWord * list);
#endif //TEST5_WORD_H
