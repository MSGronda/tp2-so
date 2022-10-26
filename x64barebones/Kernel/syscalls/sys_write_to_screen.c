#include <syscalls.h>
#include <multitasking.h>

uint64_t sys_write_to_screen(const char *buf, unsigned int count) {
	return sys_write(get_current_output(),buf,count);			// no requiere de la especificacion de a que pantalla escribir 
}