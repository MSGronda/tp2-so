#include <pipes.h>
#include <syscalls.h>

uint64_t sys_read_pipe(unsigned int pipe_id, uint8_t * dest, unsigned int count)
{
	read_from_pipe(pipe_id, dest, count);
	return 1;
}
