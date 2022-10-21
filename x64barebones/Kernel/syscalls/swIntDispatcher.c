#include <stdint.h>
#include <syscalls.h>

#define INVALID_SYS_CALL 255

//registros en asm:		rax		  rdi		 rsi	 rdx		r10		 r8			r9
//registros en c: 		rdi		  rsi		 rdx	 rcx		r8		 r9		   stack		// de derecha a izquierda se pasan a los registros
uint64_t swIntDispatcher(uint64_t mode, uint64_t arg0, uint64_t arg1, 
	uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5, uint64_t ss, uint64_t rsp) 
{
	switch (mode) {

		// IO
		case SYS_WRITE_TO_SCREEN:
			return sys_write_to_screen((const char *) arg0,(unsigned int) arg1);
		case SYS_READ_FROM_SCREEN:
			return sys_read_from_screen((char *) arg0, (unsigned int) arg1);
		case SYS_CONSUME_STDIN:
			return sys_consume_stdin((char *) arg0 , (unsigned int) arg1);
		case SYS_CLEAR_SCREEN:
			return sys_clear_screen();


		// Procesos
		case SYS_REGISTER_PROCESS:
			return sys_register_process(arg0, (int) arg1, arg2);
			
		case SYS_REGISTER_CHILD_PROCESS:
			return sys_register_child_process(arg0, (int) arg1, arg2);

		case SYS_WAIT_FOR_CHILDREN:
			return sys_wait_for_children(rsp, ss);

		case SYS_PAUSE_PROCESS:
			return sys_pause_process((unsigned int) arg0);

		case SYS_KILL_PROCESS:
			return sys_kill_process((unsigned int) arg0);

		case SYS_RENOUNCE_CPU:
			return sys_renounce_cpu(rsp, ss);

		case SYS_NICE:
			return sys_nice(arg0, arg1);

		case SYS_GET_PID:
			return sys_get_pid();

		// Semaphore
		case SYS_REGISTER_SEM:
			return sys_register_sem((unsigned int) arg0);
		case SYS_WAIT_SEM:
			return sys_wait_sem((unsigned int) arg0,  rsp,  ss);
		case SYS_SIGNAL_SEM:
			return sys_signal_sem((unsigned int) arg0);
		case SYS_PRINT_SEM:
			return sys_print_sem();

		// MM
		case SYS_ALLOC:
			return sys_alloc(arg0, arg1);

		case SYS_FREE:
			return sys_free(arg0);

		// Otros
		case SYS_RTC:
			return sys_rtc((unsigned int) arg0);

		case SYS_INFOREG:
			return sys_inforeg((uint64_t*) arg0);

		case SYS_PRINTMEM:
			return sys_printmem((uint64_t)arg0, (char *) arg1);

		case SYS_LIST_PROCESS:
			return sys_list_process();

		default:
			return INVALID_SYS_CALL;
	}
}
