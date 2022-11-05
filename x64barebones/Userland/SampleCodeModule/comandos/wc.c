// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
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
	int len, count = 0;


	len = sys_read(buffer, SIZE);

	while(len != EOF){
		count += count_new_line(buffer, len);
		len = sys_read(buffer, SIZE);
	}

	num_to_string(count,buffer2);

	print("\nLine count: ",14);
	puts(buffer2);

}