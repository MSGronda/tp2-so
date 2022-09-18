#ifndef _STDIO_H
#define _STDIO_H

/*--------  DEPENDENCIES --------*/
#include "syscalls.h"
#include "stdlib.h"

/* --- CONSTANTS  --- */
#define LEFT_SCREEN 3
#define RIGHT_SCREEN 5
#define NORMAL_SCREEN 1

// --- Caracteres especiales ---
#define PAUSE_NORMAL_SCREEN 17
#define PAUSE_LEFT_SCREEN  18
#define PAUSE_RIGHT_SCREEN 19
#define ESCAPE_KEY 27

/*
 * << print >>
 * ----------------------------------------------------------------------
 * Descripcion: Prints to corresponding screen
 * ----------------------------------------------------------------------
 * Recibe: 
 *      (char*) string to print
 *      (int) length of string
 * Devuelve: -- 
 */
void print(char * string, int length);

/*
 * << puts >>
 * ----------------------------------------------------------------------
 * Descripcion: Prints a line ending with \n to corresponding screen
 * ----------------------------------------------------------------------
 * Recibe: 
 *      (char*) string to print
 * Devuelve: -- 
 */
void puts(char * string);

/*
 * << read_line >>
 * ----------------------------------------------------------------------
 * Descripcion: Reads line from STDIN
 * ----------------------------------------------------------------------
 * Recibe: 
 *      (char*) buffer to leave answer
 *      (int) size of bytes to read
 * Devuelve: -- 
 */
void read_line(char * buf, int length);

/*
 * << getchar >>
 * ----------------------------------------------------------------------
 * Descripcion: Gets character from STDIN
 * ----------------------------------------------------------------------
 * Recibe: --
 * Devuelve: -- 
 *      (char) character read
 */
char getchar();

/*
 * << clear_screen >>
 * ----------------------------------------------------------------------
 * Descripcion: Clears corresponding screen
 */
void clear_screen();

/*
 * << consume_buffer >>
 * ----------------------------------------------------------------------
 * Descripcion: If there is something in buffer it consumes it
 * ----------------------------------------------------------------------
 * Recibe: 
 *      (char*) buffer to consume
 *      (int) max length expected to be consumed
 * Devuelve: 
 *      (uint) amount consumed
 */
unsigned int consume_buffer(char * buffer, int length);
char getchar();
void putchar(char c);


#endif
