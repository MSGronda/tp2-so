#ifndef _MULTITASKING_H
#define _MULTITASKING_H

/*--------  DEPENDENCIES --------*/
#include <interrupts.h>
#include <stdint.h>

/* --- CONSTANTS  --- */
// Return values
#define NO_TASKS -1
#define ERROR_NO_SPACE_FOR_TASK -1
#define NO_TASK_FOUND -1
#define TASK_ALTERED 1


void enableMultiTasking();
void moveToNextTask(uint64_t stackPointer, uint64_t stackSegment);

int addTask(uint64_t entrypoint, int screen, uint64_t arg0);
void removeCurrentTask();
int removeTask(unsigned int pid);
int pauseOrUnpauseProcess(unsigned int pid);

uint64_t getRSP();
uint64_t getSS();
uint8_t getCurrentScreen();


#endif
