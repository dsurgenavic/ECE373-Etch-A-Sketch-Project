//Display(task 3) header file
#include "display.h"
#include "storage.h"
extern queue_t display_mem_semaphore;
extern uint16_t cursor_x_pos;
extern uint16_t cursor_y_pos;
extern uint8_t display_mem[102][8];

  
void init_spi(void) { 
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; 
	SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_CPOL | SPI_CR1_SSI | SPI_CR1_SSM | SPI_CR1_BR_1; 
	SPI1->CR1 |= SPI_CR1_SPE; 
	return; 
} 

void init_dogs() { 
	for(volatile int i = 0; i < 6; i++) {} 
	GPIOA->ODR &= ~(1U << 8U); 
	for(volatile int i = 0; i < 20; i++) {} 
	GPIOA->ODR |= (1U << 8U); 
	GPIOA->ODR &= ~(1U << 6);
	send_packet(0x40, 0); 
	send_packet(0xA1, 0); 
	send_packet(0xC0, 0); 
	send_packet(0xA4, 0); 
	send_packet(0xA6, 0); 
	send_packet(0xA2, 0); 
	send_packet(0x2F, 0); 
	send_packet(0x27, 0); 
	send_packet(0x81, 0); 
	send_packet(0x08, 0); 
	send_packet(0xFA, 0); 
	send_packet(0x90, 0); 
	send_packet(0xAF, 0); 
	return;
} 




void send_packet(uint32_t packet, uint8_t CD) {  
	if(CD == 1) { 
		GPIOA->ODR |= (1U << 6); 
	} 
	else { 
		GPIOA->ODR &= ~(1U << 6); 
	} 
	GPIOA->ODR &= ~(1U << 4U); 
	SPI1->DR = packet; 
	for(volatile int i = 0; i < 3; i++) {} 
	while(SPI1->SR & SPI_SR_BSY){} 
	GPIOA->ODR |= (1U << 4U); 
	return; 
} 




void clear_dogs() {
	for(volatile uint32_t i = 0; i < 8; i++) {
		send_packet(0xB0 | i, 0);
		for(volatile uint32_t j = 0; j < 102; j++) {
			volatile uint32_t lsb = j & 0x0F;
			volatile uint32_t msb = ((j & 0xF0) >> 4) | 0x10;
			send_packet(lsb, 0); 
			send_packet(msb, 0); 
			send_packet(0x00, 1);
			
		}
	}
}




void draw_dogs(){
	uint8_t page = cursor_y_pos / 8;
	send_packet(0xB0 | (0x0F & page), 0);
	volatile uint32_t lsb = cursor_x_pos & 0x0F;
	volatile uint32_t msb = ((cursor_x_pos & 0xF0) >> 4) | 0x10;
	send_packet(lsb, 0); 
	send_packet(msb, 0);
	
	bool check = write_q(&display_mem_semaphore, 1);
	if(!check) {return;}
	send_packet(display_mem[cursor_x_pos][page], 1);
	int16_t dummy;
	check = read_q(&display_mem_semaphore, &dummy);
	
}


