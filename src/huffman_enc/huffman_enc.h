/**
* Structure et prototype de compression et decrompression
*
* @author  Nunes Borba Manoel / Quitman Lucas / Mozet Jacques-Arno
* @version 1.0
* @since   2022-09-11
*/
#ifndef HUFFMAN_ENC_H_INCLUDED
#define HUFFMAN_ENC_H_INCLUDED

#define EXT_ASCII 256

#include <stdio.h>



#include "../huffman_tree/huffman_tree.h"
#include "../frequency/frequency.h"

typedef __int128 BigInt;
typedef struct CanonicalList CanonicalList;
struct CanonicalList {
    unsigned char Symbol;
    unsigned char Depth;
    BigInt Code;
};
unsigned char getUniqueChars(FrequencyListRoot list);
void assignSymbolsDepth(HuffmanLeaf *node, CanonicalList list[]);
static int canonicalSort(const void *firstItem, const void *secondItem);
static int sortBySymbol(const void *firstItem, const void *secondItem);
void assignCodes(CanonicalList *list, int uniqueChars, int size);
int writeHeader(CanonicalList *list, unsigned char uniqueChars, unsigned long characterAmmount, FILE *outputStream);
int encode(CanonicalList *list, FILE *inputStream, FILE *output);
CanonicalList* readHeader(FILE *inputStream, unsigned char *uniqueChars, unsigned long *characterAmmount);
int decode(CanonicalList *list, unsigned long characterAmmount, int uniqueChars, FILE *inputStream, FILE *outputStream);

#endif