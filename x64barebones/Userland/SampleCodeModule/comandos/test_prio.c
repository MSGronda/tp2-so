#include "../include/comandos.h"
#include "../include/test_util.h"
#include "../include/syscalls.h"

#define MINOR_WAIT 1000000 // TODO: Change this value to prevent a process from flooding the screen
#define WAIT      50000000 // TODO: Change this value to make the wait long enough to see theese processes beeing run at least twice

#define TOTAL_PROCESSES 3
#define LOWEST 0
#define MEDIUM 2
#define HIGHEST 4

int prio[TOTAL_PROCESSES] = {LOWEST, MEDIUM,  HIGHEST};

void test_prio(){
  uint8_t pids[TOTAL_PROCESSES];
  uint64_t i;

  for(i = 0; i < TOTAL_PROCESSES; i++)
    pids[i] = (uint8_t) sys_register_process((uint64_t) &endless_loop_print, 1,1, NULL);

  bussy_wait(WAIT);
  puts("\nCHANGING PRIORITIES...");

  for(i = 0; i < TOTAL_PROCESSES; i++)
    sys_nice(pids[i], prio[i]);

  bussy_wait(WAIT);

  puts("\nBLOCKING...");

  for(i = 0; i < TOTAL_PROCESSES; i++)
    sys_pause_process(pids[i]);

  puts("CHANGING PRIORITIES WHILE BLOCKED...");

  for(i = 0; i < TOTAL_PROCESSES; i++)
    sys_nice(pids[i], MEDIUM);

  puts("UNBLOCKING...");

  for(i = 0; i < TOTAL_PROCESSES; i++)
    sys_pause_process(pids[i]);

  bussy_wait(WAIT);
  puts("\nKILLING...\n");

  for(i = 0; i < TOTAL_PROCESSES; i++)
    sys_kill_process(pids[i]);
}
