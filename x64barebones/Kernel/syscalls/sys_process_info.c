// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <multitasking.h>
#include <data_types.h>
#include <syscalls.h>

uint64_t sys_process_info(process_info * info)
{
	return get_process_info(info);
}
