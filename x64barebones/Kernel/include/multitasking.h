#ifndef _MULTITASKING_H
#define _MULTITASKING_H

/*--------  DEPENDENCIES --------*/
#include <interrupts.h>
#include <stdint.h>

/* --- CONSTANTS  --- */
// Return values
#define NO_TASKS 0
#define NO_TASK_FOUND -1
#define TASK_ALTERED 1

#define ERROR_NO_SPACE_FOR_TASK 1 
#define ERROR_SCREEN_NOT_AVAILABLE 2

// Common constantes
#define DEFAULT_PRIORITY 1
#define IMMORTAL 1
#define MORTAL 0

/* --- Init --- */
void enableMultiTasking();


/* --- Getters --- */
uint64_t getRSP();
uint64_t getSS();
uint8_t getCurrentScreen();


/* --- Process Management --- */
int add_task(uint64_t entrypoint, uint8_t screen, uint8_t priority, uint8_t immortal ,uint64_t arg0);

void pauseScreenProcess(unsigned int screen);
int pauseOrUnpauseProcess(unsigned int pid);

void kill_screen_processes();
void removeCurrentTask();
int removeTask(unsigned int pid);


/* --- Scheduling --- */
uint8_t has_or_decrease_time();
void moveToNextTask(uint64_t stackPointer, uint64_t stackSegment);


/* --- Child processes --- */
void wait_for_children(uint64_t rsp, uint64_t ss);
unsigned int add_child_task(uint64_t entrypoint, int screen, uint64_t arg0);

#endif
