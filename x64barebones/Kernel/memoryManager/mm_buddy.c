#include <memoryManager.h>

#define MIN_SIZE_CLASS 5
#define BUDDY_START ((uint64_t *) 0xA00000)
#define BUDDY_SUM_PTR(ptr, num) (((uint64_t) (ptr) + (num)) )

typedef struct TNode{
    uint8_t sizeClass;
    char isAllocated;
    char isDivided;

    uint64_t * userAddr;
    TNode * left;
    TNode * right;
} TNode;

void mm_init() {

    int maxSizeClass = getSizeClass(HEAP_SIZE);

    uint64_t * sizeClasses = BUDDY_START;

    int nodes = (1  << ((maxSizeClass - MIN_SIZE_CLASS) + 1)) - 1; // 2^h+1 - 1

    //Como nos aseguramos que el TREE + la memoria de 2^maxSizeClass entre en el heapsize??

    uint64_t * userStart = (uint64_t *) BUDDY_SUM_PTR(BUDDY_START, nodes * sizeof(TNode));


    uint64_t endOfTree;    
    buildTreeRec(BUDDY_START, maxSizeClass, userStart, &endOfTree);
    
}


//Buildeo el arbol primero izq hasta llegar al MIN_SIZE_CLASS y lo mismo por la der despues.
TNode * buildTreeRec(uint64_t * currAddr, int sizeClass, uint64_t * userAddr, uint64_t * finalAdress) {

    //Si ya me pase del MIN_SIZE_CLASS devuelvo NULL pues el padre es el ultimo.
    if(sizeClass == MIN_SIZE_CLASS - 1){
        *finalAdress = currAddr;
        return NULL;
    }

    TNode * currNode = (TNode *) currAddr;
    currAddr = BUDDY_SUM_PTR(currAddr, sizeof(TNode));

    currNode->sizeClass = sizeClass;
    currNode->isAllocated = FALSE;
    currNode->userAddr = userAddr;
    currNode->isDivided = FALSE;

    uint64_t final;
    
    
    uint64_t * leftAddr = userAddr;
    currNode->left = buildTree(BUDDY_SUM_PTR(currAddr, sizeof(TNode)), sizeClass - 1, leftAddr ,&final);
    currAddr = final;

    uint64_t halfBlockSize = getSize(sizeClass)/2;
    uint64_t * rightAddr = BUDDY_SUM_PTR(userAddr, halfBlockSize);
    currNode->right = buildTree(BUDDY_SUM_PTR(currAddr, sizeof(TNode)), sizeClass - 1, rightAddr ,&final);
    currAddr = final;

    *finalAdress = currAddr;
    return currNode;
}

void setNode(TNode * node, int size, char allocated, uint64_t userAddr, TNode * left, TNode * right){
    node->sizeClass = size;
    node->isAllocated = allocated;
    node->userAddr = userAddr;
    node->left = left;
    node->right = right;
}

TNode * getRoot(){
    return (TNode *) BUDDY_START;
}


//Returns the size in bytes of a block of sizeClass
//Performs a 2^sizeClass using bitwise operations
int getSize(int sizeClass){
    int out = 1;
    while(sizeClass != 0){
        out <<= 1;
        sizeClass --;
    }
    return out;
}

//Returns the max size class that fits a block of size
//Performs a log2(size) rounded to nearest whole num using bitwise operations
int getSizeClass(uint64_t size) {
    long out = 1; // TODO: creo q esto arrancaba con 0
    while((size >>= 1) != 0) 
        out++;
    return out;
}
