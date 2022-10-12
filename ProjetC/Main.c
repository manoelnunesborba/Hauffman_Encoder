#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define MAX_PATH 300
typedef char String[MAX_PATH];
typedef enum { FALSE = 0, TRUE = 1 } Booleen;
Booleen DebugOn = FALSE;

typedef struct {
	unsigned short int Key;
    double frequency; 

}HashMap;

void ReadInputString(String word){
    scanf("%s", word);
    if (DebugOn) printf(">>echo %s\n", word);
}

void FrequencyFunction(int size, char* bytes, HashMap* output){
for(int i = 0; i<size; i++)
    printf("%u ", bytes[i]); // prints a series of bytes
}
int main() {
    String buffer;
    FILE *readFile_ptr;
    int FileSize;
    char* FileBytes = NULL;
    HashMap bufferMap;
    printf("Hauffman encoder !\n");
    printf("Enter file name: ");
    ReadInputString(buffer);
    printf("Value entered : %s", buffer);
    while(access(buffer, F_OK) != 0)
    {
        printf("\n File entered was not valid, try another :");
        ReadInputString(buffer);
    };
    printf("\nValue entered was valid");
    if (fopen(buffer,"rb") != NULL) {
        FILE* readFile_ptr= fopen(buffer,"rb");
        fseek(readFile_ptr, 0L, SEEK_END); 
        const long int res = ftell(readFile_ptr); 
        FileBytes =(char*)malloc(res * sizeof( char));
        fseek(readFile_ptr, 0L, SEEK_SET);
        fread(FileBytes,res,1,readFile_ptr); 
        FrequencyFunction(res,FileBytes, &bufferMap);
        printf("\n");

    }else{
        printf("Error");
        return 0;
    }

    return 0;

}
