/**
* Module de creation de l'arbre de huffman
*
* @author  Nunes Borba Manoel / Quitman Lucas / Mozet Jacques-Arno
* @version 1.0
* @since   2022-09-11
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Word/word.h"
#include "Tree/huffman.h"
#include "Hufenc/hufenc.h"
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


int isNULL(LinkedListWord * list);

void createHuffmanTree(LinkedListRoot * linkedListRoot, HuffmanRoot * root);
void createBranch(LinkedListRoot * listWord, HuffmanRoot * root);
void initHuffmanTree(LinkedListRoot * linkedListRoot, HuffmanRoot * root);
void createParalleTree(HuffmanRoot * huffmanRoot, LinkedListRoot * linkedListRoot);
void initializeHuffmanTree(HuffmanRoot * huffmanRoot, LinkedListRoot * linkedListRoot);
void displayDocumentation();
char * displayInterface();
void commandReader(int argc, char *argv[]);
unsigned long getCharAmmount(FILE *inputFile);
void openFile(String path, FILE ** file);
void closeFile(FILE ** file);
void readFile(FILE * file, LinkedListRoot * linkedListRoot);



int main(int argc, char *argv[]) {
    commandReader(argc, argv);
    return 0;
}

void openFile(String path, FILE ** file) {
    *file = fopen(path, "rb");
    if (*file == NULL) {
        printf("Error opening file %s", path);
        exit(1);
    }
    printf("File %s opened successfully", path);
}

void closeFile(FILE ** file) {
    fclose(*file);
}

unsigned long getCharAmmount(FILE *inputFile) {
    fseek(inputFile, 0L, SEEK_END );
    unsigned long bytesAmmount = ftell(inputFile);
    rewind(inputFile);
    return bytesAmmount;
}

void readFile(FILE * file, LinkedListRoot * linkedListRoot) {
    char * c = malloc(sizeof(char));
    while((c = fgetc(file)) != EOF) {
        findLetterFrequency(linkedListRoot->start, &c);
    }
    sortLinkedListWord(linkedListRoot->start);
}
void staticCompression(char * var_input, char * var_output){
/*Juste ici, il faut changer car ca depend dans quel repertoire ton IDE torne*/
    LinkedListRoot * linkedListRoot = ReadFileAndGenerateStruct("./StaticTrees/alphabetfrancais.txt"); //Fast encoding uses static tree
    sortLinkedListWord(linkedListRoot->start);
    linkedListRoot->start = linkedListRoot->start->next;
    FILE *readFilePtr;
    char * input = var_input;
    char * output = var_output;
    openFile(input, &readFilePtr);
    unsigned long characterAmmount = getCharAmmount(readFilePtr);
    char uniqueChars = getUniqueChars(*linkedListRoot);
    HuffmanRoot * Huffmanroot = createHuffmanRoot();
    createHuffmanTree(linkedListRoot, Huffmanroot);
    CanonicalList canonicalList[EXT_ASCII];
    getSymbolsDepth(Huffmanroot->Root, canonicalList);
    assignCodes(canonicalList, uniqueChars, EXT_ASCII);
    FILE *outputFile;
    if ((outputFile = fopen(output, "wb")) == NULL) {
        perror("couldn't open output file");
        exit(EXIT_FAILURE);
    }
    writeHeader(canonicalList, uniqueChars,characterAmmount, outputFile);
    encode(canonicalList,readFilePtr, outputFile);
    fclose(readFilePtr);
}
void dynammicCompression(char * var_input, char * var_output){
    LinkedListRoot *  linkedListRoot =  createDynammicRoot();
    FILE *readFilePtr;
    char * input = var_input;
    char * output = var_output;
    openFile(input, &readFilePtr);
    readFile(readFilePtr, linkedListRoot);
    unsigned long characterAmmount = getCharAmmount(readFilePtr);
    sortLinkedListWord(linkedListRoot->start);
    char uniqueChars = getUniqueChars(*linkedListRoot);
    HuffmanRoot * Huffmanroot = createHuffmanRoot();
    createHuffmanTree(linkedListRoot, Huffmanroot);
    CanonicalList canonicalList[EXT_ASCII];
    getSymbolsDepth(Huffmanroot->Root, canonicalList);
    assignCodes(canonicalList, uniqueChars, EXT_ASCII);
    FILE *outputFile;
    if ((outputFile = fopen(output, "wb")) == NULL) {
        perror("couldn't open output file");
        exit(EXIT_FAILURE);
    }
    writeHeader(canonicalList, uniqueChars,characterAmmount, outputFile);
    encode(canonicalList,readFilePtr, outputFile);
    fclose(readFilePtr);
}
void decompress(char * var_input, char * var_output){
    char * inputPath = var_input;
    char * outputPath = var_output;
    FILE *input;
    FILE *output;
    openFile(inputPath, &input);
    if ((output = fopen(outputPath, "wb")) == NULL) {
        perror("couldn't open output file");
        exit(EXIT_FAILURE);
    }
    unsigned char uniqueChars;
    unsigned long characterAmmount;
    CanonicalList *CanonicalList = readHeader(input, &uniqueChars, &characterAmmount);
    assignCodes(CanonicalList, uniqueChars, uniqueChars);
    decode(CanonicalList, characterAmmount, uniqueChars, input, output);
}
void commandReader(int argc, char *argv[]) {
    HuffmanRoot * Huffmanroot = createHuffmanRoot();
    if(argc == 1){
        displayDocumentation();
        return;
    }else if(argc > 1 && argc <= 3) {
        if(strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "--interactive") == 0){
            printf("Interactive mode\n");
            displayInterface();
        }else{
            fprintf(stderr, "Error : not enough arguments\n");
        }
    } else if(argc > 4) {
        fprintf(stderr, "Error : too much arguments\n");
    } else {
        if(strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "--fast") == 0){
            staticCompression(argv[2],argv[3]);

        } else if(strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "--slow") == 0){
            dynammicCompression(argv[2],argv[3]);
        } else if(strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--decompress") == 0){
            decompress(argv[2],argv[3]);
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
            printf("Fast compression \nPlease enter the name of the file you want to compress : ");
            char * fileNameFast = (char*)malloc(sizeof(char)*MAX_WORD_LENGTH);
            scanf("%s", fileNameFast);
            printf("Please enter the name of the output file : ");
            char * outputFileNameFast = (char*)malloc(sizeof(char)*MAX_WORD_LENGTH);
            scanf("%s", outputFileNameFast);
            staticCompression(fileNameFast, outputFileNameFast);
            break;
        case 2:
            printf("Slow compression \nPlease enter the name of the file you want to compress : ");
            char * fileNameSlow = (char*)malloc(sizeof(char)*MAX_WORD_LENGTH);
            scanf("%s", fileNameSlow);
            printf("Please enter the name of the output file : ");
            char * outputFileNameSlow = (char*)malloc(sizeof(char)*MAX_WORD_LENGTH);
            scanf("%s", outputFileNameSlow);
            dynammicCompression(fileNameSlow, outputFileNameSlow);
            break;
        case 3:
            printf("Decompress a file \n"
                   "Please enter the name of the file you want to decompress : ");
            char * fileNameCompression = (char*)malloc(sizeof(char)*MAX_WORD_LENGTH);
            scanf("%s", fileNameCompression);
            printf("Please enter the name of the output file : ");
            char * outputFileNameCompression = (char*)malloc(sizeof(char)*MAX_WORD_LENGTH);
            scanf("%s", outputFileNameCompression);
            decompress(fileNameCompression, outputFileNameCompression);
            break;
        case 4:
            printf("Exit \n");
            break;
        default:
            printf("Error : invalid choice \n");
            break;
    }
}

