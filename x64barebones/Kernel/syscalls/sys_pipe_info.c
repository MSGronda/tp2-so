#include <pipes.h>
#include <data_types.h>
#include <syscalls.h>

uint64_t sys_pipe_info(pipes_info * info)
{
	return get_pipe_info(info);
}
