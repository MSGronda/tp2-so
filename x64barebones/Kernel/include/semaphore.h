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
#include <data_types.h>
#include <stdbool.h>

unsigned int get_blocked_by_sem_id(unsigned int sem_id, unsigned int * blocked_pids);
unsigned int get_sem_blocked_process(unsigned int i, unsigned int * blocked_pids);
uint64_t get_semaphore_info(semaphore_info * info);

int create_sem_available(unsigned int value);

int create_sem(unsigned int sem_id, unsigned int value);
void destroy_sem(unsigned int sem_id);

unsigned int signal_sem(unsigned int sem_id);
unsigned int wait_sem(unsigned int sem_id);

#endif
