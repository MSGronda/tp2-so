#ifndef _PIPES_H_
#define _PIPES_H_

#include <semaphore.h>
#include <memoryManager.h>
#include <stdint.h>
#include <lib.h>
#include <stdbool.h>

#define INVALID_PIPE_ID -1
#define EOF -1



uint64_t get_pipe_info(pipes_info * info);

void signal_eof(unsigned int pipe_id);
int create_pipe_available();

int create_pipe(unsigned int pipe_id);
void destroy_pipe(unsigned int pipe_id);

int read_from_pipe(unsigned int pipe_id, char * dest, unsigned int count);
int write_to_pipe(unsigned int pipe_id, const char * src, unsigned int count);



#endif
