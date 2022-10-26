#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include "Word/word.h"
// code style:
// Variable and function as camelCase:
// ex : firstName lastName hello thisIsQuiteGood
// Struct as PascalCase :
// ex: FirstName LastName Hello ThisIsQuiteGood

#define MAX_PATH 300
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



int main() {
    String buffer;
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
        printf("YO");
        Start * start = createStaticStart();
        fseek(readFilePtr, 0L, SEEK_END); 
        const long int res = ftell(readFilePtr); 
        fileBytes =(char*)malloc(res * sizeof( char));
        fseek(readFilePtr, 0L, SEEK_SET);
        fread(fileBytes,res,1,readFilePtr); 
        printf("\n");

    }else{
        printf("Error");
        return 1;
    }

    return 0;

}
