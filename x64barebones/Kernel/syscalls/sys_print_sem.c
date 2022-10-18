#include <semaphore.h>
#include <syscalls.h>


unsigned int sys_print_sem(){
	 print_sem();
	 return 1;
}