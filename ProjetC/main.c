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
#define LINE_LENGTH 100
#define ABSOLUT_PATH "C:\\Users\\jacqu\\OneDrive\\Bureau\\ESIEA\\S1\\PASS INFO\\Hauffman_Encoder\\ProjetC\\hard_test.txt"

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

void displayDocumentation();
char * displayInterface();
void commandReader(int argc, char *argv[]);

void openFile(String path, FILE ** file);
void closeFile(FILE ** file);
void readFile(FILE * file, LinkedListRoot * linkedListRoot);

int main(int argc, char *argv[]) {

    char testWord[MAX_WORD_LENGTH] = "bcaadddccacacac efdmedfmspfd";
    char testWord2[MAX_WORD_LENGTH] = "AAABBBCCCO POKPOKPOKAAADADADDDDD \n AAABBBCCCO POKPOKPOKAAADADADDDDD";

    // Creation table des frequence

    LinkedListRoot * linkedListRoot = createRoot();
    /*findLetterFrequency(linkedListRoot->start, testWord2);
    sortLinkedListWord(linkedListRoot->start);*/
    FILE *readFilePtr;
    String path = ABSOLUT_PATH;
    openFile(path, &readFilePtr);
    readFile(readFilePtr, linkedListRoot);
    closeFile(&readFilePtr);
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

void openFile(String path, FILE ** file) {
    *file = fopen(path, "r");
    if (*file == NULL) {
        printf("Error opening file %s", path);
        exit(1);
    }
}

void closeFile(FILE ** file) {
    fclose(*file);
}

void readFile(FILE * file, LinkedListRoot * linkedListRoot) {
    char * c = malloc(sizeof(char));
    while((c = fgetc(file)) != EOF) {
        findLetterFrequency(linkedListRoot->start, &c);
    }
    sortLinkedListWord(linkedListRoot->start);
}

void commandReader(int argc, char *argv[]) {
    if(argc == 1){
        displayDocumentation();
        return;
    }else if(argc > 1 && argc <= 3) {
        fprintf(stderr, "Error : not enough arguments\n");
    } else if(argc > 4) {
        fprintf(stderr, "Error : too much arguments\n");
    } else {
        if(strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "--fast") == 0){
            printf("Compression rapide du fichier %s vers %s\n", argv[2], argv[3]);
        } else if(strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "--slow") == 0){
            printf("Compression lente du fichier %s vers %s\n", argv[2], argv[3]);
        } else if(strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--decompress") == 0){
            printf("Décompression du fichier %s vers %s\n", argv[2], argv[3]);
        } else if(strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "--interactive") == 0){
            printf("Interface en mode interactif\n");
            displayInterface();
        }
    }
}

void displayDocumentation(){
    printf("NAME \n"
           "\thcode - huffman encoder & decoder \n"
           "SYNOPSIS \n"
           "\thcode [OPTION] [INPUT_FILE] [OUTPUT_FILE] \n"
           "DESCRIPTION \n"
           "\tCompress and decompress a file using huffman algorithm \n"
           "\tIF no argument is given, help will be returned \n"
           "\t-f, -fast \n"
           "\t\tCompress using a static tree, less compress but faster.If no output is given, file will contain same name \n"
           "\t-s, -slow \n"
           "\t\tCompress using a dynammic tree, more compress but slower. If no output is given, file will contain same name \n"
           "\t-d, -decompress \n"
           "\t\tDecompress a given file, if no output is given, file will contain same name \n"
           "\t-i, -interactive \n"
           "\t\tAllow same thing as others, but in an interactive way \n"
           "\tExit status: \n"
           "\t0 if okay \n"
           "\t1 if an error occur \n"
           "AUTHOR \n"
           "\tJacques-Arno MOZET \n"
           "\tManoel NUNES BORBA \n"
           "\tLucas QUITMAN ");
}

