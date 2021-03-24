#ifndef HEAPLIB_H
#define HEAPLIB_H

typedef struct HeapNode* Heap;

struct HeapNode {
    int node;
    int weight;
    Heap leftChild, rightChild;
};

#endif
