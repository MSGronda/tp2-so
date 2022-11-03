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

/*
 * << keyboard_handler >>
 * ----------------------------------------------------------------------
 *  Descripcion: Handles keyboard functionality
 * ----------------------------------------------------------------------
 *  Recibe: --
 *  Devuelve:
 *      1 <=> wrote buffer
 *      0 <=> otherwise
 */
void keyboard_handler();


/*
 * << get_key >>
 * ----------------------------------------------------------------------
 * Descripcion: OBTAINS && CONSUMES pressed key
 * ----------------------------------------------------------------------
 * Recibe: --
 * Devuelve: 
 *      (char) pressedKey <=> was a mapped key and consumed it
 *      0 <=> otherwise
 */
char get_key();


/*
 * << peek_key >>
 * ----------------------------------------------------------------------
 * Descripcion: OBTAINS but DOES NOT CONSUME pressed key
 * ----------------------------------------------------------------------
 * Recibe: --
 * Devuelve:
 *      (char) pressedKey <=> was a mapped key
 *      0 <=> otherwise
 */
char peek_key();

/*
 * << consume_kb_buffer >>
 * ----------------------------------------------------------------------
 * Descripcion: Consumes keyboard buffer DUH
 * ----------------------------------------------------------------------
 * Recibe: --
 * Devuelve: 
 *      (uint) bytes consumed
 */
unsigned int consume_kb_buffer(char * buf, unsigned int count);

#endif
