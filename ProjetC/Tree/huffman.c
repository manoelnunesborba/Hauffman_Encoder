//
// Created by jacqu on 25/10/2022.
//

#include "huffman.h"
#include <stdlib.h>

HuffmanRoot * createHuffmanRoot() {
    HuffmanRoot * root = malloc(sizeof(HuffmanRoot));
    root->Root = NULL;
    root->TotalValue = 0;
    return root;
}

HuffmanLeaf * createHuffmanLeaf(char Letter, int Frequency) {
    HuffmanLeaf * newLeaf = malloc(sizeof(HuffmanLeaf));
    newLeaf->Frequency = Frequency;
    newLeaf->Letter = Letter;
    newLeaf->Left = NULL;
    newLeaf->Right = NULL;
    newLeaf->Parent = NULL;
    return newLeaf;
}

void addLeaves(HuffmanLeaf * parent, HuffmanLeaf * leftChild, HuffmanLeaf * rightChild) {
    if(leftChild == NULL || rightChild == NULL || parent == NULL)
        return;
    parent->Left = leftChild;
    parent->Right = rightChild;
    parent->Frequency = leftChild->Frequency + rightChild->Frequency;
    rightChild->Parent = parent;
    leftChild->Parent = parent;
}