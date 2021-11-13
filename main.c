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

void init_gpio(void) {
	GPIOC->MODER &= ~(GPIO_MODER_MODE13_Msk); //Enable GPIO C13 for the pen button
	GPIOC->MODER |= GPIO_MODER_MODE13_0;
	
	GPIOB->MODER &= ~(GPIO_MODER_MODE1_Msk); //Enable GPIO B1 & B2 for one of the buttons
	GPIOB->MODER |= GPIO_MODER_MODE1_0;
	GPIOB->MODER &= ~(GPIO_MODER_MODE2_Msk);
	GPIOB->MODER |= GPIO_MODER_MODE2_0;
	
	GPIOB->MODER &= ~(GPIO_MODER_MODE3_Msk); //Enable GPIO B3 & B4 for the other button
	GPIOB->MODER |= GPIO_MODER_MODE3_0;
	GPIOB->MODER &= ~(GPIO_MODER_MODE4_Msk);
	GPIOB->MODER |= GPIO_MODER_MODE4_0;
	
	GPIOA->MODER &= ~(GPIO_MODER_MODE6_Msk); //Enable GPIO A6 for the CD line on the display
	GPIOA->MODER |= GPIO_MODER_MODE6_0;
	GPIOA->MODER &= ~(GPIO_MODER_MODE8_Msk); //Enable GPIO A8 to act as a reset switch for the display
	GPIOA->MODER |= GPIO_MODER_MODE8_0;
	GPIOA->ODR &= ~(1U << 8); //Assert reset high
	return;
}

int main(void) {
	init_queue(&input_queue, 4);
	init_queue(&display_mem_semaphore, 1);
	init_display_mem();
	//initialization for display
	init_gpio();
	init_spi();
	init_dogs();
	
	while(1) {
		update_inputs();
		update_storage();
		draw_dogs();
	}
}
