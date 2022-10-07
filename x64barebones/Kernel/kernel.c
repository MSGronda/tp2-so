#include <idtLoader.h>
#include <lib.h>
#include <moduleLoader.h>
#include <stdint.h>
#include <string.h>
#include <multitasking.h>
#include <syscalls.h>
#include <memoryManager.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize) {
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);

	clearBSS(&bss, &endOfKernel - &bss);

	return getStackBase();
}

/* TESTEOS MM -- BORRAR */
void testFree() {
	char * ptr1 = mm_malloc(5);
	char * ptr2 = mm_malloc(5);

	char buffer1[100];
	hex_to_string(ptr1, buffer1, 100);
	char buffer2[100];
	hex_to_string(ptr1, buffer2, 100);

	sys_write(1, buffer1, 100);
	sys_write(1, '\n', 1);
	sys_write(1, buffer2, 100);

	ptr1[0] = 'h';
	ptr1[1] = 'o';
	ptr1[2] = 'l';
	ptr1[3] = 'a';
	ptr1[4] = 0;
	mm_free(ptr1);

	char * ptr3 = mm_malloc(5);
	ptr3[0] = 'j';
	ptr3[1] = 'a';
	ptr3[2] = 'l';
	ptr3[3] = 'a';
	ptr3[4] = 0;
	
	ptr2[0] = 'c';
	ptr2[1] = 'h';
	ptr2[2] = 'a';
	ptr2[3] = 'u';
	ptr2[4] = 0;


	sys_write(1, ptr1, 5);
	for(int i=0 ; i<500000000 ; i++);
	sys_write(1, ptr2, 5);
	for(int i=0 ; i<50000000000 ; i++);

	mm_free(ptr2);
}

void testLimit() {
	char * ptr = mm_malloc(HEAP_SIZE - HEADER_SIZE - EOL_SIZE);
	sys_write(1, "check", 5);
	char * check = mm_malloc(3);

	if(ptr == NULL) 
		sys_write(1, "ptr null", 8);
	else
		sys_write(1, "ptr no null", 12);

	if(check == NULL) 
		sys_write(1, "chc null", 8);
	else
		sys_write(1, "chc no null", 12);


	for(int i=0 ; i<50000000000 ; i++);
	// Lo que se deberia ver es:
	// ptr no null chc null
	// pero me esta apareciendo que ambos son no null
}
/* ---------------------- */

int main()
{	
	sys_clear_screen();

	load_idt();

	mm_init();
	
	/* Testeos MM */
	testFree();
	
	/* --------- */

	addTask((uint64_t)sampleCodeModuleAddress,1,0);	// llamada a userland
	enableMultiTasking();
	
	return 0;
}
