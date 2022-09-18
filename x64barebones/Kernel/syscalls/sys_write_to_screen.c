#include <syscalls.h>
#include <multitasking.h>

unsigned int sys_write_to_screen(const char *buf, unsigned int count) {
	return sys_write(getCurrentScreen(),buf,count);			// no requiere de la especificacion de a que pantalla escribir 
}