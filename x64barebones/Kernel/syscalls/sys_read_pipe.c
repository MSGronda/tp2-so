#include <pipes.h>
#include <syscalls.h>

uint64_t sys_read_pipe(unsigned int pipe_id, uint8_t * dest, unsigned int count, uint64_t rsp, uint64_t ss)
{
	read_from_pipe(pipe_id, dest, count, rsp, ss);
	return 1;
}
