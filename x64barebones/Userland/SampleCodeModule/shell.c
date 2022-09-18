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
#define MAX_WORDS 10
#define TOTAL_COMMANDS 8

#define TOTAL_SPECIAL_KEYS 4
static char specialKeys[] = {
    PAUSE_RIGHT_SCREEN, PAUSE_LEFT_SCREEN, PAUSE_NORMAL_SCREEN, ESCAPE_KEY
};

// --- Comandos ---
static char * commands[] = {
    "fibonacci", "primos", "help", "time", "inforeg",
    "div-error", "opcode-error", "printmem"
};

static uint64_t functions[] = {
    (uint64_t) &fibonacci, (uint64_t)&primos, (uint64_t)&help, (uint64_t)&time, (uint64_t)&inforeg,
    (uint64_t) &divError, (uint64_t)&opCodeError, (uint64_t)&printmem
};


#define REGISTER_PROGRAM(name, param, screen) \
                pos1 = checkCommand(name, commands, TOTAL_COMMANDS);        \
                if(pos1 >= 0){                                              \
                    sys_clear_screen();                                     \
                    pid1 = sys_register_process(functions[pos1], screen, (uint64_t) param); \
                }                                                           \
                else{                                                       \
                    puts(INVALID_COMMAND_MSG);                              \
                    return;                                                 \
                }                                                           \
                break;                                                      \

#define REGISTER_DUAL_PROGRAMS(name1, name2, param1, param2, screen1, screen2) \
                pos1 = checkCommand(name1, commands, TOTAL_COMMANDS);       \
                pos2 = checkCommand(name2, commands, TOTAL_COMMANDS);       \
                if(pos2 >= 0 && pos2 >=0){                                  \
                    sys_clear_screen();                                     \
                    pid1 = sys_register_process(functions[pos1], screen1, (uint64_t) param1); \
                    pid2 = sys_register_process(functions[pos2], screen2, (uint64_t) param2); \
                }                                                           \
                else{                                                       \
                    puts(INVALID_COMMAND_MSG);                              \
                    return;                                                 \
                }                                                           \
                break;                                                      \


/* = = = = = = = = = CODIGO = = = = = = = = = */

int parseCommands(char * string, char ** words){         // noto las posiciones de la palabra en words
    int count=0;
    int i=0;
    for(int postSpace=1; string[i]!=0 && string[i]!='\n'; i++){
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
unsigned int checkCommand(char * string, char ** array, unsigned int dim){
    for(int i=0; i<dim; i++){
        if(strcmp(string, array[i])==0){
            return i;
        }
    }
    return -1;
}

// retorna la primera key especial que encuentra
char findSpecialKey(char * string, char * keys, unsigned int size){
    int i;
    for(i=0; string[i]!=0; i++){
        for(int j=0; j<size; j++){
            if(string[i]==keys[j]){
                return keys[j];
            }
        }
    }
    return -1;
}


/*
    Primero se fija si es una combinacion valida de commands y pipe.
    Luego registra los procesos y entra un loop donde se fija si
    el usuario toco una tecla especial para pausar o terminar la ejecucion.
    Parametros: words: array de strings  | count: cantidad de elementos en array
*/
void commandsDispatcher(char ** words, unsigned int count){
    char finishedExecution = 0;
    int pos1, pos2, pid1=-1, pid2=-1;
    char buffer[BUFFER_LENGTH];
    int size;
    switch(count){
        case 0:
            puts("Too few arguments!");
            return; 
        case 1:
            REGISTER_PROGRAM(words[0], NULL, NORMAL_SCREEN)

        case 2:
            REGISTER_PROGRAM(words[0], words[1], NORMAL_SCREEN)

        case 3:                                 // caso valido: COMMAND | COMMAND
           if(strcmp(words[1],PIPE)!=0){
                puts(INVALID_COMMAND_MSG);
                return;
            } 
            REGISTER_DUAL_PROGRAMS(words[0],words[2],NULL, NULL, LEFT_SCREEN, RIGHT_SCREEN)

        case 4:                                 // casos valido: COMMAND ARG | COMMAND  o  COMMAND | COMMAND ARG
            if(strcmp(words[1],PIPE)==0){              
                REGISTER_DUAL_PROGRAMS(words[0],words[2],NULL, words[3], LEFT_SCREEN, RIGHT_SCREEN)
            }
            else if(strcmp(words[2],PIPE)==0){
                REGISTER_DUAL_PROGRAMS(words[0],words[3], words[1], NULL, LEFT_SCREEN, RIGHT_SCREEN)
            }
            else{
                puts(INVALID_COMMAND_MSG);
                return; 
            }

        case 5:
            if(strcmp(words[2],PIPE)!=0){       // caso valido: COMMAND ARG1 | COMMAND ARG2
                puts(INVALID_COMMAND_MSG);
                return;
            }
            REGISTER_DUAL_PROGRAMS(words[0],words[3],words[1], words[4], LEFT_SCREEN, RIGHT_SCREEN)

         default:
            puts("Too many arguments!");
            return;
        }

    while(finishedExecution==0){                                // el shell sigue corriendo en el fondo, fijandose si se toco una tecla especial
        size = consume_buffer(buffer, BUFFER_LENGTH-1);
        buffer[size] = 0;
        char key = findSpecialKey(buffer, specialKeys, TOTAL_SPECIAL_KEYS);

        switch(key){
            case ESCAPE_KEY:
                sys_kill_process(pid1);     
                sys_kill_process(pid2);                          // en todos estos casos, nos aprovechamos con que si no existe un task con ese
                sys_clear_screen();                              // pid, no hace nada y listo.
                finishedExecution = 1;
                break;
            case PAUSE_NORMAL_SCREEN:
                if(pid2<0)
                sys_pause_process(pid1);
                break;
            case PAUSE_LEFT_SCREEN:
                if(pid2>0)
                    sys_pause_process(pid1);
                break;
            case PAUSE_RIGHT_SCREEN:
                if(pid2>0)
                    sys_pause_process(pid2);
                break;
        }  
    }
}

void shell(){
    char buffer[BUFFER_LENGTH];
    char * commands[MAX_WORDS];


    int amount;
    while(1){
        print(SYMBOL, SYMBOL_LENGTH);
        read_line(buffer, BUFFER_LENGTH);

        amount = parseCommands(buffer, commands);
        commandsDispatcher(commands, amount);
    }
}