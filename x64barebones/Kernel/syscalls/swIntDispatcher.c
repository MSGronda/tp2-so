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
		case SYS_CLEAR_SCREEN:
			return sys_clear_screen();


		// Procesos
		case SYS_REGISTER_PROCESS:
			return sys_register_process(arg0, (uint8_t) arg1, (uint8_t) arg2, (char **) arg3);
		case SYS_REGISTER_CHILD_PROCESS:
			return sys_register_child_process(arg0, (uint8_t) arg1, (uint8_t) arg2, (char **) arg3);
		case SYS_WAIT_FOR_CHILDREN:
			return sys_wait_for_children();
		case SYS_PAUSE_PROCESS:
			return sys_pause_process((unsigned int) arg0);
		case SYS_KILL_PROCESS:
			return sys_kill_process((unsigned int) arg0);
		case SYS_RENOUNCE_CPU:
			return sys_renounce_cpu();
		case SYS_NICE:
			return sys_nice(arg0, arg1);
		case SYS_GET_PID:
			return sys_get_pid();
		case SYS_PROCESS_ALIVE:
			return sys_process_alive((unsigned int) arg0);
		case SYS_PROCESS_INFO:
			return sys_process_info((process_info *) arg0);

		// Semaphore
		case SYS_REGISTER_SEM:
			return sys_register_sem((unsigned int) arg0, (unsigned int) arg1);
		case SYS_WAIT_SEM:
			return sys_wait_sem((unsigned int) arg0);
		case SYS_SIGNAL_SEM:
			return sys_signal_sem((unsigned int) arg0);
		case SYS_DESTROY_SEM:
			return sys_destroy_sem((unsigned int) arg0);
		case SYS_SEMAPHORE_INFO:
			return sys_semaphore_info((semaphore_info *) arg0);
		case SYS_REGISTER_SEM_AVAILABLE:
			return sys_register_sem_available((unsigned int) arg0);

		// Pipes
		case SYS_REGISTER_PIPE:
				return sys_register_pipe((unsigned int) arg0);
		case SYS_WRITE_PIPE:
			return sys_write_pipe((unsigned int) arg0, (char *)arg1, (unsigned int) arg2);
		case SYS_READ_PIPE:
			return sys_read_pipe((unsigned int) arg0, (char *)arg1, (unsigned int) arg2);
		case SYS_DESTROY_PIPE:
			return sys_destroy_pipe((unsigned int) arg0);
		case SYS_REGISTER_PIPE_AVAILABLE:
			return sys_register_pipe_available();
		case SYS_PIPE_INFO:
			return sys_pipe_info((pipes_info * )arg0);

		// MM
		case SYS_ALLOC:
			return sys_alloc(arg0);
		case SYS_FREE:
			return sys_free( (void*) arg0);

		// Otros
		case SYS_RTC:
			return sys_rtc((unsigned int) arg0);
		case SYS_MM_STATUS:
			return sys_mm_status((uint64_t *) arg0);

		default:
			return INVALID_SYS_CALL;
	}
}
