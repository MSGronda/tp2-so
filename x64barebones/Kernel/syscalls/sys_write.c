#include <video.h>

/* Decides where to write */
unsigned int sys_write(unsigned int fd, const char *buf, unsigned int count) {
	return writeDispatcher(fd, buf, count);
}
