// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../include/comandos.h"
#include "../include/syscalls.h"

#define SIZE 20

void cat(){
	char buffer[SIZE] = {0};
	int len;

	while(1){
		len = sys_read(buffer, 1);

		if(len == EOF){
			return;
		}
		
		print(buffer, len);
	}	
}