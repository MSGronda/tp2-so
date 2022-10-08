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
	char * ptr1 = mm_malloc(8);
	char * ptr2 = mm_malloc(8);

	ptr1[0] = 'n';
	ptr1[1] = 'o';
	ptr1[2] = 'f';
	ptr1[3] = 'u';
	ptr1[4] = 'n';
	ptr1[5] = 'c';
	ptr1[6] = 'a';
	ptr1[7] = 0;
	mm_free(ptr1);

	char * ptr3 = mm_malloc(8);
	ptr3[0] = 'p';
	ptr3[1] = 'a';
	ptr3[2] = 's';
	ptr3[3] = 's';
	ptr3[4] = 'e';
	ptr3[5] = 'd';
	ptr3[6] = 0;
	
	ptr2[0] = 'c';
	ptr2[1] = 'h';
	ptr2[2] = 'a';
	ptr2[3] = 'u';
	ptr2[4] = 0;


	sys_write(1, ptr1, 7);
	sys_write(1, "     ", 5);
}

void testMerge(){

	//LLEVA HEADER_SIZE/8????

	char * m1 = mm_malloc(10);
	char * m2 = mm_malloc(10);
	char * m3 = mm_malloc(10);
	char * m4 = mm_malloc(10);

	int size = GET_SIZE(m3-HEADER_SIZE / 8);

	mm_free(m4);
	mm_free(m3);

	if(GET_SIZE(m3-HEADER_SIZE / 8) == size*2)
		sys_write(1, "test passed   ", 14);
	else
		sys_write(1, "test merge 1 failed   ", 22);

	mm_free(m2);

	if(GET_SIZE(m2-HEADER_SIZE / 8) == size*3)
		sys_write(1, "test passed   ", 14);
	else
		sys_write(1, "test merge 2 failed   ", 22);

	mm_free(m1);

	if(GET_SIZE(m1-HEADER_SIZE/ 8) == size*4)
		sys_write(1, "test passed   ", 14);
	else
		sys_write(1, "test merge 3 failed   ", 22);

}

void testNoFragmentation(){
	char * m1 = mm_malloc(30);
	int size1 = GET_SIZE(m1 - HEADER_SIZE);

	mm_free(m1);

	char * m2 = mm_malloc(28);
	int size2 = GET_SIZE(m2 - HEADER_SIZE);

	if(size1 == size2)
		sys_write(1, "test passed   ", 14);
	else
		sys_write(1, "test fragmentation failed   ", 28);


	
}



void testLimit() {
	char * ptr = mm_malloc(HEAP_SIZE - HEADER_SIZE - EOL_SIZE);
	char * check = mm_malloc(3);

	if(ptr != NULL) 
		sys_write(1, "test passed   ", 14);
	else
		sys_write(1, "test limit 1 failed   ", 22);

	if(check == NULL) 
		sys_write(1, "test passed   ", 14);
	else
		sys_write(1, "test limit 2 failed   ", 22);
}
/* ---------------------- */

int main()
{	
	sys_clear_screen();

	load_idt();

	for(int i = 1 ; i < 10 ; i++){
		mm_init();
		switch(i){
			case 1: testLimit();
					break;
			case 2: testNoFragmentation();
					break;
			case 3: testMerge();
					break;
			case 4: testFree();
					break;
			default: break;
		}
	}
	
	for(int i=0 ; i<50000000000 ; i++);

	/* --------- */

	addTask((uint64_t)sampleCodeModuleAddress,1,0);	// llamada a userland
	enableMultiTasking();
	
	return 0;
}
