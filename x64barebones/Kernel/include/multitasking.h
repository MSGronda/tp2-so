#ifndef _MULTITASKING_H
#define _MULTITASKING_H

/*--------  DEPENDENCIES --------*/
#include <interrupts.h>
#include <stdint.h>
#include <video.h>
#include <child_process.h>
#include <semaphore.h>
#include <pipes.h>
#include <data_types.h>
#include <io.h>
#include <stdbool.h>

/* --- CONSTANTS  --- */
// Return values
#define NO_TASKS 0
#define NO_TASK_FOUND -1
#define TASK_ALTERED 1
#define TASK_NOT_ALTERED -1

#define ERROR_NO_SPACE_FOR_TASK -1
#define ERROR_SCREEN_NOT_AVAILABLE 2

// Common constantes
#define DEFAULT_PRIORITY 1
#define IMMORTAL 1
#define MORTAL 0

// ----- Estado de task -----
#define DEAD_PROCESS 0
#define ACTIVE_PROCESS 1 
#define PAUSED_PROCESS 2
#define WAITING_FOR_CHILD 3
#define WAITING_FOR_SEM 4
#define WAITING_FOR_INPUT 5

int get_process_info(process_info * info);

void list_process();

/* --- Init --- */
void enableMultiTasking();


/* --- Getters --- */
uint64_t getRSP();
uint64_t getSS();
uint8_t get_current_output();
uint8_t get_current_input();
unsigned int  get_current_pid();


int findTask(unsigned int pid);

/* --- Process Management --- */
int add_task(uint64_t entrypoint, uint8_t input, uint8_t output, uint8_t priority, uint8_t immortal, char ** arg0);

void alter_process_state(unsigned int pid, uint8_t new_state);
void alter_state_if(uint8_t old_state, uint8_t new_state);

void pauseScreenProcess(unsigned int screen);
int pauseOrUnpauseProcess(unsigned int pid);

void kill_screen_processes();
void removeCurrentTask();
int removeTask(unsigned int pid);

unsigned int change_priority(unsigned int pid, int delta);

void forceChangeTask();

/* --- Scheduling --- */
uint8_t has_or_decrease_time();
uint64_t next_task(uint64_t stackPointer, uint64_t stackSegment);




#endif
