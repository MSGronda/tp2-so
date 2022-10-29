#include "../include/comandos.h"
#include "../include/syscalls.h"

#define SIZE 20

int removeVocals(char * buf, int length){
	int i=0;
	for(int j=0; j<length; j++){
		while( j<length && (buf[j] == 'a' || buf[j] == 'e' || buf[j] == 'i' 
			|| buf[j] == 'o' || buf[j] == 'u')){
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
		len = sys_read(buffer, 10);

		int len2 = removeVocals(buffer, len);

		print(buffer, len2);
	}
}