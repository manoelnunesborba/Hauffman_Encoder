#include "../Tree/huffman.h"
#include "../Word/word.h"
#include "./hufenc.h"
#include <stdio.h>
#include <stdlib.h>

unsigned char getUniqueChars(LinkedListRoot list) {
   unsigned char uniqueCharsAmmount = 1;
    LinkedListWord *currentNode = list.start;
    while (currentNode->next != NULL) {
        uniqueCharsAmmount++;
        currentNode = currentNode->next;
    }
    return uniqueCharsAmmount;
}


int getSymbolsDepth(HuffmanLeaf *node, CanonicalList list[]) {
    unsigned char currentDepth = 0;
    for (int i=0; i < EXT_ASCII; i++){
        list[i].code = 0;
        list[i].depth = 0;
        list[i].symbol = i;
    }
    for(;;) {
        while (node->Right != NULL)
        {   
            node = node->Right;
            currentDepth++;
        }
        list[node->Letter].depth = currentDepth;
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
    return 0;
}

int canonicalSort(const void *firstItem, const void *secondItem) {
    if (((CanonicalList *)firstItem)->depth > ((CanonicalList*)secondItem)->depth){
        return 1;
    } else if (((CanonicalList *)firstItem)->depth < (((CanonicalList*)secondItem))->depth) {
        return -1;
    } else {
        if (((CanonicalList *)firstItem)->symbol > (((CanonicalList*)secondItem))->symbol) {
            return 1;
        } else {
            return -1;
        }
    }
    return 0;
}
int sortBySymbol(const void *firstItem, const void *secondItem) {
    if (((CanonicalList *)firstItem)->symbol > (((CanonicalList*)secondItem))->symbol){
        return 1;
    }
    return -1;
}


int assignCodes(CanonicalList *list, int uniqueChars, int size) {
    qsort(list, size, sizeof(CanonicalList), canonicalSort);
    int depth = list->depth;
    unsigned long long code = 0;
    int firstOccurence = 0;
    for (int i = size-uniqueChars; i < size; i++) {
        if (list[i].depth == 0) {
            break;
        }
        if (!firstOccurence) {
            list[i].code = code;
            firstOccurence = 1;
            continue;
        }
        code ++;
        if (list[i].depth > depth) {
            code = code << 1;
            depth = list[i].depth;
        }
        list[i].code = code;
    }
    return 0;
}
int writeHeader(CanonicalList *list, unsigned char uniqueChars, unsigned long characterAmmounts, FILE *output) {
    fwrite(&characterAmmounts, sizeof(unsigned long), 1, output);
    fputc(uniqueChars, output);
    for(int i = EXT_ASCII - uniqueChars; i < EXT_ASCII; i++) {
        fputc(list[i].depth, output);
    }
    for(int i = EXT_ASCII - uniqueChars; i < EXT_ASCII; i++) {
        fputc(list[i].symbol, output);
    }
    return 0;
}
CanonicalList* readHeader(FILE *input, unsigned char *uniqueChars, unsigned long *characterAmmount) {
    fread(characterAmmount, sizeof(unsigned long), 1, input);
    *uniqueChars = fgetc(input);
    CanonicalList *canonicalList = (CanonicalList*)malloc( *uniqueChars * sizeof(CanonicalList));
    for (int i = 0; i < *uniqueChars; i++) {
        canonicalList[i].depth = fgetc(input);
    }
    for (int i = 0; i < *uniqueChars; i++) {
        canonicalList[i].symbol = fgetc(input);
    }
    return canonicalList;
}
int encode(CanonicalList *list, FILE *input, FILE *output) {
    qsort(list, EXT_ASCII, sizeof(CanonicalList), sortBySymbol);
    int character, bitCount = 0;
    unsigned char leftover = 0;
    unsigned char buffer = 0;
    rewind(input);
    while ((character =  fgetc(input)) != EOF ) {
        int depth = list[character].depth;
        BigInt code = list[character].code;
        for(int bit = depth - 1; bit >= 0; bit--){
            if (bitCount == 8) {
                fputc(buffer, output);
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
        fputc(buffer, output);
    }
    fclose(output);
    return 0;
}

int decode(CanonicalList *list, unsigned long characterAmmount, int uniqueChars, FILE *input, FILE *output){
    qsort(list, uniqueChars, sizeof(CanonicalList), canonicalSort);
    int searchIndex[uniqueChars];
    for (int i = 0; i < uniqueChars; i++) {
        searchIndex[i] = uniqueChars;
    }
    for (int i = 0; i < uniqueChars; i++) {
        if (searchIndex[list[i].depth] > i ) {
            searchIndex[list[i].depth] = i;
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
                buffer = fgetc(input);
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
                    if (list[currentIndex].depth > length || currentIndex  == uniqueChars) {
                        break;
                    }
                    if (code == list[currentIndex].code) {
                        fputc(list[currentIndex].symbol, output);
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
}