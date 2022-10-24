#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Word/word.h"
// code style:
// Variable and function as camelCase:
// ex : firstName lastName hello thisIsQuiteGood
// Struct as PascalCase :
// ex: FirstName LastName Hello ThisIsQuiteGood

#define MAX_PATH 300
typedef char String[MAX_PATH];
typedef enum { false = 0, true = 1 } Booleen;
Booleen debugOn = false;

typedef struct {
	char key;
    int frequency; 

}HashMap[5];

void readInputString(String word){
    scanf("%s", word);
    if (debugOn) printf(">>echo %s\n", word);
}
Booleen hashMapHasValue(int size, char value, HashMap* output){
    for(int i =0; i<size; i++){
        if(output[i]->key == value)
            return true;
        if(debugOn)    printf("With. %u \n",output[i]->key);

    }
    return false;
}

int main() {
    String buffer;
    FILE *readFilePtr;
    int fileSize;
    char* fileBytes = NULL;
    HashMap bufferMap;
    printf("Hauffman encoder !\n");
    printf("Enter file name: ");
    readInputString(buffer);
    while(access(buffer, F_OK) != 0)
    {
        printf("\n File entered was not valid, try another :");
        readInputString(buffer);
    };

    if (fopen(buffer,"rb") != NULL) {
        FILE* readFilePtr= fopen(buffer,"rb");
        Start * start = createStart();
        fseek(readFilePtr, 0L, SEEK_END); 
        const long int res = ftell(readFilePtr); 
        fileBytes =(char*)malloc(res * sizeof( char));
        fseek(readFilePtr, 0L, SEEK_SET);
        fread(fileBytes,res,1,readFilePtr); 

        findLetterFrequency(start->start, fileBytes);
        sortLinkedListWord(start->start);
        /*fseek(readFilePtr, 0L, SEEK_END); 
        fileBytes =(char*)malloc(res * sizeof( char));
        fseek(readFilePtr, 0L, SEEK_SET);
        fread(fileBytes,res,1,readFilePtr); 
        frequencyFunction(res,fileBytes, &bufferMap);*/
        printf("\n");

    }else{
        printf("Error");
        return 1;
    }

    return 0;

}
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