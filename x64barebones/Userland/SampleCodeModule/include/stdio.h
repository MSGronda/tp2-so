#ifndef _STDIO_H
#define _STDIO_H

/*--------  DEPENDENCIES --------*/
#include "syscalls.h"
#include "stdlib.h"

/* --- CONSTANTS  --- */
#define LEFT_SCREEN 3
#define RIGHT_SCREEN 5
#define NORMAL_SCREEN 1
#define BACKGROUND 0
#define STDIN 1

#define EOF -1

void print(char * string, int length);

/**
 * @brief   Prints a line ending with \n to corresponding screen
 * 
 * @param   string NULL terminated string
*/
void puts(char * string);

/**
 * @param   string NULL terminated string
*/
void printl(char * string);

/**
 * @brief   Reads length bytes from STDIN
*/
int read_line(char * buf, int length);

char getchar();

void clear_screen();

unsigned int consume_buffer(char * buffer, int length);

char getchar();

void putchar(char c);

#endif