int isNULL(LinkedListWord * list) {
    return list == NULL ? 1 : 0;
}

void createHuffmanTree(LinkedListRoot * linkedListRoot, HuffmanRoot * huffmanRoot) {
    if(huffmanRoot->Root == NULL){
        initializeHuffmanTree(huffmanRoot,linkedListRoot);
    }
    while(linkedListRoot->start != NULL ) {
        if(linkedListRoot->start->frequency <= huffmanRoot->Root->Frequency) {
            if(isNULL(linkedListRoot->start->next))
                createBranch(linkedListRoot, huffmanRoot);
            else
                createParalleTree(huffmanRoot, linkedListRoot);
        } else {
            createBranch(linkedListRoot, huffmanRoot);
        }
    }
}

void initializeHuffmanTree(HuffmanRoot * huffmanRoot, LinkedListRoot * linkedListRoot) {
    huffmanRoot->Root = createHuffmanLeaf(' ',0);

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
    addLeaves(huffmanRoot->Root, leafLeft, leafRight);
    linkedListRoot->start = linkedListRoot->start->next->next;
}

void createParalleTree(HuffmanRoot * huffmanRoot, LinkedListRoot * linkedListRoot) {
    HuffmanRoot * ParallelTree = createHuffmanRoot();
    initializeHuffmanTree(ParallelTree, linkedListRoot);
    while(linkedListRoot->start != NULL) {
        if(ParallelTree->Root->Frequency > huffmanRoot->Root->Frequency) {
            break;
        }
        createBranch(linkedListRoot, ParallelTree);
    }
    HuffmanLeaf * jointureLeaf = createHuffmanLeaf(' ',0);
    addLeaves(jointureLeaf,ParallelTree->Root,huffmanRoot->Root);
    huffmanRoot->Root = jointureLeaf;
}

void createBranch(LinkedListRoot * listWordRoot, HuffmanRoot * root) {
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
    if(isNULL(listWordRoot->start->next) || isNULL(listWordRoot->start)) {
        listWordRoot->start = NULL;
        return;
    }
    listWordRoot->start = listWordRoot->start->next;
}
