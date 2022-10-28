#include <keyboard.h>

extern char readKeyboard();		// en libasm.asm
/*-------- CONSTANTS --------*/
#define BUFFER_SIZE 200

// --- Caracteres especiales ---
#define ESCAPE_KEY 27
#define F1_KEY 17
#define F2_KEY 18
#define F3_KEY 19

// Scan codes
#define ESCAPE_KEY_SCAN_CODE 0x01
#define F1_SCAN_CODE 0x3B
#define F2_SCAN_CODE 0x3C
#define F3_SCAN_CODE 0x3D
#define F5_SCAN_CODE 0x3F

/*-------- STATIC FILE VARIABLES --------*/
static char keyBuffer[BUFFER_SIZE];             // Buffer de caracters de teclado
static int writePos;				// Posicion a escribir en el buffer
static int readPos;				// Posicion a consumir en el buffer

/* Tabla de equivalencias entre makeCode y Ascii */
static char scanCodeTable[] = {
        UNMAPPED,ESCAPE_KEY,'1','2','3','4','5','6','7','8',	
	'9','0','-','=','\b','\t','q','w','e','r',
	't','y','u','i','o','p','[',']','\n',UNMAPPED,
	'a','s','d','f','g','h','j','k','l',';',
	'\'','|',UNMAPPED,'|','z','x','c','v','b','n',
	'm',',','.','/',UNMAPPED,'*',UNMAPPED,' ',UNMAPPED,
	F1_KEY,F2_KEY,F3_KEY,UNMAPPED,UNMAPPED,
	UNMAPPED,UNMAPPED,UNMAPPED,UNMAPPED,UNMAPPED,
	UNMAPPED,UNMAPPED,UNMAPPED,UNMAPPED,UNMAPPED,'-',
	UNMAPPED,UNMAPPED,UNMAPPED,'+',UNMAPPED,UNMAPPED,
	UNMAPPED,UNMAPPED,UNMAPPED,UNMAPPED,UNMAPPED,UNMAPPED,
	UNMAPPED,UNMAPPED,UNMAPPED
};	

// ---------------------------------------

/* Consumo letra del buffer y sobreescribe con 0 para denotar una posicion vacia. */
char get_key()
{
	if(!checkIfAvailableKey())
		return 0;

	char c = keyBuffer[readPos];		// consumo letra 
	keyBuffer[readPos] = 0;

	INCREASE_MOD(readPos,BUFFER_SIZE)
	
	return c;
}

unsigned int consume_kb_buffer(char * buf, unsigned int count) 
{
	int i=0;
	
	while(checkIfAvailableKey() && i<count) {
		char c = get_key();
		buf[i++] = c;
	}
	return i;
}


char checkIfAvailableKey() {
	return keyBuffer[readPos] != 0;
}


// ---------------------------------------


/* Usa un array circular. Si se llega a la capacidad maxima, no sobre-escribe. */
void keyboard_handler() {
	int key = readKeyboard();

	// Special Actions
	switch(key){
		case ESCAPE_KEY_SCAN_CODE:
			kill_screen_processes();
			return;
		case F1_SCAN_CODE:
			pauseScreenProcess(STDOUT);
			return;

		case F2_SCAN_CODE:
			pauseScreenProcess(STDOUT_LEFT);
			return;
		case F3_SCAN_CODE:
			pauseScreenProcess(STDOUT_RIGHT);
			return;
	}

	if(key<0 || key>=128 || keyBuffer[writePos]!=0)
		return;
			
	char c = scanCodeTable[key];			// convierto a ascii

	// ------ Caracteres normales -------
	if(c != UNMAPPED){
		keyBuffer[writePos] = c;					// se agraga al buffer
		INCREASE_MOD(writePos,BUFFER_SIZE);
	}
}