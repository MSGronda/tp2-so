#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <stdint.h>
#include <syscalls.h>
#include <lib.h>

void default_exception_handler(const char * msg, uint64_t * registerDumpPos);
void exceptionDispatcher(int exception, uint64_t * registerDumpPos);

void invalid_opcode(uint64_t * registerDumpPos);
void zero_division(uint64_t * registerDumpPos);


#endif