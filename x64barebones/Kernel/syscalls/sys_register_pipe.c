// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <pipes.h>
#include <syscalls.h>

uint64_t sys_register_pipe(unsigned int pipe_id)
{
	return create_pipe(pipe_id);
}
