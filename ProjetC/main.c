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

typedef struct {
	char key;
    int frequency; 

}HashMap[5];

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

int isNULL(LinkedListWord * list) {
    return list == NULL ? 1 : 0;
}

void initHuffmanTree(LinkedListRoot * linkedListRoot, HuffmanRoot * root) {
    root->Root = createHuffmanLeaf(' ',0);

    LinkedListWord * listWord = linkedListRoot->start;

    if(isNULL(linkedListRoot->start) || isNULL(linkedListRoot->start->next))
        return;

    HuffmanLeaf * leafLeft = NULL;
    HuffmanLeaf * leafRight = NULL;

    if(listWord->frequency < listWord->next->frequency) {
        leafLeft = createHuffmanLeaf(listWord->letter, listWord->frequency);
        leafRight = createHuffmanLeaf(listWord->next->letter, listWord->next->frequency);
    } else {
        leafLeft = createHuffmanLeaf(listWord->next->letter, listWord->next->frequency);
        leafRight = createHuffmanLeaf(listWord->letter, listWord->frequency);
    }
    addLeaves(root->Root, leafLeft, leafRight);
    linkedListRoot->start = linkedListRoot->start->next->next;
    addStack(linkedListRoot->start, root->Root->Frequency);
}

void createHuffmanTree(LinkedListRoot * linkedListRoot, HuffmanRoot * root) {
    if(root->Root == NULL){
        initHuffmanTree(linkedListRoot,root);
    }
    while(linkedListRoot->start != NULL ) {
        createBranch(linkedListRoot, root);
    }
}

void createBranch(LinkedListRoot * listWordRoot, HuffmanRoot * root) {
    LinkedListWord * listWord = listWordRoot->start;
    if(isNULL(listWord) || isNULL(listWord->next)) {
        listWord == NULL;
    }
    int nextLetterFrequency = listWord->letter == NULL ? listWord->next->frequency : listWord->frequency;
    char nextLetter = listWord->letter == NULL ? listWord->next->letter : listWord->letter;
    HuffmanLeaf * newParent = createHuffmanLeaf(' ', 0);
    if(nextLetterFrequency < root->Root->Frequency) {
        HuffmanLeaf * left = createHuffmanLeaf(nextLetter, nextLetterFrequency);
        HuffmanLeaf * right = root->Root;
        addLeaves(newParent,left,right);
    } else {
        HuffmanLeaf * left = root->Root;
        HuffmanLeaf * right = createHuffmanLeaf(nextLetter, nextLetterFrequency);
        addLeaves(newParent,left,right);
    }
    root->Root = newParent;
    if(listWord->letter == NULL && isNULL(listWord->next->next->next))
        listWordRoot->start = listWordRoot->start->next->next->next;
    listWordRoot->start = listWordRoot->start->next->next;
    if(listWordRoot->start == NULL)
        return;
    addStack(listWordRoot->start,root->Root->Frequency);
    sortLinkedListWord(listWordRoot->start);
}
}
