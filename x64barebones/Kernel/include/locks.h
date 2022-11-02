#ifndef LOCKS_H_
#define LOCKS_H_

#include <libasm.h>

void lock(unsigned int * lock);
void unlock(unsigned int * lock);

#endif