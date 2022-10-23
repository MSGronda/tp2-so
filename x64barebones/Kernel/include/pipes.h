#ifndef _PIPES_H_
#define _PIPES_H_

#include <semaphore.h>
#include <memoryManager.h>
#include <stdint.h>
#include <lib.h>

#define INVALID_PIPE_ID 2

int create_pipe(unsigned int pipe_id);
void destroy_pipe(unsigned int pipe_id);

void read_from_pipe(unsigned int pipe_id, uint8_t * dest, unsigned int count, uint64_t rsp, uint64_t ss);
void write_to_pipe(unsigned int pipe_id, uint8_t * src, unsigned int count, uint64_t rsp, uint64_t ss);

void print_pipe();

#endif
