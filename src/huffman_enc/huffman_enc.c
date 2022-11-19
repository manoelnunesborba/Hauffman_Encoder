/**
* Fonction de compression et decrompression
*
* @author  Nunes Borba Manoel / Quitman Lucas / Mozet Jacques-Arno
* @version 1.0
* @since   2022-09-11
*/
#include <errno.h>
#include <stdlib.h>

#include "./huffman_enc.h"

unsigned char getUniqueChars(FrequencyListRoot list) {
   unsigned char uniqueCharsAmmount = 1;
    FrequencyListNode *currentNode = list.Start;
    while (currentNode->Next != NULL) {
        uniqueCharsAmmount++;
        currentNode = currentNode->Next;
    }
    return uniqueCharsAmmount;
}


void assignSymbolsDepth(HuffmanLeaf *node, CanonicalList list[]) {
    unsigned char currentDepth = 0;
    for (int i=0; i < EXT_ASCII; i++){
        list[i].Code = 0;
        list[i].Depth = 0;
        list[i].Symbol = i;
    }
    for(;;) {
        while (node->Right != NULL)
        {   
            node = node->Right;
            currentDepth++;
        }
        list[node->Letter].Depth = currentDepth;
        while (node->Parent != NULL) {
            if (node->Parent->Left != node) {
                node = node->Parent->Left;
                break;
            } else {
                node = node->Parent;
                currentDepth--;
            }
        } 
        if (node->Parent == NULL) {
            break;
        }
    }
}

static int canonicalSort(const void *firstItem, const void *secondItem) {
    if (((CanonicalList *)firstItem)->Depth > ((CanonicalList*)secondItem)->Depth){
        return 1;
    } else if (((CanonicalList *)firstItem)->Depth < (((CanonicalList*)secondItem))->Depth) {
        return -1;
    } else {
        if (((CanonicalList *)firstItem)->Symbol > (((CanonicalList*)secondItem))->Symbol) {
            return 1;
        } else {
            return -1;
        }
    }
    return 0;
}
static int sortBySymbol(const void *firstItem, const void *secondItem) {
    if (((CanonicalList *)firstItem)->Symbol > (((CanonicalList*)secondItem))->Symbol){
        return 1;
    }
    return -1;
}


void assignCodes(CanonicalList *list, int uniqueChars, int size) {
    qsort(list, size, sizeof(CanonicalList), canonicalSort);
    int depth = list->Depth;
    unsigned long long code = 0;
    int firstOccurence = 0;
    for (int i = size-uniqueChars; i < size; i++) {
        if (list[i].Depth == 0) {
            break;
        }
        if (!firstOccurence) {
            list[i].Code = code;
            firstOccurence = 1;
            depth = list[i].Depth;
            continue;
        }
        code ++;
        if (list[i].Depth > depth) {
            code = code << 1;
            depth = list[i].Depth;
        }
        list[i].Code = code;
    }
}
int writeHeader(CanonicalList *list, unsigned char uniqueChars, unsigned long characterAmmounts, FILE *outputStream) {
    if (NULL == outputStream) {
        errno = ENOENT;
        return -1;
    }
    fwrite(&characterAmmounts, sizeof(unsigned long), 1, outputStream);
    fputc(uniqueChars, outputStream);
    for(int i = EXT_ASCII - uniqueChars; i < EXT_ASCII; i++) {
        fputc(list[i].Depth, outputStream);
    }
    for(int i = EXT_ASCII - uniqueChars; i < EXT_ASCII; i++) {
        fputc(list[i].Symbol, outputStream);
    }
    return 0;
}

CanonicalList* readHeader(FILE *inputStream, unsigned char *uniqueChars, unsigned long *characterAmmount) {
    if (NULL == inputStream) {
        errno = ENOENT;
        exit(1);
    }
    fread(characterAmmount, sizeof(unsigned long), 1, inputStream);
    *uniqueChars = fgetc(inputStream);
    CanonicalList *canonicalList = (CanonicalList*)malloc( *uniqueChars * sizeof(CanonicalList));
    for (int i = 0; i < *uniqueChars; i++) {
        canonicalList[i].Depth = fgetc(inputStream);
    }
    for (int i = 0; i < *uniqueChars; i++) {
        canonicalList[i].Symbol = fgetc(inputStream);
    }
    return canonicalList;
}

int encode(CanonicalList *list, FILE *inputStream, FILE *outputStream) {

    if ((NULL == inputStream) || (NULL == outputStream)) {
        errno = ENOENT;
        return -1;
    }
    qsort(list, EXT_ASCII, sizeof(CanonicalList), sortBySymbol);
    int character, bitCount = 0;
    unsigned char leftover = 0;
    unsigned char buffer = 0;
    rewind(inputStream);
    while ((character =  fgetc(inputStream)) != EOF ) {
        int depth = list[character].Depth;
        BigInt code = list[character].Code;
        for(int bit = depth - 1; bit >= 0; bit--){
            if (bitCount == 8) {
                fputc(buffer, outputStream);
                buffer = 0;
                bitCount = 0;
            }
            buffer = buffer << 1;
            if((code >> bit) & 1) {
                buffer++;
            }
            bitCount++;
        }
    }
    if (bitCount != 0) {
        leftover = 8 - bitCount;
        buffer = buffer << leftover;
        fputc(buffer, outputStream);
    }
    return 0;
}

int decode(CanonicalList *list, unsigned long characterAmmount, int uniqueChars, FILE *inputStream, FILE *outputStream){
    if ((NULL == inputStream) || (NULL == outputStream)) {
        errno = ENOENT;
        return -1;
    }
    qsort(list, uniqueChars, sizeof(CanonicalList), canonicalSort);
    int searchIndex[uniqueChars];
    for (int i = 0; i < uniqueChars; i++) {
        searchIndex[i] = uniqueChars;
    }
    for (int i = 0; i < uniqueChars; i++) {
        if (searchIndex[list[i].Depth] > i ) {
            searchIndex[list[i].Depth] = i;
        }
    }
    unsigned char buffer;
    unsigned long code = 0;
    int length = 0;
    int flushBuffer = 1;
    int startingBit;
    for (unsigned long i = 0; i < characterAmmount; i++) {
        int nextChar = 0;
        while (!nextChar) {
            if (flushBuffer) {
                buffer = fgetc(inputStream);
                startingBit = 7;
            }
            for(int bit = startingBit; bit >= 0; bit--){
                code = code << 1;
                length++;
                if((buffer >> bit) & 1) {
                    code++;
                }
                int offset = 0;
                int currentIndex;
                for(;;){
                    currentIndex = searchIndex[length] + offset;
                    if (list[currentIndex].Depth > length || currentIndex  == uniqueChars) {
                        break;
                    }
                    if (code == list[currentIndex].Code) {
                        fputc(list[currentIndex].Symbol, outputStream);
                        length = 0;
                        code = 0;
                        nextChar = 1;
                        if (bit != 0) {
                            flushBuffer = 0;
                            startingBit = bit - 1;
                        }
                        break;
                    }
                    offset++;
                }
                if (bit == 0) {
                    flushBuffer = 1;
                }
                if (nextChar) {
                    break;
                }
            }
        }
    }
    return 0;
}