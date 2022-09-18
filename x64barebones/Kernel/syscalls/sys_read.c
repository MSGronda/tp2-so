#include <syscalls.h>
#include <io.h>

unsigned int sys_read(unsigned int fd, char * buf, unsigned int count){
	return readDispatcher(fd, buf, count);
}

