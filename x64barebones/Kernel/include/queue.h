#ifndef	_QUEUE_H
#define _QUEUE_H

#include <stdint.h>
#include <memoryManager.h>

typedef struct queueADT{
    uint64_t  * array;
    unsigned int readPos;
    unsigned int writePos;
    unsigned int amount;        // mucho mas entendible con una variable
    unsigned int size;
}queueADT;

#endif