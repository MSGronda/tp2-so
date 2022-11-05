// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <memoryManager.h>

// en vez de retornar la el void *, nos pasa una posicion de memoria y se lo ponemos ahi
// para no tener que cambiar el tipo de retorno de todas las syscalls
uint64_t sys_alloc(uint64_t len) {
	return (uint64_t) mm_malloc(len);
}