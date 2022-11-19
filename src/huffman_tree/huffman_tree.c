/**
* Fonction de creation de l'arbre de huffman
*
* @author  Nunes Borba Manoel / Quitman Lucas / Mozet Jacques-Arno
* @version 1.0
* @since   2022-09-11
*/

#include "huffman_tree.h"
#include <stdlib.h>

HuffmanRoot * createHuffmanRoot() {
    HuffmanRoot * root = malloc(sizeof(HuffmanRoot));
    root->Root = NULL;
    root->TotalValue = 0;
    return root;
}

static HuffmanLeaf * createHuffmanLeaf(char Letter, int Frequency) {
    HuffmanLeaf * newLeaf = malloc(sizeof(HuffmanLeaf));
    newLeaf->Frequency = Frequency;
    newLeaf->Letter = Letter;
    newLeaf->Left = NULL;
    newLeaf->Right = NULL;
    newLeaf->Parent = NULL;
    return newLeaf;
}

static void addLeaves(HuffmanLeaf * parent, HuffmanLeaf * leftChild, HuffmanLeaf * rightChild) {
    if(leftChild == NULL || rightChild == NULL || parent == NULL)
        return;
    parent->Left = leftChild;
    parent->Right = rightChild;
    parent->Frequency = leftChild->Frequency + rightChild->Frequency;
    rightChild->Parent = parent;
    leftChild->Parent = parent;
}

void createHuffmanTree(FrequencyListRoot * frequencyList, HuffmanRoot * huffmanRoot) {
    if(huffmanRoot->Root == NULL){
        initializeHuffmanTree(huffmanRoot,frequencyList);
    }
    while(frequencyList->Start != NULL ) {
        if(frequencyList->Start->Frequency <= huffmanRoot->Root->Frequency) {
            if(isNULL(frequencyList->Start->Next))
                createBranch(frequencyList, huffmanRoot);
            else
                createParallelTree(huffmanRoot, frequencyList);
        } else {
            createBranch(frequencyList, huffmanRoot);
        }
    }
}

static void initializeHuffmanTree(HuffmanRoot * huffmanRoot, FrequencyListRoot * linkedListRoot) {
    huffmanRoot->Root = createHuffmanLeaf(' ',0);

    FrequencyListNode * listWord = linkedListRoot->Start;

    if(isNULL(linkedListRoot->Start) || isNULL(linkedListRoot->Start->Next))
        return;

    HuffmanLeaf * leafLeft = NULL;
    HuffmanLeaf * leafRight = NULL;

    if(listWord->Frequency <= listWord->Next->Frequency) {
        leafLeft = createHuffmanLeaf(listWord->Symbol, listWord->Frequency);
        leafRight = createHuffmanLeaf(listWord->Next->Symbol, listWord->Next->Frequency);
    } else {
        leafLeft = createHuffmanLeaf(listWord->Next->Symbol, listWord->Next->Frequency);
        leafRight = createHuffmanLeaf(listWord->Symbol, listWord->Frequency);
    }
    addLeaves(huffmanRoot->Root, leafLeft, leafRight);
    linkedListRoot->Start = linkedListRoot->Start->Next->Next;
}

static void createParallelTree(HuffmanRoot * huffmanRoot, FrequencyListRoot * linkedListRoot) {
    HuffmanRoot * ParallelTree = createHuffmanRoot();
    initializeHuffmanTree(ParallelTree, linkedListRoot);
    while(linkedListRoot->Start != NULL) {
        if(ParallelTree->Root->Frequency > huffmanRoot->Root->Frequency) {
            break;
        }
        createBranch(linkedListRoot, ParallelTree);
    }
    HuffmanLeaf * jointLeaf = createHuffmanLeaf(' ',0);
    addLeaves(jointLeaf,ParallelTree->Root,huffmanRoot->Root);
    huffmanRoot->Root = jointLeaf;
}

static void createBranch(FrequencyListRoot * listWordRoot, HuffmanRoot * root) {
    int nextLetterFrequency = listWordRoot->Start->Symbol == NULL ? listWordRoot->Start->Next->Frequency : listWordRoot->Start->Frequency;
    char nextLetter = listWordRoot->Start->Symbol == NULL ? listWordRoot->Start->Next->Symbol : listWordRoot->Start->Symbol;
    HuffmanLeaf * newParent = createHuffmanLeaf(' ', 0);
    if(nextLetterFrequency <= root->Root->Frequency) {
        HuffmanLeaf * left = createHuffmanLeaf(nextLetter, nextLetterFrequency);
        HuffmanLeaf * right = root->Root;
        addLeaves(newParent,left,right);
    } else {
        HuffmanLeaf * left = root->Root;
        HuffmanLeaf * right = createHuffmanLeaf(nextLetter, nextLetterFrequency);
        addLeaves(newParent,left,right);
    }
    root->Root = newParent;
    if(isNULL(listWordRoot->Start->Next) || isNULL(listWordRoot->Start)) {
        listWordRoot->Start = NULL;
        return;
    }
    listWordRoot->Start = listWordRoot->Start->Next;
}

int isNULL(FrequencyListNode * list) {
    return list == NULL ? 1 : 0;
}
