//
// Stolen by manoel jacqu on 21/10/2022.
//

#include "word.h"
#include <stdlib.h>

LinkedListRoot * createRoot(){
    LinkedListRoot * root = malloc(sizeof(root));
    root->start = NULL;
    LinkedListWord * element = malloc(sizeof(LinkedListWord));
    element->next = NULL;
    element->letter = NULL;
    element->frequency = NULL;
    root->start = element;
    return root;
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
    for(int i = 0 ; word[i] != '\000' ; i++)
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

void addStack(LinkedListWord * list, int value) {
    if(list == NULL)
        return;
    LinkedListWord * newWord = malloc(sizeof(LinkedListWord));
    newWord->frequency = value;
    newWord->letter = NULL;
    newWord->next = list->next;
    list->next = newWord;
}