#include "stm32l053xx.h"
#include "fsm_btn.h"
#include "storage.h"
#include "queue.h"

/*QUEUES NEEDED:
 *Inputs
 *SEMAPHORES
 *display_data
 */

queue_t knob_queue;
queue_t button_queue;
queue_t display_mem_semaphore;

void gpio_init(void);
int main(void);

void gpio_init(void) {
	return;
}

int main(void) {
	init_queue(&knob_queue, 4);
	init_queue(&button_queue, 2);
	init_queue(&display_mem_semaphore, 1);
	init_display_mem();
	return 0;
}
