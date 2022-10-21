#include <syscalls.h>
#include <keyboard.h>


uint64_t sys_consume_stdin(char * buf, unsigned int count) {
	return consume_kb_buffer(buf, count);
}
