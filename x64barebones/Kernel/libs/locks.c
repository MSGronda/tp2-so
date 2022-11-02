#include <locks.h>


void lock(unsigned int * lock){
	while(_xchg(lock, 1) != 0);
}


void unlock(unsigned int * lock){
	_xchg(lock,0);
}