#include <multitasking.h>
#include <syscalls.h>

uint64_t sys_read_from_screen(char *buf, unsigned int count) {
	return sys_read(get_current_input(),buf,count);			// no requiere de la especificacion de a que pantalla escribir 
}