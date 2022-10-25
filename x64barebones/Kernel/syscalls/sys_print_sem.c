#include <semaphore.h>
#include <syscalls.h>


uint64_t sys_print_sem(){
	 print_sem();
	 return 1;
}