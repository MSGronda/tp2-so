#include "../include/test_util.h"
#include "../include/syscall.h"
#include "../include/stdio.h"

enum State {RUNNING, BLOCKED, KILLED};

typedef struct P_rq{
  int32_t pid;
  enum State state;
}p_rq;

void test_processes(char ** argv){
  uint8_t rq;
  uint8_t alive = 0;
  uint8_t action;
  uint64_t max_processes;

  if(argv[1] == NULL)
    return;

  if ((max_processes = satoi(argv[1])) <= 0){
     puts("Invalid argument! Please pass a number as the argument");
     return;
  }

  print("Max process: ",13);
  puts(argv[1]);

  p_rq p_rqs[max_processes];

  while (1){

    // Create max_processes processes
    for(rq = 0; rq < max_processes; rq++){
      p_rqs[rq].pid = sys_register_child_process((uint64_t) &endless_loop, 1, 1, NULL);

      if (p_rqs[rq].pid == -1){
        puts("test_processes: ERROR creating process");
        return;
      }else{
        p_rqs[rq].state = RUNNING;
        alive++;
      }
    }

    // Randomly kills, blocks or unblocks processes until every one has been killed
    while (alive > 0){

      for(rq = 0; rq < max_processes; rq++){
        action = GetUniform(100) % 2; 

        switch(action){
          case 0:
            if (p_rqs[rq].state == RUNNING || p_rqs[rq].state == BLOCKED){
              if (sys_kill_process(p_rqs[rq].pid) == -1){  
                puts("test_processes: ERROR killing process");
                return;
              }
              p_rqs[rq].state = KILLED; 
              alive--;
            }
            break;

          case 1:
            if (p_rqs[rq].state == RUNNING){
              if(sys_pause_process(p_rqs[rq].pid) == -1){
                puts("test_processes: ERROR blocking process");
                return;
              }
              p_rqs[rq].state = BLOCKED; 
            }
            break;
        }
      }

      // Randomly unblocks processes
      for(rq = 0; rq < max_processes; rq++)
        if (p_rqs[rq].state == BLOCKED && GetUniform(100) % 2){
          if(sys_pause_process(p_rqs[rq].pid) == -1){
            puts("test_processes: ERROR unblocking process");
            return;
          }
          p_rqs[rq].state = RUNNING; 
        }
    } 
  }
}
