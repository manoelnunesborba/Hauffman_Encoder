/**
* Fonction de creation de la table de frequence
*
* @author  Nunes Borba Manoel / Quitman Lucas / Mozet Jacques-Arno
* @version 1.0
* @since   2022-09-11
*/


#include "word.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

LinkedListRoot * createDynammicRoot(){
    LinkedListRoot * root = malloc(sizeof(root));
    root->start = NULL;
    LinkedListWord * element = malloc(sizeof(LinkedListWord));
    element->next = NULL;
    element->letter = NULL;
    element->frequency = 0;
    root->start = element;
    return root;
}
void addStatic(LinkedListWord *list, char letter, int frequence){
    if(list->letter != letter){
        if(list->next == NULL && list->letter == NULL){
            list->frequency = frequence;
            list->letter = letter;
            LinkedListWord * newElement = malloc(sizeof(LinkedListWord));
            newElement->next = NULL;
            newElement->letter = NULL;
            list->next = newElement;
        }else {
            addStatic(list->next, letter, frequence);
        }
    }

}
LinkedListRoot * createStaticRoot(){
    LinkedListRoot * start = malloc(sizeof(start));
    start->start = NULL;
    LinkedListWord * element = malloc(sizeof(LinkedListWord));
    element->next = NULL;
    element->letter = NULL;
    element->frequency = 0.0;
    start->start = element;
    return start;
}
LinkedListRoot * ReadFileAndGenerateStruct(const char *FileName){
    FILE* ptr;
    char ch;
    LinkedListRoot *root = createStaticRoot();
    // Opening file in reading mode
    ptr = fopen(FileName, "r");
    if (NULL == ptr) {
        printf("file can't be opened \n");
    }
    int indice =0;
    int readNExtChar=1;
    int readNExtFrequency=0;
    char lettres[83];
    do {
        ch = fgetc(ptr);

        if(readNExtChar == 1 ){
            //add char
            lettres[indice] = ch;
        }
        if(readNExtFrequency == 1 ){
            //add frequency
            double freq;
            char tmp[9];
            int cnt =0;
            do{
                int i =ch;
                tmp[cnt]=ch;
                cnt++;
                ch = fgetc(ptr);
                freq=atof(tmp);
            }while(ch !=10 && ch != ' ');
            addStatic(root->start,lettres[indice],freq);
        }

        if(ch == '\t'){
            readNExtFrequency=1;
        }else{
            readNExtFrequency=0;
        }
        if(ch == 10){
            readNExtChar =1;
            indice++;
        }else{
            readNExtChar =0;
        }
        // Checking if character is not EOF.
        // If it is EOF stop eading.
    } while (ch != EOF);

    // Closing the file
    fclose(ptr);
    return root;
}

void addElement(LinkedListWord *list, char letter){
    if(list->next == NULL && list->letter == NULL){
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
void standardizedFrequency(LinkedListWord *list, int size){
    list->frequency = list->frequency/size;
    if(list->next != NULL){
        standardizedFrequency(list->next,size);
    }
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
    double temp2;
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