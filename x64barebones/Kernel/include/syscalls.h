#ifndef _SYSCALLS_H
#define _SYSCALLS_H

/*--------  DEPENDENCIES --------*/
#include <stdint.h>
#include <multitasking.h>
#include <video.h>
#include <data_types.h>

/* --- CONSTANTS  --- */
#define SYS_READ_FROM_SCREEN 0
#define SYS_WRITE_TO_SCREEN 1
#define SYS_CLEAR_SCREEN 2
#define SYS_REGISTER_PROCESS 3 
#define SYS_RTC 4

#define SYS_KILL_PROCESS 8
#define SYS_PAUSE_PROCESS 9

#define SYS_REGISTER_CHILD_PROCESS 12
#define SYS_WAIT_FOR_CHILDREN 13
#define SYS_RENOUNCE_CPU 14

#define SYS_NICE 15
#define SYS_GET_PID 16

#define SYS_ALLOC 18
#define SYS_FREE 19

#define SYS_WAIT_SEM 20
#define SYS_REGISTER_SEM 21
#define SYS_SIGNAL_SEM 22

#define SYS_DESTROY_SEM 24

#define SYS_WRITE_PIPE 25
#define SYS_REGISTER_PIPE 26
#define SYS_READ_PIPE 27

#define SYS_DESTROY_PIPE 29
#define SYS_REGISTER_PIPE_AVAILABLE 30
#define SYS_MM_STATUS 31
#define SYS_PROCESS_ALIVE 32

#define SYS_PROCESS_INFO 33
#define SYS_SEMAPHORE_INFO 34
#define SYS_PIPE_INFO 35

#define SYS_REGISTER_SEM_AVAILABLE 36

// Return values
#define INVALID_SCREEN -1

uint64_t sys_pipe_info(pipes_info * info);
uint64_t sys_semaphore_info(semaphore_info * info);
uint64_t sys_process_info(process_info * info);
uint64_t sys_mm_status(uint64_t * buffer);


uint64_t sys_process_alive(unsigned int pid);

uint64_t sys_register_pipe_available();

uint64_t sys_destroy_pipe(unsigned int pipe_id);
uint64_t sys_read_pipe(unsigned int pipe_id, char * dest, unsigned int count);
uint64_t sys_write_pipe(unsigned int pipe_id, const char * src, unsigned int count);
uint64_t sys_register_pipe(unsigned int pipe_id);

uint64_t sys_destroy_sem(unsigned int sem_id);

uint64_t sys_signal_sem(unsigned int sem_id);
uint64_t sys_register_sem(unsigned int sem_id, unsigned int value);
uint64_t sys_wait_sem(unsigned int sem_id);


uint64_t sys_free(void * ptr);

uint64_t sys_alloc(uint64_t len);

uint64_t sys_get_pid();

uint64_t sys_nice(uint8_t pid, int delta);

uint64_t sys_renounce_cpu();

uint64_t sys_wait_for_children();

uint64_t sys_register_child_process(uint64_t entryPoint, uint8_t input, uint8_t output, char ** arg0);

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
uint64_t sys_write(unsigned int fd, const char *buf, unsigned int count);


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
uint64_t sys_read(unsigned int fd, char * buf, unsigned int count);

/*
 * << sys_clear_screen >>
 * ----------------------------------------------------------------------
 * Description: Clears STODUT
 * ----------------------------------------------------------------------
 * Receives: --
 * Returns: 
 *      0 if successful 
 */
uint64_t sys_clear_screen();

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
uint64_t sys_rtc(unsigned int option);

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
uint64_t sys_write_to_screen(const char *buf, unsigned int count);

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

uint64_t sys_read_from_screen(char *buf, unsigned int count);


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
uint64_t sys_register_process(uint64_t entrypoint, uint8_t input, uint8_t output, char **  arg0);

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
uint64_t sys_kill_process(unsigned int pid);

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
uint64_t sys_pause_process(unsigned int pid);

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
