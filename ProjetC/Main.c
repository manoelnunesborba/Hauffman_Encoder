#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define MAX_PATH 300
typedef char String[MAX_PATH];
typedef enum { FALSE = 0, TRUE = 1 } Booleen;
Booleen DebugOn = FALSE;

typedef struct {
	char Key;
    double frequency; 
    int nbOfAppear; 

}HashMap[5];

void ReadInputString(String word){
    scanf("%s", word);
    if (DebugOn) printf(">>echo %s\n", word);
}
Booleen HashMapHasValue(int size, char value, HashMap* output){
    for(int i =0; i<size; i++){
        if(output[i]->Key == value)
            return TRUE;
        if(DebugOn)    printf("With. %u \n",output[i]->Key);

    }
    return FALSE;
}
void FrequencyFunction(int size, char* bytes, HashMap* output){
    output =  (HashMap*)malloc(size * sizeof(HashMap));
    for(int i = 0; i<size; i++){
        if(DebugOn)    printf("testing value... %u \n",bytes[i]);
        
        if(!HashMapHasValue(size, bytes[i], output)){
            output[i]->Key=bytes[i];
        }
            output[i]->nbOfAppear = output[i]->nbOfAppear+1;
            output[i]->frequency = output[i]->nbOfAppear / size;


        
    }
    for(int i = 0; i<size; i++){
        if(output[i]->Key != 0){
        printf("For key %u, nbObAppear %d, frequency : %f \n", output[i]->Key,output[i]->nbOfAppear, output[i]->frequency );

        }
    }
    
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
    while(access(buffer, F_OK) != 0)
    {
        printf("\n File entered was not valid, try another :");
        ReadInputString(buffer);
    };
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
