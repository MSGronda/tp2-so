#include <pipes.h>
#include <syscalls.h>

uint64_t sys_write_pipe(unsigned int pipe_id, uint8_t * src, unsigned int count)
{
	return write_to_pipe(pipe_id, src, count);
}
