#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#define SUCCESS 0
#define ERROR_SEM_ID_EXISTS -1
#define ERROR_NO_MORE_SPACE -3
#define INVALID_SEM_ID -2

#define SEM_CONTINUE 0
#define SEM_BLOCK 1

#include <multitasking.h>
#include <video.h>
#include <interrupts.h>
#include <locks.h>
#include <queue.h>

int create_sem_available(unsigned int value);

int create_sem(unsigned int sem_id, unsigned int value);
void destroy_sem(unsigned int sem_id);

unsigned int signal_sem(unsigned int sem_id);
unsigned int wait_sem(unsigned int sem_id);

void print_sem();
#endif
