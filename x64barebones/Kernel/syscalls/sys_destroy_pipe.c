#include <pipes.h>
#include <syscalls.h>

uint64_t sys_destroy_pipe(unsigned int pipe_id)
{
	destroy_pipe(pipe_id);
	return 1;
}
