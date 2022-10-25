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