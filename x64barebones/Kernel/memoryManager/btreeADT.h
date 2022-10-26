typedef struct TNode{
    int sizeClass;
    char isAllocated;
    uint64_t * userAdd;
    TNode * left;
    TNode * right;
} TNode;

TNode * initTree(uint64_t * start, int sizeClass, uint64_t * userAdd);

void setNode(TNode * node, int size, char allocated, uint64_t userAdd, TNode * left, TNode * right);

//getRoot();

//getDir();
//getAllocated();

//setAllocated();

//getLeft();
//getRight();

