#include <keyboard.h>
#include <stdint.h>
#include <time.h>

static void int_20();
static void int_21();

void irqDispatcher(uint64_t irq, uint64_t arg0) 
{
	switch (irq) {
		case 0:
			int_20();
			break;
			
		case 1:
			int_21(arg0);
			break;
	}
	return;
}

/* Handler del timer tick */
void int_20() {
	timer_handler();
}

/* Handler del keyboard */
void int_21(uint64_t arg0){
	keyboard_handler(arg0);
}
