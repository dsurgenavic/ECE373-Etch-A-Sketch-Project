#include "stm32l053xx.h"
#include "fsm_btn.h"
#include "storage.h"
#include "queue.h"
#include "knob.h"
#include "display.h"

queue_t input_queue;
queue_t display_mem_semaphore;

void gpio_init(void);
int main(void);

void gpio_init(void) {
	return;
}

int main(void) {
	init_queue(&input_queue, 4);
	init_queue(&display_mem_semaphore, 1);
	init_display_mem();
	while(1) {
		update_inputs();
		update_storage();
	}
}
