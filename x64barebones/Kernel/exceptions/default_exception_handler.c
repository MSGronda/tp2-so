// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <exceptions.h>
#include <lib.h>
#include <multitasking.h>
#include <syscalls.h>


void default_exception_handler(const char * msg, uint64_t * registerDumpPos)
{
	int screen =  get_current_output() + 1;		// se le suma 1 pues la (screen + 1) es la misma screen pero en rojo.
	sys_write(screen, msg, str_len(msg));
	
	printRegisters(screen,registerDumpPos);		// imprimo valor de registros al causarse la exception

	removeCurrentTask();						// lo elimino del queue de tasks
}
