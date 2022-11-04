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

/**
 * @brief	Writes to corresponding screen
 * 
 * @param	buf String to be written
 * @param 	format Background color
 * @param 	count Number of letters to write
 * @param	offset Current cursos position
 * @param	start Initial column of screen
 * @param	legth Length of screen where we print
 * @param  	step Number of positions (x-axis) to jump after we reach the end of the screen
 * 
 * @return 	Bytes written
*/
unsigned int write(const char * buf, char format, unsigned int count, 
					unsigned int * offset, unsigned int start,  unsigned int length , unsigned int step);


/**
 * @param	start Initial column of screen
 * @param 	length Length of screen to clear
 * @param	step Number of positions (x-axis) to jump after we reach end of screen 
*/
void clearScreen(int start, int length, int step);

/**
 * @brief 	Decides which screen to clear
*/
unsigned int clearScreenDispatcher();

unsigned int getFdOffSet(unsigned int fd);


/* ========================= SPECIAL KEYS ============================ */
/**
 * @brief	DeleteKey functionality
 * 
 * @param 	offset Current cursor position
 * @param	start Initial column of screen
 * @param	length Length of the current screen
 * @param	step Number of positions (x-axis) to jump after end of screen
*/
void deleteKey(unsigned int * offset, unsigned int start,  unsigned int length , unsigned int step);

/**
 * @brief	ScrollUp functionality
 * 
 * @param	start Initial column of screen
 * @param	length Length of the current screen
 * @param	step Number of positions (x-axis) to jump after end of screen
*/
void scrollUp(int start, int length, int step);

#endif