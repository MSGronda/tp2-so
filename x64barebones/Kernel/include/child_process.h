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

/**
 * @brief   Adds a child process which executes a specific function
 * 
 * @param   entrypoint Pointer to function which child will execute
 * @param   input Where will the child get info from
 * @param   output Where will the child print its output
 * @param   arg0 Arguments of the function passed in entrypoint. NULL terminated
 * 
 * @note    If you want child process to appear in the ps command, start arg0 with
 *          the name of the child process. Eg: { "child1", arg0, arg1, ..., NULL }
*/
unsigned int add_child_task(uint64_t entrypoint, uint8_t input, uint8_t output, char **  arg0);


#endif