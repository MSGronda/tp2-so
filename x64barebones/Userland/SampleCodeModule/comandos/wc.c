#include "../include/comandos.h"
#include "../include/syscalls.h"

#define SIZE 100

int count_new_line(char * buff, int length){
	int count = 0;
	for(int i=0; i<length; i++){
		if(buff[i] == '\n'){
			count++;
		}
	}
	return count;
}


void wc(){
	char buffer[SIZE] = {0};
	char buffer2[SIZE] = {0};
	int len;


	len = sys_read(buffer, SIZE);

	int count = count_new_line(buffer, len);

	num_to_string(count,buffer2);

	puts(buffer2);

}