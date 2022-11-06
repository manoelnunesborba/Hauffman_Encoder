#include <stdio.h>
#define EXT_ASCII 256
typedef unsigned __int128 BigInt;
typedef struct CanonicalList CanonicalList;
struct CanonicalList {
    unsigned char symbol;
    unsigned char depth;
    BigInt code;
};
unsigned char getUniqueChars(LinkedListRoot list);
int getSymbolsDepth(HuffmanLeaf *node, CanonicalList list[]);
int canonicalSort(const void *firstItem, const void *secondItem);
int sortBySymbol(const void *firstItem, const void *secondItem);
int assignCodes(CanonicalList *list, int uniqueChars, int size);
int writeHeader(CanonicalList *list, unsigned char uniqueChars, unsigned long characterAmmount, FILE *output);
int encode(CanonicalList *list, FILE *input, FILE *output);
CanonicalList* readHeader(FILE *input, unsigned char *uniqueChars, unsigned long *characterAmmount);
int decode(CanonicalList *list, unsigned long characterAmmount, int uniqueChars, FILE *input, FILE *output);