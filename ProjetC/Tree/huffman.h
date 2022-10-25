//
// Created by jacqu on 25/10/2022.
//

#ifndef HAUFFMAN_ENCODER_HUFFMAN_H
#define HAUFFMAN_ENCODER_HUFFMAN_H

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

HuffmanLeaf * createHuffmanLeaf(char Letter, int Frequency);

void addLeaves(HuffmanLeaf * parent, HuffmanLeaf * leftChild, HuffmanLeaf * rightChild);

#endif //HAUFFMAN_ENCODER_HUFFMAN_H
