// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <io.h>

/* Decides where to write */
uint64_t sys_write(unsigned int fd, const char *buf, unsigned int count) {
	return writeDispatcher(fd, buf, count);
}
