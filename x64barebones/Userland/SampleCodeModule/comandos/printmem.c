#include "../include/comandos.h"
#include "../include/syscalls.h"

#define INVALID_POS 0xDEAD

void printmem(char ** args)
{
    if(!isNum(args[1])) {                                            // recibe un string que puede o no ser un numero
        puts("Invalid argument!\nArgument must be number!");
        return;
    }
    uint64_t position = atoi(args[1]);


    char buffer[BUFFER_LENGTH];

    if(sys_printmem(position, buffer) == INVALID_POS){
        puts("Invalid memory address!");
        puts("Valid memory address range: [ 4,194,304d - 34,359,738,367d )");
    }
    else
        puts(buffer);
}
