#include "../include/comandos.h"
#include "../include/syscalls.h"

#define SIZE 20

void cat(){
	char buffer[SIZE] = {0};
	int len;

	while(1){
		len = sys_read(buffer, 1);
		print(buffer, len);
	}	
}