#include "../include/comandos.h"
#include "../include/syscalls.h"

#define INVALID_POS 0xDEAD

void printmem(char * arg)
{
    if(!isNum(arg)) {                                            // recibe un string que puede o no ser un numero
        puts("Invalid argument!\nArgument must be number!");
        return;
    }
    uint64_t position = atoi(arg);


    char buffer[BUFFER_LENGTH];

    if(sys_printmem(position, buffer) == INVALID_POS){
        puts("Invalid memory address!");
        puts("Valid memory address range: [ 4,194,304d - 34,359,738,367d )");
    }
    else
        puts(buffer);
}
