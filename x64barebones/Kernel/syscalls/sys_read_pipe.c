#include <pipes.h>
#include <syscalls.h>

uint64_t sys_read_pipe(unsigned int pipe_id, char * dest, unsigned int count)
{
	return read_from_pipe(pipe_id, dest, count);
}
