#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "HeapLib.h"

Heap emptyHeap() {
    return NULL;
}

Heap newHeapNode(int n, int w, Heap hL, Heap hR) {
    Heap new = malloc(sizeof(struct HeapNode));
    assert(new != NULL);
    new->node = n;
    new->weight = w;
    new->leftChild = hL;
    new->rightChild = hR;
    return new;
}

