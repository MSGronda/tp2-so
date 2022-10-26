#include <syscalls.h>

#define TOTAL_REGISTERS 15

static uint64_t inforegData[TOTAL_REGISTERS] = {0};


void saveInfoReg(uint64_t * regDumpPos)
{
	for(int i=0; i<TOTAL_REGISTERS; i++)
		inforegData[i] = regDumpPos[i];
}


uint64_t sys_inforeg(uint64_t * buffer) // recibo buffer y le escribo, NUNCA devuelvo puntero a algo que esta en kernel
{			 
	for(int i=0; i<TOTAL_REGISTERS; i++)
		buffer[i] = inforegData[i];

	return 1;
}