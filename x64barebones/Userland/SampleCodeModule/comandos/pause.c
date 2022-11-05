// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../include/comandos.h"
#include "../include/syscalls.h"

void pause(char ** args){
	    if(!isNum(args[1])) { 
        puts("Invalid argument!\nArgument must be number!");
        return;
    }
    uint64_t pid = atoi(args[1]);
	sys_pause_process(pid);
}