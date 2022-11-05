// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <pipes.h>
#include <syscalls.h>

uint64_t sys_destroy_pipe(unsigned int pipe_id)
{
	destroy_pipe(pipe_id);
	return 1;
}
