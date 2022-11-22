/**
* @author  Nunes Borba Manoel / Quitman Lucas / Mozet Jacques-Arno
* @version 1.0
* @since   2022-09-11
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "frequency/frequency.h"
#include "huffman_tree/huffman_tree.h"
#include "huffman_enc/huffman_enc.h"

#define MAX_PATH 300
#define FRENCH_DICT "./dicts/french-dict.txt"
typedef char FilePath[MAX_PATH];

void displayHelp();
char * displayInterface();
void commandReader(int argc, char *argv[]);
unsigned long getCharAmmount(FILE *fileStream);
void readFile(FILE * fileStream, FrequencyListRoot * frequencyList);



int main(int argc, char *argv[]) {
    commandReader(argc, argv);
    return 0;
}

unsigned long getCharAmmount(FILE *fileStream) {
    fseek(fileStream, 0L, SEEK_END );
    unsigned long bytesAmmount = ftell(fileStream);
    rewind(fileStream);
    return bytesAmmount;
}

void readFile(FILE *fileStream, FrequencyListRoot *frequencyList) {
    char *symbol;
    while((symbol = fgetc(fileStream)) != EOF) {
        findSymbolFrequency(frequencyList->Start, &symbol);
    }
    sortFrequencyList(frequencyList->Start);
}

void staticCompression(char *inputFilePath, char *outputFilePath){
    FrequencyListRoot * frequencyList = generateStaticList(FRENCH_DICT);
    sortFrequencyList(frequencyList->Start);
    frequencyList->Start = frequencyList->Start->Next;
    FILE *inputFileStream;
    FILE *outputFileStream;
    char * input = inputFilePath;
    char * output = outputFilePath;
    if ((inputFileStream = fopen(inputFilePath, "rb")) == NULL) {
        errno=ENOENT;
        exit(EXIT_FAILURE);
    }
    if ((outputFileStream = fopen(outputFilePath, "wb")) == NULL) {
        errno=ENOENT;
        exit(EXIT_FAILURE);
    }
    unsigned long characterAmmount = getCharAmmount(inputFileStream);
    char uniqueChars = getUniqueChars(*frequencyList);
    HuffmanRoot * Huffmanroot = createHuffmanRoot();
    createHuffmanTree(frequencyList, Huffmanroot);
    CanonicalList canonicalList[EXT_ASCII];
    assignSymbolsDepth(Huffmanroot->Root, canonicalList);
    assignCodes(canonicalList, uniqueChars, EXT_ASCII);

    if (writeHeader(canonicalList, uniqueChars,characterAmmount, outputFileStream) != 0) {
        fprintf(stderr, "\nstaticCompression: couldn't write the header to the output file.");
        exit(1);
    }
    ;
    if (encode(canonicalList,inputFileStream, outputFileStream) != 0) {
        fprintf(stderr, "\ncompression: couldn't encode source.");
        exit(1);
    }
    fclose(inputFileStream);
    fclose(outputFileStream);
}

void compress(char *inputFilePath, char *outputFilePath){
    FrequencyListRoot *frequencyList =  createFrequencyList();
    FILE *inputFileStream;
    // char *fp = inputFilePath;
    // openFile(fp, &inputFileStream);
    if ((inputFileStream = fopen(inputFilePath, "rb")) == NULL) {
        errno=ENOENT;
        exit(EXIT_FAILURE);
    }
    unsigned long characterAmmount = getCharAmmount(inputFileStream);
    readFile(inputFileStream, frequencyList);
    // unsigned long characterAmmount = getCharAmmount(inputFileStream);
    if (sortFrequencyList(frequencyList->Start) != 0) {
        fprintf(stderr, "\ncompression: couldn't sort frequency list");
        exit(1);
    }
    char uniqueChars = getUniqueChars(*frequencyList);
    HuffmanRoot *Huffmanroot = createHuffmanRoot();
    createHuffmanTree(frequencyList, Huffmanroot);
    CanonicalList canonicalList[EXT_ASCII];
    assignSymbolsDepth(Huffmanroot->Root, canonicalList);
    assignCodes(canonicalList, uniqueChars, EXT_ASCII);
    FILE *outputFileStream;
    if ((outputFileStream = fopen(outputFilePath, "wb")) == NULL) {
        errno=ENOENT;
        exit(EXIT_FAILURE);
    }
    if (writeHeader(canonicalList, uniqueChars,characterAmmount, outputFileStream) != 0) {
        fprintf(stderr, "\ncompression: couldn't write the header to the output file.");
        exit(1);
    }
    if (encode(canonicalList,inputFileStream, outputFileStream) != 0) {
        fprintf(stderr, "\ncompression: couldn't encode source.");
        exit(1);
    }
    fclose(inputFileStream);
    fclose(outputFileStream);
}
void decompress(char *inputFilePath, char *outputFilePath){
    FILE *inputFileStream;
    FILE *outputFileStream;
    if ((inputFileStream = fopen(inputFilePath, "rb")) == NULL) {
        errno=ENOENT;
        exit(EXIT_FAILURE);
    }
    if ((outputFileStream = fopen(outputFilePath, "wb")) == NULL) {
        errno=ENOENT;
        exit(EXIT_FAILURE);
    }
    unsigned char uniqueChars;
    unsigned long characterAmmount;
    CanonicalList *CanonicalList = readHeader(inputFileStream, &uniqueChars, &characterAmmount);
    assignCodes(CanonicalList, uniqueChars, uniqueChars);
    if ( decode( CanonicalList, characterAmmount, uniqueChars, inputFileStream, outputFileStream) != 0) {
        fprintf(stderr, "\ndecompression: couldn't decode source.");
        exit(1);
    }
    fclose(inputFileStream);
    fclose(outputFileStream);
}

void commandReader(int argc, char *argv[]) {
    HuffmanRoot * Huffmanroot = createHuffmanRoot();
    if(argc == 1){
        displayHelp();
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
            compress(argv[2],argv[3]);
        } else if(strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--decompress") == 0){
            decompress(argv[2],argv[3]);
        }
    }
}

void displayHelp(){
    printf("NAME \n"
           "\thcode - huffman encoder & decoder \n"
           "SYNOPSIS \n"
           "\thcode [OPTION] INPUT_FILE OUTPUT_FILE\n"
           "DESCRIPTION \n"
           "\tCompress and decompress a file using huffman algorithm \n"
           "\t-f, -fast \n"
           "\t\tCompress a french text using a faster, less optimal algorithm\n"
           "\t-s, -slow \n"
           "\t\tCompress using a slower, more optimal compression algorithm\n"
           "\t-d, -decompress \n"
           "\t\tDecompress a given file \n"
           "\t-i, -interactive \n"
           "\t\tInteractive session \n"
           "\tExit codes: \n"
           "\t0 if okay \n"
           "\t1 if an error occurs \n"
           "AUTHOR \n"
           "\tJacques-Arno MOZET \n"
           "\tManoel NUNES BORBA \n"
           "\tLucas QUITMAN ");
}

char * displayInterface(){
    printf("---------------------------------------------\n"
           "Welcome to hcode, the huffman encoder & decoder ! \n");
    int choice;
    char * inputFilePath = (char*)malloc(sizeof(char)*MAX_PATH);
    char * outputFilePath = (char*)malloc(sizeof(char)*MAX_PATH);

    printf("\nPlease enter the path of the file you want to compress : ");
    scanf("%s", inputFilePath);
    fflush(stdin);
    printf("\nPlease enter the name of the output file : ");
    scanf("%s", outputFilePath);
    fflush(stdin);
    printf("Please choose an option : \n"
           "1 - Fast compression \n"
           "2 - Slow compression \n"
           "3 - Decompress a file \n"
           "4 - Exit \n"
           "\n>  ");
    scanf("%d", &choice);
    fflush(stdin);

    switch(choice){
        case 1:
            staticCompression(inputFilePath, outputFilePath);
            break;
        case 2:
            compress(inputFilePath, outputFilePath);
            break;
        case 3:
            decompress(inputFilePath, outputFilePath);
            break;
        case 4:
            printf("Exit \n");
            break;
        default:
            printf("Error : invalid choice \n");
            break;
    }
}

