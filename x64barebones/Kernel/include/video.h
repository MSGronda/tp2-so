#ifndef _VIDEO_H
#define _VIDEO_H

/* --- DEPENDENCIES --- */
#include <syscalls.h>


/* --- CONSTANTS --- */
#define BACKGROUND 0

// Normal mode
#define STDOUT 1
#define STDERR 2

// Split screen
#define STDOUT_LEFT 3
#define STDOUT_RIGHT 5
#define STDERR_LEFT 4
#define STDERR_RIGHT 6

// Colores 
#define STDOUT_COLOR 7
#define STDERR_COLOR 4

// Columna de comienzo en pantalla
#define START_LEFT 0
#define START_RIGHT 80

// Dimensiones de pantalla
#define NORMAL_MODE_LENGTH 160
#define SPLIT_MODE_LENGTH 80

#define SCREEN_HEIGHT 25
#define SCREEN_WIDTH 160

// Salto de pantalla
#define NORMAL_MODE_STEP 0
#define SPLIT_MODE_STEP 80

unsigned int * normalOffset();
unsigned int * leftOffset();
unsigned int * rightOffset();

void resetNormal();
void resetLeft();
void resetRight();

/*
 * << write >>
 * ----------------------------------------------------------------------
 * Descripcion: Writes to corresponding screen
 * ----------------------------------------------------------------------
 * Recibe: 
 *      [buf] = string to be written
 * 		[format] = background color
 *      [count] = number of letters to be written
 *		[offset] = current cursor position
 * 		[start] = initial column of screen
 *		[length] = length of screen where we print
 *		[step] = number of positions to jump after we reach end of screen
 * Devuelve: 
 *      (uint) bytes written
 */
unsigned int write(const char * buf, char format, unsigned int count, 
					unsigned int * offset, unsigned int start,  unsigned int length , unsigned int step);


/*
 * << clearScreen >>
 * ----------------------------------------------------------------------
 * Descripcion: Writes to corresponding screen
 * ----------------------------------------------------------------------
 * Recibe: 
 *      [start] = initial column of screen
 *      [length] = length of screen where we print
 *      [step] = number of positions to jump after we reach end of screen
 * Devuelve: --
 */
void clearScreen(int start, int length, int step);

/*
 * << clearScreenDispatcher >>
 * ----------------------------------------------------------------------
 * Descripcion: Decides which screen to clear
 * ----------------------------------------------------------------------
 * Recibe: --
 * Devuelve: --
 */
unsigned int clearScreenDispatcher();

/*
 * << getFdOffset >>
 * ----------------------------------------------------------------------
 * Descripcion: Gets the offset of a given [fd]
 * ----------------------------------------------------------------------
 * Recibe: 
 *      [fd] = screen
 * Devuelve: 
 *      (uint) offset to write on screen
 */
unsigned int getFdOffSet(unsigned int fd);



/* ========================= SPECIAL KEYS ============================ */
/*
 * << deleteKey >>
 * ----------------------------------------------------------------------
 * Descripcion: DeleteKey functionality
 * ----------------------------------------------------------------------
 * Recibe: 
 *		[offset] = current cursor position
 * 		[start] = initial column of screen (Eg: normal=izq=0, right= 80)
 *		[length] = length of screen where we print
 *		[step] = number of positions to jump after we reach end of screen
 * Devuelve: --
 */
void deleteKey(unsigned int * offset, unsigned int start,  unsigned int length , unsigned int step);

/*
 * << scrollUp >>
 * ----------------------------------------------------------------------
 * Descripcion: ScrollUp functionality
 * ----------------------------------------------------------------------
 * Recibe: 
 * 		[start] = initial column of screen (Eg: normal=izq=0, right= 80)
 *		[length] = length of screen where we print
 *		[step] = number of positions to jump after we reach end of screen
 * Devuelve: --
 */
void scrollUp(int start, int length, int step);




#endif