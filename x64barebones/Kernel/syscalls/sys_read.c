// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <syscalls.h>
#include <io.h>

uint64_t sys_read(unsigned int fd, char * buf, unsigned int count){
	return readDispatcher(fd, buf, count);
}

