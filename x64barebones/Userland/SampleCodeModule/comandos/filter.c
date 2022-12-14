// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../include/comandos.h"
#include "../include/syscalls.h"

#define SIZE 20

int removeVocals(char * buf, int length){
	int i=0;
	for(int j=0; j<length; j++){
		while( j<length &&( (buf[j] == 'a' || buf[j] == 'e' || buf[j] == 'i' 
					|| buf[j] == 'o' || buf[j] == 'u') || (buf[j] == 'A' || buf[j] == 'E' || buf[j] == 'I' 
					|| buf[j] == 'O' || buf[j] == 'U'))){
			j++;
		}
		if(j<length){
			buf[i] = buf[j];
			i++;
		}
	}
	buf[i] = 0;
	return i;
}


void filter(){
	char buffer[SIZE] = {0};
	int len;

	while(1){
		len = sys_read(buffer, 1);

		if(len == EOF){
			return;
		}

		int len2 = removeVocals(buffer, len);

		print(buffer, len2);
	}
}