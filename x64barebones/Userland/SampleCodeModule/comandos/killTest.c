// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../include/comandos.h"
#include "../include/syscalls.h"

void killTest(){
    sys_alloc(50);
    sys_alloc(50);
    sys_alloc(50);
    sys_alloc(50);
    sys_alloc(50);
    sys_alloc(50);
    sys_alloc(50);
    sys_alloc(50);
    sys_alloc(50);
    sys_alloc(50);
    sys_alloc(50);
    sys_alloc(50);
}