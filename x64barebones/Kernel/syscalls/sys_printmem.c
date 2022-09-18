#include <lib.h>
#include <syscalls.h>

#define MAX_MEM_READ 16
#define BYTE_LENGTH 2
#define MAX_MEM_POS 0x7FFFFFFFF		/* F FFFF FFFFh tira page fault */
#define MIN_MEM_POS 0x400000		/* Aca arranca Userland */
#define INVALID_POS 0xDEAD

unsigned int sys_printmem(uint64_t position, char * buffer)
{
	if( !(position >= MIN_MEM_POS && position < MAX_MEM_POS) )		// restringimos tmb que no pueda leer memoria de kernel
		return INVALID_POS;

	uint64_t current;
	
	for(int i=0, k=0; i < MAX_MEM_READ; i++) {
		if(i!=0 && i%4==0)
			buffer[k++] = ' ';

       	current = *((uint8_t * )position + i);
        k += hex_to_string(current, buffer + k, BYTE_LENGTH);
	}

	return 0;
}