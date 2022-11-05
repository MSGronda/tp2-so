// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <exceptions.h>

#define INVALID_OP_CODE_ERR_MSG "Se produjo una excepcion por codigo de operacion invalida!\n"

void invalid_opcode(uint64_t * registerDumpPos) {
	default_exception_handler(INVALID_OP_CODE_ERR_MSG, registerDumpPos);
}