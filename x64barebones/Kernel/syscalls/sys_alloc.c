#include <memoryManager.h>

// en vez de retornar la el void *, nos pasa una posicion de memoria y se lo ponemos ahi
// para no tener que cambiar el tipo de retorno de todas las syscalls
unsigned int sys_alloc(void ** ptr, uint64_t len) {
	void * resp = mm_malloc(len);

	*(ptr) = resp;

	return resp!=NULL;	
}