// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <keyboard.h>
#include <multitasking.h>
#include <video.h>

// Variables estaticas
static uint8_t * defaultVideoPos = (uint8_t*)0xB8000;

static unsigned int currentVideoPosOffset = START_LEFT;
static unsigned int currentVideoPosLeftOffset = START_LEFT;
static unsigned int currentVideoPosRightOffset = START_RIGHT;


/* Writes to given screen */
unsigned int write(const char * buf, char format, unsigned int count, unsigned int * offset, unsigned int start,  unsigned int length , unsigned int step)
{
	int i;

	for(i=0; i<count; i++) {

		if(*offset >= (SCREEN_HEIGHT-1) * SCREEN_WIDTH + length + start) {	// llego al final de pantalla, tengo que hacer scroll up
			scrollUp(start, length, step);
			*offset = (SCREEN_HEIGHT-1) * SCREEN_WIDTH + start;
		}
		
		char c = buf[i];

		//------ CARACTERES EPECIALES ------	
		if(c == '\n') {		
			int aux = length - (*offset % length);			// avanzo a la proxima linea en pantalla
			*offset += aux + step;
		}
		else if(c == '\b')				
			deleteKey(offset, start, length, step);		
		

		//------ CARACTERES NORMALES ------	
		else {	
			*(defaultVideoPos + (*offset)++) = c;			// escribo letra y formato
			*(defaultVideoPos + (*offset)++) = format;

			if(*offset % length  == 0)						// salto a new line si llego a fin 
                *offset += step;
		}

	}
	return i;
}

unsigned int * normalOffset(){
	return &currentVideoPosOffset;
}
unsigned int * leftOffset(){
	return &currentVideoPosLeftOffset;
}

unsigned int * rightOffset(){
	return &currentVideoPosRightOffset;
}

void resetRight(){
	currentVideoPosRightOffset = 0;		// se resetean las split screen
}

void resetLeft(){
	currentVideoPosLeftOffset = 0;
}

void resetNormal(){
	currentVideoPosOffset = 0;		// se resetean el normal mode
}

/* Clears given screen */
void clearScreen(int start, int length, int step) 
{
	for(int i=start ; i < SCREEN_WIDTH * SCREEN_HEIGHT - start; ) {
		*(defaultVideoPos + i++) = ' ';
		*(defaultVideoPos + i++) = STDOUT_COLOR;

		if( i % length  == 0)											// salto a nueva linea, si llegue a fin
			i += step;
	}
}

/* Decides how to proceed depending on screen to clear */
unsigned int clearScreenDispatcher() 
{
	int screen = get_current_output();
	switch(screen) {
		case STDOUT_LEFT:
			currentVideoPosOffset = currentVideoPosLeftOffset = START_LEFT;		// se resetan las pantallas
			clearScreen(START_LEFT, SPLIT_MODE_LENGTH, SPLIT_MODE_STEP);
			break;

		case STDOUT_RIGHT:
			currentVideoPosOffset = START_LEFT;		// se resetan las pantallas
			currentVideoPosRightOffset = START_RIGHT;
			clearScreen(START_RIGHT, SPLIT_MODE_LENGTH, SPLIT_MODE_STEP);
			break;

		case STDOUT:
			currentVideoPosOffset = currentVideoPosLeftOffset = START_LEFT;		// se resetan las pantallas
			currentVideoPosRightOffset = START_RIGHT;
			clearScreen(START_LEFT, NORMAL_MODE_LENGTH, NORMAL_MODE_STEP);
	}

	return 0;
}


/* Gets the offset of a given fd */
unsigned int getFdOffSet(unsigned int fd)
{
	switch(fd) {
		case STDOUT_LEFT:
			return currentVideoPosLeftOffset;

		case STDOUT_RIGHT:
			return currentVideoPosRightOffset;

		case STDOUT:
		default:
			return currentVideoPosOffset;
	}
}


void deleteKey(unsigned int * offset, unsigned int start,  unsigned int length , unsigned int step)
{
	if(*offset == start)			// si llegue al principio de la pantalla, no puedo ir para atras
		return;						

	if( ((*offset - 2) % SCREEN_WIDTH) < start || ((*offset - 2) % SCREEN_WIDTH) > start + length) // si estamos por fuera de los limites, entro devuelta pero una linea arriba
		*offset -= step;			
	
	*offset -= 2;					// voy uno para atras
	*(defaultVideoPos + *offset) = ' ';	
}


void scrollUp(int start, int length, int step)
{
	
	for(int i=start, j = SCREEN_WIDTH + start; j < SCREEN_WIDTH * SCREEN_HEIGHT ;){				// Copio todo uno para arriba 1 fila
		*(defaultVideoPos + i++) = *(defaultVideoPos + j++); 

		if( i % length  == 0){											// salto a nueva linea, si llegue a fin
			i += step;
			j += step;
		}				
	}

	for(int i=(SCREEN_HEIGHT-1) * SCREEN_WIDTH + start; 				// elimino la ultima linea
		i < (SCREEN_HEIGHT-1) * SCREEN_WIDTH + length + start; i+=2)
		*(defaultVideoPos+i)=' ';
}