#include <io.h>
#include <keyboard.h>
#include <video.h>


/* - - - Screen write through - - - */

// Handling printing to screen directly during keyboard interruption 
// Which allows interruption to be momentary and not continuos
static uint8_t screenWriteThrough = 0;
static unsigned int initialPos;					// position on screen
static unsigned int finished = 0;				// denotes if there has been a new line
static unsigned int fd;

// IDEA: en vez de un initial pos, tene un counter


void screen_write_through(char c){
	if(screenWriteThrough){
		if(c!='\b') {
			writeDispatcher(fd,&c, 1);

			if(c=='\n')
				finished = 1;

		}
		else{
			if(getFdOffSet(fd) > initialPos) {  // no dejo que borre lo que ya habia
				writeDispatcher(fd,"\b",1);
			}
		}
	}
}

int * enable_screen_write_through(unsigned int screen_fd){
	screenWriteThrough = 1;
	initialPos = getFdOffSet(fd);
	fd = screen_fd;
	finished = 0;
	return &finished;
}

void disable_screen_write_through(){
	screenWriteThrough = 0;
	initialPos = 0;
	fd = 0;
}




/* - - - IO - - - */

unsigned int read_stdin(unsigned int fd, char * buf, unsigned int count) 
{
	_sti();
	int * finished = enable_screen_write_through(fd);

	while(*finished == 0){
		//
	}

	disable_screen_write_through();

	int j=0;
	for(; checkIfAvailableKey();j++)				// consumo el buffer de una, hasta el \n o fin de caracteres
		buf[j] = get_key();

	return j;
}


/* Decides how to proceed depending on where to read */
unsigned int readDispatcher(unsigned int fd, char * buf, unsigned int count) 
{
	switch(fd) {										// Eligimos posicion de donde leer. Tambien lo podriamos hacer con una funcion/tabla
		case STDIN:
		case STDIN_LEFT:
		case STDIN_RIGHT:
			if(checkIfAvailableKey())
				return consume_kb_buffer(buf,count);		// Si el key buffer no esta vacio, primero tengo que consumirlo
			return read_stdin(fd, buf, count);				// El buffer esta vacio, puedo leer de pantalla

		default:
			return 0;	// Seria error?
	}
}