/**
* Structure et prototype de creation de l'arbre de huffman
*
* @author  Nunes Borba Manoel / Quitman Lucas / Mozet Jacques-Arno
* @version 1.0
* @since   2022-09-11
*/


#ifndef HAUFFMAN_TREE_HUFFMAN_H
#define HAUFFMAN_TREE_HUFFMAN_H

#include "../frequency/frequency.h"

typedef struct HuffmanLeaf HuffmanLeaf;
struct HuffmanLeaf {
    char Letter;
    int Frequency;
    HuffmanLeaf *Left;
    HuffmanLeaf *Right;
    HuffmanLeaf *Parent;
};

typedef struct HuffmanRoot HuffmanRoot;
struct HuffmanRoot {
    HuffmanLeaf *Root;
    int TotalValue;
};

HuffmanRoot * createHuffmanRoot();
static HuffmanLeaf * createHuffmanLeaf(char Letter, int Frequency);
void createHuffmanTree(FrequencyListRoot * frequencyList, HuffmanRoot * huffmanRoot);
static void addLeaves(HuffmanLeaf * parent, HuffmanLeaf * leftChild, HuffmanLeaf * rightChild);
static void initializeHuffmanTree(HuffmanRoot * huffmanRoot, FrequencyListRoot * linkedListRoot);
static void createParallelTree(HuffmanRoot * huffmanRoot, FrequencyListRoot * linkedListRoot);
static void createBranch(FrequencyListRoot * listWordRoot, HuffmanRoot * root);
int isNULL(FrequencyListNode * list);

#endif
