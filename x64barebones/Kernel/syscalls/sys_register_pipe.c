#include <pipes.h>
#include <syscalls.h>

uint64_t sys_register_pipe(unsigned int pipe_id)
{
	return create_pipe(pipe_id);
}
