#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#define SUCCESS 0
#define ERROR_SEM_ID_EXISTS 1
#define ERROR_NO_MORE_SPACE 3
#define INVALID_SEM_ID 2

#define SEM_CONTINUE 0
#define SEM_BLOCK 1

#include <multitasking.h>

unsigned int create_sem(unsigned int sem_id);
int update_sem_table(unsigned int sem_id);
int can_continue(unsigned int pid);
unsigned int signal_sem(unsigned int sem_id);

#endif
