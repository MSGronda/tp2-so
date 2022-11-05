// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../include/comandos.h"
#include "../include/syscalls.h"


void pipe(){

	pipes_info * info = malloc(20 * sizeof(pipes_info));
	if(info == NULL) {
		puts("No more memory");
		return;
	}

	int len;
	char buffer[20];

	uint64_t amount = sys_pipe_info(info);
	
	puts("-=-=-=-=-= Pipe Info =-=-=-=-=-");

	for(int i=0; i<amount; i++){

			print("Pipe Id: ",9);
			len = num_to_string(info[i].id, buffer);
			print( buffer, len);

			print(" | Usage: ",10);

			len = num_to_string(info[i].usage , buffer);
			print( buffer, len);

			printl("\n--Read semaphore--");
			print_blocked_processes(info[i].read_blocked_pids, info[i].read_num_blocked);

			print( "--Write semaphore--",19);
			print_blocked_processes(info[i].write_blocked_pids, info[i].write_num_blocked);

			puts("-------------------------------");

	}


	free(info);



}