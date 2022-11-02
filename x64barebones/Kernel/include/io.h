#ifndef IO_H_
#define IO_H_

// Entrada estandar
#define STDIN 1

#include <stdint.h>
#include <keyboard.h>
#include <video.h>
#include <multitasking.h>
#include <video.h>

/*
 * << writeDispatcher >>
 * ----------------------------------------------------------------------
 * Descripcion: Decides how to proceed depending on screen to write
 * ----------------------------------------------------------------------
 * Recibe: 
 *      [fd] = screen to write
 *      [buf] = string to be written
 *      [count] = number of letters to be written
 * Devuelve: 
 *      0 <=> successful
 */
int writeDispatcher(unsigned int fd, const char * buf, unsigned int count);


/*
 * << readDispatcher >>
 * ----------------------------------------------------------------------
 * Descripcion: Decides how to proceed depending on screen
 * ----------------------------------------------------------------------
 * Recibe: 
 *      [fd] = screen
 *      [buf] = string to be leave answer
 *      [count] = number of letters to be read
 * Devuelve: 
 *      (uint) bytes read
 */
int readDispatcher(unsigned int fd, char * buf, unsigned int count);

#endif