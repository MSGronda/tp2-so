#include <syscalls.h>
#include <io.h>

uint64_t sys_read(unsigned int fd, char * buf, unsigned int count){
	return readDispatcher(fd, buf, count);
}

