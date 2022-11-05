// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <locks.h>


void lock(unsigned int * lock){
	while(_xchg(lock, 1) != 0);
}


void unlock(unsigned int * lock){
	_xchg(lock,0);
}