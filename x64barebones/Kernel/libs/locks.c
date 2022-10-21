#include <locks.h>


void lock(int * lock){
	while(_xchg(lock, 1) != 0);
}


void unlock(int * lock){
	_xchg(lock,0);
}