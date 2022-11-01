#ifndef _SYSCALLS_H
#define _SYSCALLS_H

#include <stdint.h>

uint64_t sys_mm_status(uint64_t * buffer);
uint64_t sys_destroy_sem(unsigned int semId);
uint64_t sys_print_sem();
uint64_t sys_free(void * ptr);
uint64_t sys_alloc(uint64_t len);

uint64_t sys_print_pipe();
uint64_t sys_destroy_pipe(unsigned int pipe_id);
uint64_t sys_read_pipe(unsigned int pipe_id, uint8_t * dest, unsigned int count);
uint64_t sys_write_pipe(unsigned int pipe_id, uint8_t * src, unsigned int count);
uint64_t sys_register_pipe(unsigned int pipe_id);

uint64_t  sys_destroy_sem(unsigned int sem_id);
uint64_t  sys_print_sem();
uint64_t  sys_list_process();
uint64_t  sys_get_pid();
uint64_t  sys_nice(uint8_t pid, int delta);
uint64_t  sys_renounce_cpu();
uint64_t  sys_wait_for_children();
uint64_t sys_register_child_process(uint64_t entryPoint, uint8_t input, uint8_t output, uint64_t arg0);

/*
 * << sys_clear_screen >>
 * ----------------------------------------------------------------------
 * Description: Clears STODUT
 * ----------------------------------------------------------------------
 * Receives: --
 * Returns: 
 *      0 if successful 
 */
uint64_t  sys_clear_screen();

/*
 * << sys_rtc >>
 * ----------------------------------------------------------------------
 * Description: Gets current hour(1) or current day(2)
 * ----------------------------------------------------------------------
 * Receives: 
 *      1 => get current hour
 *      2 => get current day
 * Returns: 
 *      current hour HHMMSS
 *      current day DDMMYY
 *      0 other option
 */
uint64_t  sys_rtc(unsigned int option);

/*
 * << sys_write_to_screen >>
 * ----------------------------------------------------------------------
 * Description: Writes to screen
 * ----------------------------------------------------------------------
 * Receives: 
 *      [buf] = string to be written
 *      [count] = number of letters to be written
 * Returns: 
 *      (uint) bytes written
 */
uint64_t  sys_write(const char *buf, unsigned int count);

/*
 * << sys_read_from_screen >>
 * ----------------------------------------------------------------------
 * Description: Reads from screen
 * ----------------------------------------------------------------------
 * Receives: 
 *      [buf] = string to be read
 *      [count] = number of letters to be read
 * Returns: 
 *      (uint) bytes read
 */

uint64_t  sys_read(char *buf, unsigned int count);


/*
 * << sys_register_process >>
 * ----------------------------------------------------------------------
 * Description: Registers a processs to participate in multitasking
 * ----------------------------------------------------------------------
 * Receives: 
 *      (uint64_t) start of function
 *      (int) screen to print
 *      (uint64_t) argument of function (if any)
 * Returns: 
 *      (uint) pid
 */
uint64_t sys_register_process(uint64_t entrypoint, uint8_t input, uint8_t output, uint64_t arg0);

/*
 * << sys_kill_process >>
 * ----------------------------------------------------------------------
 * Description: Eliminates a task from multitasking
 * ----------------------------------------------------------------------
 * Receives: 
 *      (uint64_t) pid of process to kill
 * Returns: 
 *      (uint) 1 if it was killed
 *             -1 if no task was found
 */
uint64_t  sys_kill_process(unsigned int pid);

/*
 * << sys_pause_process >>
 * ----------------------------------------------------------------------
 * Description: Pauses or unpauses a task
 * ----------------------------------------------------------------------
 * Receives: 
 *      (uint64_t) pid of process to pause/unpause
 * Returns: 
 *      (uint) 1 if it was killed
 *             -1 if no task was found
 */
uint64_t  sys_pause_process(unsigned int pid);
uint64_t  sys_inforeg(uint64_t * buffer);


/*
 * << saveInfoReg >>
 * ----------------------------------------------------------------------
 * Description: Makes a snapshot of register values at the time of calling
 * this function
 * ----------------------------------------------------------------------
 * Receives: 
 *      (uint64_t*) place where all registers can be found
 * Returns: --
 */
void saveInfoReg(uint64_t * regDumpPos);

#endif
