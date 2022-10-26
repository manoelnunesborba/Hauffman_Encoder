#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Word/word.h"
#include "Tree/huffman.h"
// code style:
// Variable and function as camelCase:
// ex : firstName lastName hello thisIsQuiteGood
// Struct as PascalCase :
// ex: FirstName LastName Hello ThisIsQuiteGood

#define MAX_PATH 300
#define MAX_WORD_LENGTH 100
typedef char String[MAX_PATH];
typedef enum { false = 0, true = 1 } Booleen;
Booleen debugOn = false;
typedef struct LinkedListWord LinkedListWord;
struct LinkedListWord {
    char letter;
    double frequency;
    LinkedListWord *next;
};

typedef struct Start Start;
struct Start {
    LinkedListWord * start;
};



void readInputString(String word);

Booleen hashMapHasValue(int size, char value, HashMap* output);

int isNULL(LinkedListWord * list);

void createHuffmanTree(LinkedListRoot * linkedListRoot, HuffmanRoot * root);
void createBranch(LinkedListRoot * listWord, HuffmanRoot * root);
void initHuffmanTree(LinkedListRoot * linkedListRoot, HuffmanRoot * root);

int main() {

    char testWord[MAX_WORD_LENGTH] = "bcaadddccacacac";

    // Creation table des frequence

    LinkedListRoot * linkedListRoot = createRoot();
    findLetterFrequency(linkedListRoot->start, testWord);
    sortLinkedListWord(linkedListRoot->start);

    // Creation arbre de huffman
    HuffmanRoot * Huffmanroot = createHuffmanRoot();
    createHuffmanTree(linkedListRoot, Huffmanroot);

    /*String buffer;
    FILE *readFilePtr;
    int fileSize;
    char* fileBytes = NULL;
    printf("Hauffman encoder !\n");
    printf("Enter file name: ");
    readInputString(buffer);
    while(access(buffer, F_OK) != 0)
    {
        printf("\n File entered was not valid, try another :");
        readInputString(buffer);
    };

    if (fopen(buffer,"rb") != -1) {
        //setvbuf(stdout, NULL, _IONBF, 0);
        printf("Yo");
        FILE* readFilePtr= fopen(buffer,"rb");
        LinkedListRoot * start = createRoot();
        fseek(readFilePtr, 0L, SEEK_END); 
        const long int res = ftell(readFilePtr); 
        fileBytes =(char*)malloc(res * sizeof( char));
        fseek(readFilePtr, 0L, SEEK_SET);
        fread(fileBytes,res,1,readFilePtr); 


        findLetterFrequency(start->start, fileBytes);
        sortLinkedListWord(start->start);
        *//*fseek(readFilePtr, 0L, SEEK_END);
        fileBytes =(char*)malloc(res * sizeof( char));
        fseek(readFilePtr, 0L, SEEK_SET);
        fread(fileBytes,res,1,readFilePtr); 
        frequencyFunction(res,fileBytes, &bufferMap);*//*
        //Next code goes hire
        printf("\n");

    }else{
        printf("Error");
        return 1;
    }*/

    return 0;

}