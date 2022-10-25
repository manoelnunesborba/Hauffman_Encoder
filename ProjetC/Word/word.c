//
// Stolen by manoel jacqu on 21/10/2022.
//

#include "word.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Start * createStart(){
    Start * start = malloc(sizeof(start));
    start->start = NULL;
    LinkedListWord * element = malloc(sizeof(LinkedListWord));
    element->next = NULL;
    element->letter = NULL;
    element->frequency = NULL;
    start->start = element;
    return start;
}

void addElement(LinkedListWord *list, char letter){
    if(list->next == NULL && list->letter == NULL && list->frequency == NULL){
        list->frequency = 1;
        list->letter = letter;
    } else {
        LinkedListWord * newElement = malloc(sizeof(LinkedListWord));
        newElement->frequency = 1;
        newElement->letter = letter;
        newElement->next = NULL;
        list->next = newElement;
    }
}

void incrementFrequency(LinkedListWord *list, char letter){
    if(list->letter == letter)
        list->frequency++;
    else if(list->next != NULL)
        incrementFrequency(list->next, letter);
    else
        addElement(list,letter);
}

int alrdyAdded(LinkedListWord * list, char letter){
    if(list->letter == letter)
        return 1;
    if(list->next == NULL)
        return 0;
    return alrdyAdded(list->next, letter);
}

void findLetterFrequency(LinkedListWord * list, char * word){
    for(int i = 0 ; word[i] != '\0' ; i++)
        if((word[i] >= 'a' && word[i] <= 'z') || word[i] >= 'A' && word[i] <= 'Z')
            incrementFrequency(list, word[i]);
}

void sortLinkedListWord(LinkedListWord * word){
    LinkedListWord * current = word;
    LinkedListWord * index = NULL;
    char temp;
    int temp2;
    if(word == NULL)
        return;
    else {
        do {
            index = current->next;
            while (index != NULL) {
                if (current->frequency > index->frequency) {
                    temp = current->letter;
                    temp2 = current->frequency;
                    current->letter = index->letter;
                    current->frequency = index->frequency;
                    index->letter = temp;
                    index->frequency = temp2;
                }
                index = index->next;
            }
            current = current->next;
        } while (current->next != NULL);
    }
}