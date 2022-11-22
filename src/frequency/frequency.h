/**
* Structure et prototype de creation de la table de frequence
*
* @author  Nunes Borba Manoel / Quitman Lucas / Mozet Jacques-Arno
* @version 1.0
* @since   2022-09-11
*/

#ifndef FREQUENCY_H_INCLUDED
#define FREQUENCY_H_INCLUDED

typedef struct FrequencyListNode FrequencyListNode;
struct FrequencyListNode {
    char Symbol;
    int Frequency;
    FrequencyListNode *Next;
};

typedef struct FrequencyListRoot FrequencyListRoot;
struct FrequencyListRoot {
    FrequencyListNode * Start;
};

static FrequencyListRoot * initStaticFrequencyList();
FrequencyListRoot * generateStaticList(const char *filePath);
FrequencyListRoot * createFrequencyList();
static void incrementFrequency(FrequencyListNode * list, char symbol);
static void addElement(FrequencyListNode * list, char symbol);
static int alreadyAdded(FrequencyListNode * list, char symbol);
void findSymbolFrequency(FrequencyListNode * list, int *symbol);
int sortFrequencyList(FrequencyListNode * list);

#endif