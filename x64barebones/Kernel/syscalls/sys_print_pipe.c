#include <pipes.h>
#include <syscalls.h>

uint64_t sys_print_pipe(){
	 print_pipe();
	 return 1;
}