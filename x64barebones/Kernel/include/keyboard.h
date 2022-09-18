#ifndef	_KEYBOARD_H
#define _KEYBOARD_H

/*--------  DEPENDENCIES --------*/
#include <stdint.h>
#include <syscalls.h>

/* --- CONSTANTS  --- */
#define NO_KEY 0
#define VALID_KEY 1
#define DELETE_KEY 2
#define BUFFER_FULL 3
#define UNMAPPED 4

// --- Caracteres especiales ---
#define ESCAPE_KEY 27
#define F1_KEY 17
#define F2_KEY 18
#define F3_KEY 19
#define F5_SCAN_CODE 0x3F


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
char keyboard_handler();


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

char checkIfAvailableKey();

#endif
