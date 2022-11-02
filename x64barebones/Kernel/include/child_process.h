#ifndef CHILD_PROCESS_H_
#define CHILD_PROCESS_H_

#include <multitasking.h>
#include <interrupts.h>

uint8_t has_children(unsigned int pid);
void signal_process_finished(unsigned int pid);
void remove_children(unsigned int fatherPid);
void add_child(unsigned int fatherPid, unsigned int childPid);
uint8_t children_finished(unsigned int fatherPid);


void wait_for_children();
unsigned int add_child_task(uint64_t entrypoint, uint8_t input, uint8_t output, char **  arg0);


#endif