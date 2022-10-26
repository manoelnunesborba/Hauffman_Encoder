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



void readInputString(String word){
    scanf("%s", word);
    if (debugOn) printf(">>echo %s\n", word);
}

void displayDocumentation();
char * displayInterface();
void commandReader(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    return 0;
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

