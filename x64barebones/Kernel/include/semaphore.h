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
void sem_decrease_semid(unsigned int sem_id);
void sem_decrease_pid(unsigned int pid);
unsigned int signal_sem(unsigned int sem_id);
void add_waiting(unsigned int sem_id, unsigned int pid);
void remove_waiting(unsigned int pid);
uint8_t can_continue_semid(unsigned int sem_id);
uint8_t can_continue_pid(unsigned int pid);

#endif
