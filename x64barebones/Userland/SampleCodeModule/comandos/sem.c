// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../include/comandos.h"
#include "../include/syscalls.h"
#include "../include/data_types.h"



void print_blocked_processes(unsigned int * blocked_pids, unsigned int amount){
	puts("\nBlocked processes: ");

	int len;
	char buffer[10] = {0};

	for(int i=0; i<amount; i++){
		print("     -Pid: ", 11);
		len = num_to_string(blocked_pids[i], buffer);
		print( buffer, len);
		print("\n",1);
	}
}

void sem(){
	
	semaphore_info * info = malloc(20 * sizeof(semaphore_info));
	if(info == NULL) {
		puts("No more memory");
		return;
	}

	uint64_t amount =  sys_semaphore_info(info);

	puts("-=-=-=-=-= Sem Info =-=-=-=-=-");

	int len;
	char buffer[20] = {0};
	for(int i=0; i<amount; i++){
		print("Sem Id: ",8);
		len = num_to_string(info[i].id, buffer);
		print( buffer, len);

		print(" | Value: ",10);

		len = num_to_string(info[i].value, buffer);
		print( buffer, len);

		print_blocked_processes(info[i].blocked_pids, info[i].num_blocked);
		puts("------------------------------");
	}



	free(info);
}