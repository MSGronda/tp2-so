#include <syscalls.h>
#include <io.h>

unsigned int sys_read(unsigned int fd, char * buf, unsigned int count, uint64_t rsp , uint64_t ss){
	return readDispatcher(fd, buf, count, rsp, ss);
}

