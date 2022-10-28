#include <io.h>
#include <keyboard.h>
#include <video.h>
#include <multitasking.h>

/* Decides how to proceed depending on where to read */
unsigned int readDispatcher(unsigned int fd, char * buf, unsigned int count) 
{
	if(fd == STDIN) {										// Eligimos posicion de donde leer. Tambien lo podriamos hacer con una funcion/tabla
		while( !checkIfAvailableKey()){
			forceTimerTick();					// Se bloquea
		}
		return consume_kb_buffer(buf,count);		// Si el key buffer no esta vacio, primero tengo que consumirlo
	}

	// The rest of the FDs are considered pipe IDs
	read_from_pipe(fd, buf, count);
	return count;
}