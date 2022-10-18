#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#define SUCCESS 0
#define ERROR_SEM_ID_EXISTS 1
#define ERROR_NO_MORE_SPACE 3
#define INVALID_SEM_ID 2

#define SEM_CONTINUE 0
#define SEM_BLOCK 1

#include <multitasking.h>
#include <video.h>
#include <interrupts.h>

unsigned int create_sem(unsigned int sem_id);
void destroy_sem(unsigned int sem_id);

unsigned int signal_sem(unsigned int sem_id);
unsigned int wait_sem(unsigned int sem_id, uint64_t rsp, uint64_t ss);

void print_sem();
#endif