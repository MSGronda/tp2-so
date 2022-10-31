#include <pipes.h>
#include <syscalls.h>

uint64_t sys_register_pipe_available()
{
	return create_pipe_available();
}
