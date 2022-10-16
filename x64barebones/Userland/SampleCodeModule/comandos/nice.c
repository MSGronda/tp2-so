#include "../include/comandos.h"
#include "../include/syscalls.h"

void nice(char ** args){
    if(!isNum(args[1]) && !isNum(args[2])) { 
        puts("Invalid argument!\nArguments must be numbers!");
        return;
    }
    unsigned int pid = atoi(args[1]);
    int delta = atosi(args[2]);
	sys_nice(pid, delta);
}