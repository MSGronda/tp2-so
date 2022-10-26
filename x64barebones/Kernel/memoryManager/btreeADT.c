#include "./btreeADT.h"

static TNode * root;

TNode * initTree(uint64_t * start, int sizeClass, uint64_t * userAdd){
    setRoot((TNode *) start);
    setNode(root, sizeClass, 0, userAdd, NULL, NULL);
    return root;
}

void setRoot(TNode * addr){
    root = addr;
}


void setNode(TNode * node, int size, char allocated, uint64_t userAdd, TNode * left, TNode * right){
    node->sizeClass = size;
    node->isAllocated = allocated;
    node->userAdd = userAdd;
    node->left = left;
    node->right = right;
}
