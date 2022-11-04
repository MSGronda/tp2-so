#ifndef _SYSCALLS_H
#define _SYSCALLS_H

#include <stdint.h>
#include <data_types.h>

uint64_t sys_pipe_info(pipes_info * info);
uint64_t sys_semaphore_info(semaphore_info * info);
uint64_t sys_process_info(process_info * info);
uint64_t sys_mm_status(uint64_t * buffer);


uint64_t sys_process_alive(unsigned int pid);

uint64_t sys_register_sem_available(unsigned int value);
uint64_t sys_register_sem(unsigned int sem_id, unsigned int value);
uint64_t  sys_signal_sem(unsigned int sem_id);
uint64_t  sys_wait_sem(unsigned int sem_id);
uint64_t sys_destroy_sem(unsigned int semId);

uint64_t sys_free(void * ptr);
uint64_t sys_alloc(uint64_t len);


uint64_t sys_destroy_pipe(unsigned int pipe_id);
uint64_t sys_read_pipe(unsigned int pipe_id, char * dest, unsigned int count);
uint64_t sys_write_pipe(unsigned int pipe_id, const char * src, unsigned int count);
uint64_t sys_register_pipe(unsigned int pipe_id);
uint64_t sys_register_pipe_available();

uint64_t  sys_get_pid();
uint64_t  sys_nice(uint8_t pid, int delta);
uint64_t  sys_renounce_cpu();
uint64_t  sys_wait_for_children();
uint64_t sys_register_child_process(uint64_t entryPoint, uint8_t input, uint8_t output, uint64_t arg0);

uint64_t  sys_clear_screen();

/**
 * @brief   Gets currento hour or day
 * 
 * @param   option If 1, then get current hour, min, sec
 *                 If 2, then get current day, month, year
 * 
 * @return  HHMMSS (current hour)
 *          DDMMYY (current year)
*/
uint64_t  sys_rtc(unsigned int option);

uint64_t  sys_write(const char *buf, unsigned int count);

uint64_t  sys_read(char *buf, unsigned int count);

/**
 * @brief   Registers a process to participate in multitasking
 * 
 * @param   entrypoint Pointer to function wanting to be registered
 * @param   input Screen where process will consume the buffer
 * @param   output Screen where process will print to
 * @param   arg0 Pointer to arguments of function
 *               Format: { "arg0", "arg1", ..., NULL }
 * 
 * @return  pid
*/
uint64_t sys_register_process(uint64_t entrypoint, uint8_t input, uint8_t output, uint64_t arg0);

uint64_t  sys_kill_process(unsigned int pid);

uint64_t  sys_pause_process(unsigned int pid);

uint64_t  sys_inforeg(uint64_t * buffer);

void saveInfoReg(uint64_t * regDumpPos);

#endif
