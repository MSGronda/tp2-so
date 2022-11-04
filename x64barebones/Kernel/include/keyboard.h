#ifndef	_KEYBOARD_H
#define _KEYBOARD_H

/*--------  DEPENDENCIES --------*/
#include <stdint.h>
#include <syscalls.h>
#include <multitasking.h>
#include <lib.h>

/* --- CONSTANTS  --- */
#define NO_KEY 0
#define VALID_KEY 1
#define DELETE_KEY 2
#define BUFFER_FULL 3
#define UNMAPPED 4

void keyboard_handler();
char checkIfAvailableKey();

/**
 * @brief   OBTAINS and CONSUMES pressed key
 * 
 * @return  If pressed key is mapped, then pressed key
 *          Otherwise, 0
*/
char get_key();

/**
 * @brief   OBTAINS but DOES NOT CONSUME pressed key
 * 
 * @return  If pressed key is mapped, then pressed key
 *          Otherwise, 0
*/
char peek_key();

/**
 * @param   buf Buffer to leave answer
 * @param   count Maximum amount of bytes to consume
 * 
 * @return  Bytes consumed
 *         
*/
unsigned int consume_kb_buffer(char * buf, unsigned int count);

#endif