char * displayInterface(){
    printf("---------------------------------------------\n"
           "Welcome to hcode, the huffman encoder & decoder ! \n"
           "Please choose an option : \n"
           "1 - Fast compression \n"
           "2 - Slow compression \n"
           "3 - Decompress a file \n"
           "4 - Exit \n"
           "Your choice : ");
    int choice;
    scanf("%d", &choice);
    switch(choice){
        case 1:
            printf("Fast compression \n"
                   "Please enter the name of the file you want to compress : ");
            char * fileNameFast = (char*)malloc(sizeof(char)*MAX_WORD_LENGTH);
            scanf("%s", fileNameFast);
            printf("Please enter the name of the output file : ");
            char * outputFileNameFast = (char*)malloc(sizeof(char)*MAX_WORD_LENGTH);
            scanf("%s", outputFileNameFast);
            break;
        case 2:
            printf("Slow compression \n"
                   "Please enter the name of the file you want to compress : ");
            char * fileNameSlow = (char*)malloc(sizeof(char)*MAX_WORD_LENGTH);
            scanf("%s", fileNameSlow);
            printf("Please enter the name of the output file : ");
            char * outputFileNameSlow = (char*)malloc(sizeof(char)*MAX_WORD_LENGTH);
            scanf("%s", outputFileNameSlow);
            break;
        case 3:
            printf("Decompress a file \n"
                   "Please enter the name of the file you want to compress : ");
            char * fileNameCompression = (char*)malloc(sizeof(char)*MAX_WORD_LENGTH);
            scanf("%s", fileNameCompression);
            printf("Please enter the name of the output file : ");
            char * outputFileNameCompression = (char*)malloc(sizeof(char)*MAX_WORD_LENGTH);
            scanf("%s", outputFileNameCompression);
            printf("Please enter the name of the file containing the tree : ");
            break;
        case 4:
            printf("Exit \n");
            break;
        default:
            printf("Error : invalid choice \n");
            break;
    }
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

    if(listWord->frequency <= listWord->next->frequency) {
        leafLeft = createHuffmanLeaf(listWord->letter, listWord->frequency);
        leafRight = createHuffmanLeaf(listWord->next->letter, listWord->next->frequency);
    } else {
        leafLeft = createHuffmanLeaf(listWord->next->letter, listWord->next->frequency);
        leafRight = createHuffmanLeaf(listWord->letter, listWord->frequency);
    }
    addLeaves(root->Root, leafLeft, leafRight);
    linkedListRoot->start = linkedListRoot->start->next->next;
    /*addStack(linkedListRoot->start, root->Root->Frequency);*/
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
    /*if(isNULL(listWordRoot->start) || isNULL(listWordRoot->start->next)) {
        listWordRoot == NULL;
    }*/
    int nextLetterFrequency = listWordRoot->start->letter == NULL ? listWordRoot->start->next->frequency : listWordRoot->start->frequency;
    char nextLetter = listWordRoot->start->letter == NULL ? listWordRoot->start->next->letter : listWordRoot->start->letter;
    HuffmanLeaf * newParent = createHuffmanLeaf(' ', 0);
    if(nextLetterFrequency <= root->Root->Frequency) {
        HuffmanLeaf * left = createHuffmanLeaf(nextLetter, nextLetterFrequency);
        HuffmanLeaf * right = root->Root;
        addLeaves(newParent,left,right);
    } else {
        HuffmanLeaf * left = root->Root;
        HuffmanLeaf * right = createHuffmanLeaf(nextLetter, nextLetterFrequency);
        addLeaves(newParent,left,right);
    }
    root->Root = newParent;
    /*if(isNULL(listWordRoot->letter) && isNULL(listWordRoot->next->next->next))
        listWordRoot->start = listWordRoot->start->next->next->next;*/
    if(isNULL(listWordRoot->start->next) || isNULL(listWordRoot->start)) {
        listWordRoot->start = NULL;
        return;
    }
    listWordRoot->start = listWordRoot->start->next;
    /*if(listWordRoot->start == NULL)
        return;*/
    /*addStack(listWordRoot->start,root->Root->Frequency);
    sortLinkedListWord(listWordRoot->start);*/
}
