#include "stm32l053xx.h"
#include "fsm_btn.h"
#include "storage.h"
#include "queue.h"

/*QUEUES NEEDED:
 *Inputs
 *SEMAPHORES
 *display_data
 */

extern queue_t knob_queue;
extern queue_t button_queue;
extern queue_t display_data_semaphore;

void gpio_init(void);
int main(void);

void gpio_init(void) {
	return;
}

int main(void) {
	init_queue(&knob_queue, 4);
	init_queue(&button_queue, 2);
	init_queue(&display_data_semaphore, 1);
	return 0;
}
