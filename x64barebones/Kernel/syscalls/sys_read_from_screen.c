#include <multitasking.h>
#include <syscalls.h>

unsigned int sys_read_from_screen(char *buf, unsigned int count, uint64_t rsp , uint64_t ss) {
	return sys_read(getCurrentScreen(),buf,count, rsp, ss);			// no requiere de la especificacion de a que pantalla escribir 
}