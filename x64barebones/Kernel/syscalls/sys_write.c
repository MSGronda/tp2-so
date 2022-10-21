#include <video.h>

/* Decides where to write */
uint64_t sys_write(unsigned int fd, const char *buf, unsigned int count) {
	return writeDispatcher(fd, buf, count);
}
