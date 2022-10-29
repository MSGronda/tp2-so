#include "../include/comandos.h"

void loop(){
	int len, pid = sys_get_pid();
	char buffer[50] = " Hello, I am process n";
	len = num_to_string(pid, buffer + 22);
	buffer[22 + len] = '\n';
	buffer[22 + len + 1] = 0;

	while(1){
		for(int i=0; i<5000000; i++);
		print(buffer, 22 + len + 1);
	}	
}