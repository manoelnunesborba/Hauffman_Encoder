/**
* Fonction de creation de la table de frequence
*
* @author  Nunes Borba Manoel / Quitman Lucas / Mozet Jacques-Arno
* @version 1.0
* @since   2022-09-11
*/


#include "frequency.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

FrequencyListRoot *createFrequencyList(){
    FrequencyListRoot *root = malloc(sizeof(root));
    root->Start = NULL;
    FrequencyListNode * element = malloc(sizeof(FrequencyListNode));
    element->Next = NULL;
    element->Symbol = NULL;
    element->Frequency = 0;
    root->Start = element;
    return root;
}

static void addStatic(FrequencyListNode *list, char symbol, int frequency){
    if(list->Symbol != symbol){
        if(list->Next == NULL && list->Symbol == NULL){
            list->Frequency = frequency;
            list->Symbol = symbol;
            FrequencyListNode * newElement = malloc(sizeof(FrequencyListNode));
            newElement->Next = NULL;
            newElement->Symbol = NULL;
            list->Next = newElement;
        }else {
            addStatic(list->Next, symbol, frequency);
        }
    }

}
static FrequencyListRoot * initStaticFrequencyList(){
    FrequencyListRoot * start = malloc(sizeof(start));
    start->Start = NULL;
    FrequencyListNode * element = malloc(sizeof(FrequencyListNode));
    element->Next = NULL;
    element->Symbol = NULL;
    element->Frequency = 0.0;
    start->Start = element;
    return start;
}
FrequencyListRoot * generateStaticList(const char *filename){
    FILE* statisticalModel;
    int symbol;
    FrequencyListRoot *root = initStaticFrequencyList();

    statisticalModel = fopen(filename, "r");
    if (NULL == statisticalModel) {
        errno=ENOENT;
        exit(1);
    }
    int index=0;
    int readNextChar=1;
    int readNextFrequency=0;
    char symbols[83];
    while ((symbol = fgetc(statisticalModel)) != EOF) {

        if(readNextChar == 1 ){
            //add char
            symbols[index] = symbol;
        }
        if(readNextFrequency == 1 ){
            //add frequency
            double freq;
            char tmp[9];
            int counter=0;
            do{
                int i = symbol;
                tmp[counter]=symbol;
                counter++;
                symbol = fgetc(statisticalModel);
                freq=atof(tmp);
            }while(symbol !=10 && symbol != ' ');
            addStatic(root->Start,symbols[index],freq);
        }

        if(symbol == '\t'){
            readNextFrequency=1;
        }else{
            readNextFrequency=0;
        }
        if(symbol == 10){
            readNextChar =1;
            index++;
        }else{
            readNextChar =0;
        }
    }

    fclose(statisticalModel);
    return root;
}

static void addElement(FrequencyListNode *node, char symbol){
    if(node->Next == NULL && node->Symbol == NULL){
        node->Frequency = 1;
        node->Symbol = symbol;
    } else {
        FrequencyListNode * newElement = malloc(sizeof(FrequencyListNode));
        newElement->Frequency = 1;
        newElement->Symbol = symbol;
        newElement->Next = NULL;
        node->Next = newElement;
    }
}

static void incrementFrequency(FrequencyListNode *node, char symbol){
    if(node->Symbol == symbol)
        node->Frequency++;
    else if(node->Next != NULL)
        incrementFrequency(node->Next, symbol);
    else
        addElement(node,symbol);
}

static int alreadyAdded(FrequencyListNode *node, char symbol){
    if(node->Symbol == symbol)
        return 1;
    if(node->Next == NULL)
        return 0;
    return alreadyAdded(node->Next, symbol);
}

void findSymbolFrequency(FrequencyListNode *node, int *symbol){
    for(int i = 0 ; symbol[i] != '\000' ; i++)
        incrementFrequency(node, symbol[i]);
}

int sortFrequencyList(FrequencyListNode *node){
    FrequencyListNode *current = node;
    FrequencyListNode *index = NULL;
    char temp;
    double temp2;
    if(node == NULL) {
        perror("node is NULL");
        return -1;
    }
    else {
        do {
            index = current->Next;
            while (index != NULL) {
                if (current->Frequency > index->Frequency) {
                    temp = current->Symbol;
                    temp2 = current->Frequency;
                    current->Symbol = index->Symbol;
                    current->Frequency = index->Frequency;
                    index->Symbol = temp;
                    index->Frequency = temp2;
                }
                index = index->Next;
            }
            current = current->Next;
        } while (current->Next != NULL);
    }
    return 0;
}