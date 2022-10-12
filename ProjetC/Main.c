#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PATH 500
typedef char String[MAX_PATH];
typedef enum { FALSE = 0, TRUE = 1 } Booleen;
Booleen DebugOn = FALSE;

void ReadInputString(String word){
    scanf("%s", word);
    if (DebugOn) printf(">>echo %s\n", word);
}
int main() {
    String buffer;
    printf("Hauffman encoder !\n");
    printf("Enter file name: ");
    ReadInputString(buffer);
    printf("Value entered : %s", buffer);
    return 0;
}
