 /*
 *   interrupts.h
 *
 *  Created on: Apr 18, 2010
 *      Author: anizzomc
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include <idtLoader.h>
#include <stdint.h>

/* IRQ HANDLERS */
void _irq00Handler();
void _irq01Handler();
void _irq02Handler();
void _irq03Handler();
void _irq04Handler();
void _irq05Handler();

/* EXCEPTION HANDLERS */
void _exception0Handler();
void _exception6Handler();

/* ASM */
void _cli();
void _sti();
void _hlt();

/* PIC */
void picMasterMask(uint8_t mask);
void picSlaveMask(uint8_t mask);

/* Halts cpu */
void haltcpu();


/*
 * < forceNextTask >
 * ----------------------------------------------------
 *  Description: used after sys_pause and sys_kill to force 
 *  the next task to be executed
 */
void forceNextTask(uint64_t rsp, uint64_t ss);
void forceCurrentTask();

/*
 * < _swIntHandler >
 * ----------------------------------------------------
 *  Description: Converts arguments from an ASM-style to a 
 *  C-style for them to be used in the swIntDispatcher
 */
void _swIntHandler();


#endif /* INTERRUPTS_H_ */
