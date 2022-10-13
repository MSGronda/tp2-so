#include "../include/comandos.h"
#include "../include/syscalls.h"

void kill(char ** args){
	    if(!isNum(args[1])) { 
        puts("Invalid argument!\nArgument must be number!");
        return;
    }
    uint64_t pid = atoi(args[1]);
	sys_kill_process(pid);
}