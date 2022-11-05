// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <exceptions.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OP_CODE 6

void exceptionDispatcher(int exception, uint64_t * registerDumpPos) 
{
	switch(exception) {
		case ZERO_EXCEPTION_ID:
			zero_division(registerDumpPos);
			break;

		case INVALID_OP_CODE:
			invalid_opcode(registerDumpPos);
			break;

		default:
			return;		// nunca deberia entrar aca
	}
}