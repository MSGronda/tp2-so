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

int clean_buffer(char * buf, int length){
    int i=0;
    for(int j=0; j<length; j++){
        while(buf[j] == '\b' && j<length){
            j++;
            i = i>0 ? i-1: 0;
        }
        if(j<length){
            buf[i] = buf[j];
            i++;
        }
    }
    buf[i] = 0;
    return i;
}

int read_line(char * buf, int length) {
    int count = 0, inc;
    int printed = 0;

    while(count < length){
        inc = sys_read(buf + count, length);

        if(inc == EOF){
            return EOF;
        }

        for(int j=0; j<inc; j++){
            if(buf[count + j] != '\n'){
                if(buf[count + j] == '\b'){
                    if(printed > 0){
                        sys_write(buf + count + j, 1);
                        printed--;
                    }
                }
                else{
                    sys_write(buf + count + j, 1);
                    printed++;
                }
            }
            else{
                buf[count + j] = 0;
                return clean_buffer(buf, count + j);
            }
        }        

        count += inc;   
        length -= inc;
    }
    return clean_buffer(buf, count-1);
}

unsigned int consume_buffer(char * buffer, int length){
    return sys_consume_stdin(buffer, length);
}

char getchar() {
    char c;
    read_line(&c, 1);

    return c;
}




