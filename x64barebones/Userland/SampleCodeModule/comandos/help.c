#include "../include/comandos.h"

void page0()
{
    puts("= = = = = = = = = MULTITASKING = = = = = = = = ");
    puts("   - Para ejecucion simultanea comando1 | comando2\n");
    puts("   - Con tecla - F1 - se pausa/reanuda ejecucion de modo normal");
    puts("   - Con tecla - ESC - regresa a la terminal unica");
    print("\n\n\n\n\n\n\n\n\n\n\n\n\n",13);
    puts("Pag 1/4 - proxima apretando \".\" - previa apretando \",\"");
}

void page1()
{
    puts("= = = = = = = = COMANDOS = = = = = = = = ");
    puts("   - fibonacci:\n     imprime la serie de fibonacci\n     se corta ejecucion con la tecla ESC\n");
    puts("   - primos:\n    imprime los numeros primos\n    se corta ejecucion con la tecla ESC\n");
    puts("   - time:\n    imprime el dia y hora del sistema\n");
    puts("   - printargs:\n    imprime los argumentos pasados por linea de comandos\n");
    puts("   - pipe:\n    imprime la lista de pipes con sus propiedades\n");
    puts("   - filter:\n    filtra las vocales del input\n");
    puts("   - wc:\n    cuenta la cantidad de lineas del input\n");
    puts("Pag 2/4 - proxima apretando \".\" - previa apretando \",\"");

    return;
}

void page2() {
    puts("= = = = = = = = COMANDOS = = = = = = = = ");
    puts("   - sem:\n    imprime la lista de semaforos con sus propiedades\n");
    puts("   - ps:\n    imprime la lista de procesos con sus propiedades\n");
    puts("   - kill:\n    mata a un proceso dado su ID\n");
    puts("   - block:\n    cambia el estado de un proceso entre bloqueado y listo dado su ID\n");
    puts("   - nice:\n    cambia la prioridad de un proceso dado su ID y su nueva prioridad\n");
    puts("   - cat:\n    imprime el stdin tal como lo recibe\n");
    puts("   - loop:\n    imprime su ID con un saludo cada una determinada cantidad de segundos\n");
    puts("Pag 3/4 - proxima apretando \".\" - previa apretando \",\"");

    return;
}

void page3() {
    puts("= = = = = = = = COMANDOS = = = = = = = = ");
    puts("   - div-error:\n    ejecuta una division por 0 para testear la excepcion\n");
    puts("   - opcode-error:\n    ejecuta una operacion invalida para testear la excepcion\n");
    puts("= = = = = = = = TESTS = = = = = = = = ");
    puts("   - test-sem:\n    corre un testeo de semaforos\n");
    puts("   - test-mm:\n    corre un testeo del memory manager\n");
    puts("   - test-process:\n    corre un testeo de procesos\n");
    puts("   - test-prio:\n    corre un testeo de prioridades\n");
    puts("Pag 4/4 - proxima apretando \".\" - previa apretando \",\"");

    return;
}


void switchPage(int page)
{
    clear_screen();
    switch(page){
        case 0: 
            page0();
            break;

        case 1:
            page1();
            break;
        
        case 2:
            page2();
            break;

        case 3:
            page3();
            break;

        default:
            break;
    }
}

void help()
{
    int size;
    char buffer[BUFF_SIZE];
    int currPage = 0;
    page0();
    while(1) {
        size = consume_buffer(buffer, BUFFER_LENGTH-1);
        buffer[size] = 0;

        if(strContainsChar(buffer, '.')>=0) {                    // ## REMPLAZAR ##
            currPage++;
            currPage = currPage%4;
            switchPage(currPage);
        } else if(strContainsChar(buffer, ',')>=0){                    // ## REMPLAZAR ##
            currPage--;

            if(currPage < 0)
                currPage += 4;

            switchPage(currPage);
        }
    }
}