#include "../include/comandos.h"

void loop(){
	int len, pid = sys_get_pid();
	char buffer[20] = {0};

	len = num_to_string(pid, buffer);

	while(1){
		for(int i=0; i<5000000; i++);
		print(" Hello, I am process n",22);
		print(buffer,len);
		print("\n",1);
	}	
}