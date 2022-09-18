#include "../include/stdio.h"

void print(char * string, int length) {
    sys_write(string, length);
}

void putchar(char c){
    print(&c,1);
}

void clear_screen(){
    sys_clear_screen();
}

void puts(char * string) {
    print(string, strlen(string));
    print("\n",1);
}

void read_line(char * buf, int length) {
    sys_read(buf, length);
}

unsigned int consume_buffer(char * buffer, int length){
    return sys_consume_stdin(buffer, length);
}

char getchar() {
    char c;
    read_line(&c, 1);

    return c;
}




