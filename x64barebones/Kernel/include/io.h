#ifndef IO_H_
#define IO_H_

// Entrada estandar
#define STDIN 1

#include <stdint.h>
#include <keyboard.h>
#include <video.h>
#include <multitasking.h>
#include <video.h>

/**
 * @brief   Decides how to proceed depending on which screen to write
 * 
 * @param   fd Screen to write
 * @param   buf String to be written
 * @param   count Length of buf
 * 
 * @return  Bytes written
*/
int writeDispatcher(unsigned int fd, const char * buf, unsigned int count);

/**
 * @brief   Decides how to proceed depending on which screen is to be read
 * 
 * @param   fd Screen to read
 * @param   buf Buffer to leave answer
 * @param   count Maximum amount of bytes to read
*/
int readDispatcher(unsigned int fd, char * buf, unsigned int count);

#endif