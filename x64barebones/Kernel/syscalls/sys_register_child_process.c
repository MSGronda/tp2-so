#include <multitasking.h>
#include <syscalls.h>

unsigned int sys_register_child_process(uint64_t entryPoint, int screen, uint64_t arg0)
{
	if(screen != STDOUT && screen != STDOUT_LEFT && screen != STDOUT_RIGHT)			// si no es una pantalla valida, se rechaza el proceso.
		return INVALID_SCREEN;
	
	return add_child_task(entryPoint, screen, arg0);
}
