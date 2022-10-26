#ifndef _SYSCALLS_H
#define _SYSCALLS_H

/*--------  DEPENDENCIES --------*/
#include <stdint.h>
#include <video.h>


/* --- CONSTANTS  --- */
#define SYS_READ_FROM_SCREEN 0
#define SYS_WRITE_TO_SCREEN 1
#define SYS_CLEAR_SCREEN 2
#define SYS_REGISTER_PROCESS 3 
#define SYS_RTC 4
#define SYS_CONSUME_STDIN 7

#define SYS_KILL_PROCESS 8
#define SYS_PAUSE_PROCESS 9

#define SYS_INFOREG 10
#define SYS_PRINTMEM 11

#define SYS_REGISTER_CHILD_PROCESS 12
#define SYS_WAIT_FOR_CHILDREN 13
#define SYS_RENOUNCE_CPU 14

#define SYS_NICE 15
#define SYS_GET_PID 16
#define SYS_LIST_PROCESS 17

#define SYS_ALLOC 18
#define SYS_FREE 19

#define SYS_WAIT_SEM 20
#define SYS_REGISTER_SEM 21
#define SYS_SIGNAL_SEM 22
#define SYS_PRINT_SEM 23
#define SYS_DESTROY_SEM 24

#define SYS_WRITE_PIPE 25
#define SYS_REGISTER_PIPE 26
#define SYS_READ_PIPE 27
#define SYS_PRINT_PIPE 28
#define SYS_DESTROY_PIPE 29

// Return values
#define INVALID_SCREEN -1

uint64_t sys_print_pipe();
uint64_t sys_destroy_pipe(unsigned int pipe_id);
uint64_t sys_read_pipe(unsigned int pipe_id, uint8_t * dest, unsigned int count);
uint64_t sys_write_pipe(unsigned int pipe_id, uint8_t * src, unsigned int count);
uint64_t sys_register_pipe(unsigned int pipe_id);

unsigned int sys_destroy_sem(unsigned int sem_id);
unsigned int sys_print_sem();
unsigned int sys_signal_sem(unsigned int sem_id);
unsigned int sys_register_sem(unsigned int sem_id, unsigned int value);
unsigned int sys_wait_sem(unsigned int sem_id);

unsigned int sys_free(void * ptr);

unsigned int sys_alloc(void ** ptr, uint64_t len);

unsigned int sys_list_process();

unsigned int sys_get_pid();

unsigned int sys_nice(uint8_t pid, int delta);

unsigned int sys_renounce_cpu();

unsigned int sys_wait_for_children();

unsigned int sys_register_child_process(uint64_t entryPoint, int screen, uint64_t arg0);

/*
 * << sys_write >>
 * ----------------------------------------------------------------------
 * Descripcion: Takes up to [count] bytes from [buf] 
 *              and writes to a file descriptor ([fd])
 * ----------------------------------------------------------------------
 * Recibe: 
 *      [fd] = file descriptor to write
 *      [buf] = string to be written
 *      [count] = number of letters to be written
 * Devuelve: 
 *      (uint) bytes written
 *      
 */
unsigned int sys_write(unsigned int fd, const char *buf, unsigned int count);


/*
 * << sys_read >>
 * ----------------------------------------------------------------------
 * Descripcion: Reads up to [count] bytes from [fd] and writes to [buf]
 * ----------------------------------------------------------------------
 * Recibe: 
 *      [fd] = file descriptor to read from
 *      [buf] = pointer to zone to leave what was read
 *      [count] = number of letters to be written
 * Devuelve: 
 *      (uint) bytes read
 */
unsigned int sys_read(unsigned int fd, char * buf, unsigned int count);

/*
 * << sys_clear_screen >>
 * ----------------------------------------------------------------------
 * Description: Clears STODUT
 * ----------------------------------------------------------------------
 * Receives: --
 * Returns: 
 *      0 if successful 
 */
unsigned int sys_clear_screen();

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
unsigned int sys_rtc(unsigned int option);

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
unsigned int sys_write_to_screen(const char *buf, unsigned int count);

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

unsigned int sys_read_from_screen(char *buf, unsigned int count);


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
unsigned int sys_register_process(uint64_t entryPoint, int screen, uint64_t arg0);

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
unsigned int sys_kill_process(unsigned int pid);

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
unsigned int sys_pause_process(unsigned int pid);


/*
 * << sys_consume_stdin >>
 * ----------------------------------------------------------------------
 * Description: Consumes buffer without interrupting to receive keyboard
 * ----------------------------------------------------------------------
 * Receives: 
 *      (char*) buffer to leave keys consumed
 *      (uint) amount of keys to consume
 * Returns: 
 *      (uint) amount of keys consumed
 */
unsigned int sys_consume_stdin(char * buf, unsigned int count);    

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

/*
 * << sys_inforeg >>
 * ----------------------------------------------------------------------
 * Description: Transfers saved register data from saveInfoReg into a buffer
 * ----------------------------------------------------------------------
 * Receives: 
 *      (char*) buffer to leave register values
 * Returns: --
 */
unsigned int sys_inforeg(uint64_t * buffer);

/*
 * << sys_printmem >>
 * ----------------------------------------------------------------------
 * Description: Memory dump starting from [position]
 * ----------------------------------------------------------------------
 * Receives: 
 *      (uint64_t) starting position of mem dump
 *      (char*) buffer to leave data
 * Returns: --
 */
unsigned int sys_printmem(uint64_t position, char * buffer);


#endif
