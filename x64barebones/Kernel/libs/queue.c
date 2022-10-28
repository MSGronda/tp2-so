#include <queue.h>

void init_queue(queueADT * q, unsigned int size){
    if(size == 0)
        return;
    q->array = mm_malloc(size * sizeof(uint64_t));
    q->readPos = 0;
    q->writePos = 0;
    q->amount = 0;
    q->size = size;
}

unsigned int size_queue(queueADT * q){
    return q->amount;
}

void enqueue(queueADT * q, uint64_t elem){
    if(q->amount == q->size)
        return;
    q->array[q->writePos] = elem;
    q->writePos = (q->writePos + 1) % (q->size);
    q->amount++;
}

uint64_t dequeue(queueADT * q){
    if(q->amount == 0)
        return NULL;
    uint64_t resp = q->array[q->readPos];
    q->readPos = (q->readPos + 1) % (q->size);
    q->amount--;

    return resp;
}

uint8_t contais_queue(queueADT * q, uint64_t elem){
    for(unsigned int i=q->readPos, j=0;  j < q->amount; j++){
        if(q->array[i] == elem)
            return 1;
        i = (i + 1) % q->size;
    }
    return 0;
}

void destroy_queue(queueADT * q){
    mm_free(q->array);
}