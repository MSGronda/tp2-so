#include "./include/shell.h"

extern void divError();             // exception_test.asm
extern void opCodeError();          // exception_test.asm

// --- Simbolos ---
#define SYMBOL "$> "
#define SYMBOL_LENGTH 3
#define PIPE "|"

// Error Msg
#define INVALID_COMMAND_MSG "Invalid command!"
#define NON_PIPABLE "Program is not pipable!"
#define MISSING_ARGS "Missing arguments!"
#define NO_STRING "Empty string!"
#define MALLOC_ERROR "Error allocating space for args!"

// --- Dimensiones ---
#define BUFFER_LENGTH 400
#define MAX_WORDS 30

#define MIN(a,b) ((a) <= (b) ? (a) : (b))

typedef struct program_info{
        char * name;
        uint64_t ptr;
        uint8_t min_args;
        uint8_t max_args;
        uint8_t pipeable;
}program_info;

#define TOTAL_PROGRAMS 23
static program_info programs[] = {
    {.name = "fibonacci", .ptr = (uint64_t) &fibonacci, .min_args = 0, .max_args = 0, .pipeable = 0},
    {.name = "primos", .ptr = (uint64_t) &primos, .min_args = 0, .max_args = 0, .pipeable = 0},

    {.name = "help", .ptr = (uint64_t) &help, .min_args = 0, .max_args = 0, .pipeable = 0},
    {.name = "time", .ptr = (uint64_t) &time, .min_args = 0, .max_args = 0, .pipeable = 1},

    {.name = "div-error", .ptr = (uint64_t) &divError, .min_args = 0, .max_args = 0, .pipeable = 0},
    {.name = "opcode-error", .ptr = (uint64_t) &opCodeError, .min_args = 0, .max_args = 0, .pipeable = 0},

    {.name = "printargs", .ptr = (uint64_t) &printargs, .min_args = 0, .max_args = MAX_WORDS, .pipeable = 0},
    {.name = "pipe", .ptr = (uint64_t) &pipe, .min_args = 0, .max_args = 0, .pipeable = 0},
    {.name = "sem", .ptr = (uint64_t) &sem, .min_args = 0, .max_args = 0, .pipeable = 0},

    {.name = "ps", .ptr = (uint64_t) &ps, .min_args = 0, .max_args = 0, .pipeable = 1},
    {.name = "kill", .ptr = (uint64_t) &kill, .min_args = 1, .max_args = 1, .pipeable = 0},
    {.name = "block", .ptr = (uint64_t) &pause, .min_args = 1, .max_args = 1, .pipeable = 0},
    {.name = "nice", .ptr = (uint64_t) &nice, .min_args = 2, .max_args = 2, .pipeable = 0},

    {.name = "test-sem", .ptr = (uint64_t) &test_sem, .min_args = 0, .max_args = 0, .pipeable = 0},
    {.name = "test-no-sem", .ptr = (uint64_t) &test_no_sem, .min_args = 0, .max_args = 0, .pipeable = 0},
    {.name = "test-mm", .ptr = (uint64_t) &test_mm, .min_args = 0, .max_args = 0, .pipeable = 0},
    {.name = "test-process", .ptr = (uint64_t) &test_processes, .min_args = 1, .max_args = 1, .pipeable = 0},
    {.name = "test-prio", .ptr = (uint64_t) &test_prio, .min_args = 0, .max_args =0, .pipeable = 0},
    {.name = "test-pipe", .ptr = (uint64_t) &test_pipe, .min_args = 0, .max_args =0, .pipeable = 0},

    {.name = "cat", .ptr = (uint64_t) &cat, .min_args = 0, .max_args = 0, .pipeable = 1},
    {.name = "loop", .ptr = (uint64_t) &loop, .min_args = 0, .max_args = 0, .pipeable = 1},
    {.name = "filter", .ptr = (uint64_t) &filter, .min_args = 0, .max_args = 0, .pipeable = 1},
    {.name = "wc", .ptr = (uint64_t) &wc, .min_args = 0, .max_args = 0, .pipeable = 0},
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

char ** make_params(char ** words, unsigned int len){
    void * coso = (void*) sys_alloc((2 + len) * sizeof(char *)); // + 1 for name, + 1 por null termination

    if(coso == NULL){
        puts(MALLOC_ERROR);     //TODO: replace
        return NULL;
    }

    char ** params = (char **) coso;

    void * param;
    int paramLen;

    int i=0;
    for(; i<len + 1; i++){
        paramLen = strlen(words[i]) + 1;
        param = (void*) sys_alloc(paramLen);

         if(param == NULL){
            puts(MALLOC_ERROR);     //TODO: replace
            return NULL;
        }

        char * param2 = (char *) param;

        strncpy(param2, words[i], paramLen);
        params[i] = param2;
    }
    params[i] = NULL;
    return params;
}

int piped_process_handle(char ** words, unsigned int amount_of_words){
    if(amount_of_words != 3 || strcmp("|", words[1]) != 0)
        return 0;
    unsigned int p1 = check_valid_program(words[0]);
    unsigned int p2 = check_valid_program(words[2]);
    if(p1 == -1 || p2 == -1){
        puts(INVALID_COMMAND_MSG);
        return 1;
    }
    if(!programs[p1].pipeable){
        puts(NON_PIPABLE);
        return 1;
    }
    int pipe_id = sys_register_pipe_available();

    if(pipe_id <= 0){
        puts("Error creating pipe!");
        return 1;
    }

    sys_register_child_process(programs[p1].ptr, STDIN, pipe_id, (uint64_t) make_params(words, 0)); 
    sys_register_child_process(programs[p2].ptr, pipe_id, NORMAL_SCREEN, (uint64_t) make_params(words, 0)); 

    sys_wait_for_children();

    sys_destroy_pipe(pipe_id);

    return 2;
}

void single_process_handle(char ** words, unsigned int amount_of_words){
     unsigned int program_pos = check_valid_program(words[0]);

    if(program_pos == -1){
        puts(INVALID_COMMAND_MSG);
        return;
    }
    if(amount_of_words - 1 < programs[program_pos].min_args){
        puts(MISSING_ARGS);
        return;
    }


    // Check if user wants to run program in background
    int i, backgroud_indiaction = 0;
    for(i=programs[program_pos].min_args + 1; !backgroud_indiaction && i<amount_of_words; i++){
        if(strcmp("//", words[i]) == 0){         // We consider the symbol as the last argument. All subsequent arguments will be ignored
            backgroud_indiaction = 2;       
        }
        else if(strcmp("/", words[i]) == 0){         // We consider the symbol as the last argument. All subsequent arguments will be ignored
            backgroud_indiaction = 1;       
        }
    }

    // Run in background
    if(backgroud_indiaction == 2){
        sys_register_process(programs[program_pos].ptr, STDIN, BACKGROUND, (uint64_t) make_params(words, MIN(i-1,programs[program_pos].max_args))); 
    }
    else if(backgroud_indiaction == 1){
        sys_register_process(programs[program_pos].ptr, STDIN, NORMAL_SCREEN, (uint64_t) make_params(words, MIN(i-1,programs[program_pos].max_args))); 
    }

    // Run on screen
    else{
        sys_register_child_process(programs[program_pos].ptr, STDIN, NORMAL_SCREEN, (uint64_t) make_params(words, MIN(amount_of_words-1, programs[program_pos].max_args))); 
    
        sys_wait_for_children();
    }
    
}


void shell(){
    char buffer[BUFFER_LENGTH];
    char * words[MAX_WORDS];

    while(1){
        puts("");
        print(SYMBOL, SYMBOL_LENGTH);

        read_line(buffer, BUFFER_LENGTH);
        puts("");

        int amount_of_words = tokenize(buffer, words);

        if(amount_of_words  == 0){
            puts(NO_STRING);
            continue;                 // mas legible asi, no rompas los huevos
        }

        if(piped_process_handle(words,amount_of_words) == 0){
            single_process_handle(words,amount_of_words);
        }
    }
}