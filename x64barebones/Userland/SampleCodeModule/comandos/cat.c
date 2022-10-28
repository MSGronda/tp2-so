#include "../include/comandos.h"


#define SIZE 100

void cat(){
	char buffer[SIZE] = {0};
	int len;

	while(1){
		len = sys_read(buffer, 10);
		print(buffer, len);
	}	
}