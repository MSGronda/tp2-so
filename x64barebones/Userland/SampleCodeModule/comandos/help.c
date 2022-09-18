#include "../include/comandos.h"

void page0()
{
    puts("= = = = = = = = COMANDOS = = = = = = = = ");
    puts("   - fibonacci:\n       imprime la serie de fibonacci\n       se corta ejecucion con la tecla ESC\n");
    puts("   - primos:\n       imprime los numeros primos\n        se corta ejecucion con la tecla ESC\n");
    puts("   - inforeg:\n       imprime el contenido de los registros\n");
    puts("   - printmem:\n       recibe un parametro e imprime un vuelco (32 bytes) desde dicha direccion\n");    
    puts("   - time:\n       imprime el dia y hora del sistema\n");
    puts("   - div-error:\n       ejecuta una division por 0 para testear la excepcion\n");
    puts("   - opcode-error:\n       ejecuta una operacion invalida para testear la excepcion\n");
    puts("Pag 1/2 - proxima apretando \".\" - previa apretando \",\"");

    return;
}

void page1()
{
    puts("= = = = = = = = TECLA ESCPECIAL = = = = = = = = ");
    puts("   - Con tecla - F5 - se hace una captura de los registros\n\n");
    puts("= = = = = = = = = MULTITASKING = = = = = = = = ");
    puts("   - Para ejecucion simultanea comando1 | comando2\n");
    puts("   - Con tecla - F1 - se pausa/reanuda ejecucion de modo normal");
    puts("   - Con tecla - F2 - se pausa/reanuda ejecucion de lado izq");
    puts("   - Con tecla - F3 - se pausa/reanuda ejecucion de lado der");
    puts("   - Con tecla - ESC - regresa a la terminal unica");
    print("\n\n\n\n\n\n\n\n\n\n\n\n\n",13);
    puts("Pag 2/2 - proxima apretando \".\" - previa apretando \",\"");
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
            currPage = currPage%2;
            switchPage(currPage);
        } else if(strContainsChar(buffer, ',')>=0){                    // ## REMPLAZAR ##
            currPage--;

            if(currPage < 0)
                currPage += 2;

            switchPage(currPage);
        }
    }
}