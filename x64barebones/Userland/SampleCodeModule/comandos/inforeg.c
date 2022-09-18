#include "../include/comandos.h"

extern void getRegisters(uint64_t * buffer);

#define TOTAL_REGISTERS 15
#define REGISTER_LENGTH 16

static char * registerOrder[] = {
    "RAX: ","RBX: ","RCX: ","RDX: ",
    "RBP: ","RSI: ","RDI: ","R8: ", 
    "R9: ","R10: ","R11: ","R12: ",
    "R13: ","R14: ","R15: " 
};

void inforeg()
{
    char stringBuffer[BUFF_SIZE];
    uint64_t regBuffer[TOTAL_REGISTERS];

    sys_inforeg(regBuffer);        // meto valor de registros en buffer

    for(int i=0; i<TOTAL_REGISTERS ; i++) {
        hex_to_string(regBuffer[i], stringBuffer, REGISTER_LENGTH);                  // Esto probablemente este roto
        print(registerOrder[i], strlen(registerOrder[i]));
        puts(stringBuffer);
    }
}