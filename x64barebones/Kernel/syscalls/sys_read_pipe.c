// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <pipes.h>
#include <syscalls.h>

uint64_t sys_read_pipe(unsigned int pipe_id, char * dest, unsigned int count)
{
	return read_from_pipe(pipe_id, dest, count);
}
