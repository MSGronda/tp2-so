#include "./include/shell.h"

extern void divError();             // exception_test.asm
extern void opCodeError();          // exception_test.asm

// --- Simbolos ---
#define SYMBOL "$> "
#define SYMBOL_LENGTH 3
#define PIPE "|"
#define INVALID_COMMAND_MSG "Invalid command!"

// --- Dimensiones ---
#define BUFFER_LENGTH 150
#define MAX_WORDS 30

typedef struct program_info{
        char * name;
        uint64_t ptr;
        uint8_t num_args;
}program_info;

#define TOTAL_PROGRAMS 9
static program_info programs[] = {
    {.name = "fibonacci", .ptr = (uint64_t) &fibonacci, .num_args = 0},
    {.name = "primos", .ptr = (uint64_t) &primos, .num_args = 0},
    {.name = "help", .ptr = (uint64_t) &help, .num_args = 0},
    {.name = "time", .ptr = (uint64_t) &time, .num_args = 0},
    {.name = "inforeg", .ptr = (uint64_t) &inforeg, .num_args = 0},
    {.name = "divError", .ptr = (uint64_t) &divError, .num_args = 0},
    {.name = "opCodeError", .ptr = (uint64_t) &opCodeError, .num_args = 0},
    {.name = "printmem", .ptr = (uint64_t) &printmem, .num_args = 1},
    {.name = "ps", .ptr = (uint64_t) &ps, .num_args = 0},
};


/* = = = = = = = = = CODIGO = = = = = = = = = */

int tokenize(char * string, char ** words){         // noto las posiciones de la palabra en words
    int count=0;
    int i=0;
    for(int postSpace=1; string[i]!=0 && string[i]!='\n' && count < MAX_WORDS; i++){
        if(string[i]==' '){
            postSpace = 1;
            string[i] = 0;                         // corto el string original en los espacios
        }
        else if(postSpace){
            words[count++] = string + i;
            postSpace = 0;
        }
    }
    string[i] = 0;                              // elimino el \n final
    return count;                               // cantidad de palabras tokenizadas
}

// devuelve la posicion en el array de punteros a funciones
// o -1 si no dio ninguno
unsigned int check_valid_program(char * string){
    for(int i=0; i<TOTAL_PROGRAMS; i++){
        if(strcmp(string, programs[i].name)==0){
            return i;
        }
    }
    return -1;
}

void shell(){
    char buffer[BUFFER_LENGTH];
    char * words[MAX_WORDS];

    while(1){
        print(SYMBOL, SYMBOL_LENGTH);

        read_line(buffer, BUFFER_LENGTH);

        int amount_of_words = tokenize(buffer, words);

        if(amount_of_words  == 0){
            puts("Empty string!");
            continue;                 // mas legible asi, no rompas los huevos
        }

        unsigned int program_pos = check_valid_program(words[0]);

        if(program_pos == -1){
            puts("Invalid program!");
            continue;
        }

        if(amount_of_words - 1 < programs[program_pos].num_args){
            puts("Missing arguments!");
        }
        else if(amount_of_words - 1 == programs[program_pos].num_args){
            sys_register_child_process(programs[program_pos].ptr, NORMAL_SCREEN, words + sizeof(char *));   // TODO: alocar espacio y copiar los comandos ahi. Chequear parametros validos
            sys_wait_for_children();
        }
        else{
            // quiere correr en el fondo
            if(strcmp("/", words[programs[program_pos].num_args + 1]) == 0){
                sys_register_process(programs[program_pos].ptr, BACKGROUND, words + sizeof(char *)); // TODO: alocar espacio y copiar los comandos ahi. Chequear parametros validos
            }
            // paso argumentos de mas y los ignoramos
            else{
                sys_register_child_process(programs[program_pos].ptr, NORMAL_SCREEN, words + sizeof(char *)); // TODO: alocar espacio y copiar los comandos ahi. Chequear parametros validos
                sys_wait_for_children();
            }
        }
        puts("");
    }
}