// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <pipes.h>
#include <data_types.h>
#include <syscalls.h>

uint64_t sys_pipe_info(pipes_info * info)
{
	return get_pipe_info(info);
}
