#include "../include/comandos.h"
#include "../include/syscalls.h"

static char * mmInfo[] = { "Allocated Bytes: ", "Free Bytes: ", "Allocated Blocks: "};

void mmstatus(){
    uint64_t info[3] = { 0 };
    sys_mm_status(info);

    print("Total Memory: ", 14);

    char buffer[16] = { 0 };
    num_to_string(info[0] + info[1], buffer);
    puts(buffer);

    for(int i = 0 ; i < 3 ; i++){
        char buf[16] = {0};
        print(mmInfo[i], strlen(mmInfo[i]));
        int len = num_to_string(info[i], buf);
        puts(buf);
    }

}