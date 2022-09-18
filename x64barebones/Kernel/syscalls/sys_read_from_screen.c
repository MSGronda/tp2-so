#include <multitasking.h>
#include <syscalls.h>

unsigned int sys_read_from_screen(char *buf, unsigned int count) {
	return sys_read(getCurrentScreen(),buf,count);			// no requiere de la especificacion de a que pantalla escribir 
}