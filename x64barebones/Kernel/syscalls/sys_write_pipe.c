#include <pipes.h>
#include <syscalls.h>

uint64_t sys_write_pipe(unsigned int pipe_id, uint8_t * src, unsigned int count, uint64_t rsp, uint64_t ss)
{
	write_to_pipe(pipe_id, src, count, rsp, ss);
	return 1;
}
