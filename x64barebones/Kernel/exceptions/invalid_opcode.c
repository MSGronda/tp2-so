#include <exceptions.h>

#define INVALID_OP_CODE_ERR_MSG "Se produjo una excepcion por codigo de operacion invalida!\n"

void invalid_opcode(uint64_t * registerDumpPos) {
	default_exception_handler(INVALID_OP_CODE_ERR_MSG, registerDumpPos);
}