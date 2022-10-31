#ifndef IO_H_
#define IO_H_

// Entrada estandar
#define STDIN 1

#include <stdint.h>



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