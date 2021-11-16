#include "stm32l053xx.h"
#include "stdint.h"
#include "fsm_btn.h"
#include "storage.h"
#include "queue.h"
#include "knob.h"
#include "display.h"

queue_t input_queue;
queue_t display_mem_semaphore;

void init_gpio(void);
int main(void);

void init_gpio(void) {
	
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN; 
	RCC->IOPENR |= RCC_IOPENR_GPIOCEN;
	
	GPIOA->MODER &= ~(GPIO_MODER_MODE4_Msk); //These lines enable the select line for the SPI 
	GPIOA->MODER |= GPIO_MODER_MODE4_0; 
	GPIOA->MODER &= ~(GPIO_MODER_MODE5_Msk); //These Lines enable the SPI Clock 
	GPIOA->MODER |= 2 << GPIO_MODER_MODE5_Pos; 
	GPIOA->MODER &= ~(GPIO_MODER_MODE7_Msk); //These Lines enable the data line for the SPI 
	GPIOA->MODER |= 2 << GPIO_MODER_MODE7_Pos; 
	
	
	GPIOC->MODER &= ~(GPIO_MODER_MODE13_Msk); //Enable GPIO C13 for the pen button
	GPIOC->MODER |= 1 << GPIO_MODER_MODE13_Pos;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD13_Msk;
    GPIOC->PUPDR |= 0x01 << GPIO_PUPDR_PUPD13_Pos;
	
	GPIOC->MODER &= ~(GPIO_MODER_MODE0_Msk); //Enable GPIO C1 & C2 for one of the buttons
	GPIOC->MODER |= 1 << GPIO_MODER_MODE0_Pos;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD0_Msk;
    GPIOC->PUPDR |= 0x01 << GPIO_PUPDR_PUPD0_Pos;
	GPIOC->MODER &= ~(GPIO_MODER_MODE1_Msk);
	GPIOC->MODER |= 1 << GPIO_MODER_MODE1_Pos;
    GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD1_Msk;
    GPIOC->PUPDR |= 0x01 << GPIO_PUPDR_PUPD1_Pos;
	
	GPIOC->MODER &= ~(GPIO_MODER_MODE3_Msk); //Enable GPIO C3 & C4 for the other button
	GPIOC->MODER |= 1 << GPIO_MODER_MODE3_Pos;
    GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD3_Msk;
    GPIOC->PUPDR |= 0x01 << GPIO_PUPDR_PUPD3_Pos;
	GPIOC->MODER &= ~(GPIO_MODER_MODE2_Msk);
	GPIOC->MODER |= 1 << GPIO_MODER_MODE2_Pos;
    GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD2_Msk;
    GPIOC->PUPDR |= 0x01 << GPIO_PUPDR_PUPD2_Pos;
	
	GPIOA->MODER &= ~(GPIO_MODER_MODE6_Msk); //Enable GPIO A6 for the CD line on the display
	GPIOA->MODER |= GPIO_MODER_MODE6_0;
	GPIOA->MODER &= ~(GPIO_MODER_MODE8_Msk); //Enable GPIO A8 to act as a reset switch for the display
	GPIOA->MODER |= GPIO_MODER_MODE8_0;
	GPIOA->ODR &= ~(1U << 8); //Assert reset high
	return;
}

int main(void) {
	init_gpio();
	init_queue(&input_queue, 6);
	init_queue(&display_mem_semaphore, 2);
	init_display_mem();
	init_knobs();
	//initialization for display
	init_spi();
	init_dogs();
	clear_dogs();
	
	while(1) {
		update_inputs();
		update_storage();
		draw_dogs();
	}
}
