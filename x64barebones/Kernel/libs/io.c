#include <io.h>
#include <keyboard.h>
#include <video.h>
#include <multitasking.h>

#define MAX_WRTHG 20

/* - - - Screen write through - - - */

// Handling printing to screen directly during keyboard interruption 
// Which allows interruption to be momentary and not continuos
static uint8_t screenWriteThrough = 0;
static unsigned int counter = 0;
static unsigned int fd;
static unsigned int pid;
static unsigned int maxConsume;
static char * buffer;

void enable_screen_write_through(unsigned int screen_fd, char * buf, unsigned int count){
	counter = 0;
	pid = get_current_pid();
	fd = screen_fd;
	screenWriteThrough = 1;
	buffer = buf;
	maxConsume = count;
}

void disable_screen_write_through(){
	int process_pid = pid;
	counter = 0;
	pid = 0;
	fd = 0;
	screenWriteThrough = 0;
	alter_process_state(process_pid, ACTIVE_PROCESS);

	for(int j=0; checkIfAvailableKey() && j<maxConsume;j++)				// consumo el buffer de una, hasta el \n o fin de caracteres
		buffer[j] = get_key();

	buffer = 0;
	maxConsume = 0;
}

void screen_write_through(char c){
	if(screenWriteThrough){
		if(c!='\b') {
			writeDispatcher(fd,&c, 1);
			counter++;

			if(c=='\n')
				disable_screen_write_through();
		}
		else{
			if(counter >0) {  // no dejo que borre lo que ya habia
				writeDispatcher(fd,"\b",1);
				counter--;
			}
		}
	}
}


/* - - - IO - - - */

unsigned int read_stdin(unsigned int fd, char * buf, unsigned int count, uint64_t rsp, uint64_t ss) 
{
	if(screenWriteThrough)
		return 0;				// only 1 process can read from screen at one time

	enable_screen_write_through(fd, buf, count);

	alter_process_state(pid, WAITING_FOR_INPUT);
	forceNextTask(rsp,ss);

	return 1;
}


/* Decides how to proceed depending on where to read */
unsigned int readDispatcher(unsigned int fd, char * buf, unsigned int count, uint64_t rsp, uint64_t ss) 
{
	switch(fd) {										// Eligimos posicion de donde leer. Tambien lo podriamos hacer con una funcion/tabla
		case STDIN:
		case STDIN_LEFT:
		case STDIN_RIGHT:
			if(checkIfAvailableKey())
				return consume_kb_buffer(buf,count);		// Si el key buffer no esta vacio, primero tengo que consumirlo
			return read_stdin(fd, buf, count,rsp,ss);				// El buffer esta vacio, puedo leer de pantalla

		default:
			return 0;	// Seria error?
	}
}