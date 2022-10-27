#include "../include/comandos.h"


#define SIZE 100

void cat(){
	char buffer[SIZE] = {0};
	int len;

	while(1){
		read_line(buffer, 10);
		print(buffer, 10);
	}	
}