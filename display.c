//Display(task 3) header file
#include "display.h"
#include "storage.h"


void init_gpio(void) { 
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN; 
	GPIOA->MODER &= ~(GPIO_MODER_MODE4_Msk); //These lines enable the select line for the SPI 
	GPIOA->MODER |= GPIO_MODER_MODE4_0; 
	GPIOA->MODER &= ~(GPIO_MODER_MODE5_Msk); //These Lines enable the SPI Clock 
	GPIOA->MODER |= 2 << GPIO_MODER_MODE5_Pos; 
	GPIOA->MODER &= ~(GPIO_MODER_MODE7_Msk); //These Lines enable the data line for the SPI 
	GPIOA->MODER |= 2 << GPIO_MODER_MODE7_Pos; 
	GPIOA->MODER &= ~(GPIO_MODER_MODE6_Msk); //Enable GPIO A6 for the CD line on the display 
	GPIOA->MODER |= GPIO_MODER_MODE6_0; 
	GPIOA->MODER &= ~(GPIO_MODER_MODE8_Msk); //Enable GPIO A8 to act as a reset switch for the display 
	GPIOA->MODER |= GPIO_MODER_MODE8_0; 
	GPIOA->ODR &= ~(1U << 8); //Assert reset high 
  return; 
} 
  
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
	send_packet(0x10, 0); 
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

void clear_dogs(void) { 
	for(volatile uint32_t z=0; z<7; z++) //for page address
		{
			send_packet(0xB0&z, 0);
	for(volatile uint32_t y=0; y<102; y++) //for column address
		{
			volatile uint32_t lsb = y & 0x0F;
			volatile uint32_t msb = ((y & 0xF0) >> 4) | 0x10;
			send_packet(lsb, 0); 
			send_packet(msb, 0);
			
			send_packet(0x00, 1);
		}
	}
		
/*
	send_packet(0xB1, 0);
	for(volatile uint32_t y=0; y<102; y++)
		{
			volatile uint32_t lsb = y & 0x0F;
			volatile uint32_t msb = ((y & 0xF0) >> 4) | 0x10;
			send_packet(lsb, 0); 
			send_packet(msb, 0); 
			
			send_packet(0x00, 1);
		}
	send_packet(0xB2, 0);
	for(volatile uint32_t y=0; y<102; y++)
		{
			volatile uint32_t lsb = y & 0x0F;
			volatile uint32_t msb = ((y & 0xF0) >> 4) | 0x10;
			send_packet(lsb, 0); 
			send_packet(msb, 0); 
			
			send_packet(0x00, 1);
		}
	send_packet(0xB3, 0);
	for(volatile uint32_t y=0; y<102; y++)
		{
			volatile uint32_t lsb = y & 0x0F;
			volatile uint32_t msb = ((y & 0xF0) >> 4) | 0x10;
			send_packet(lsb, 0); 
			send_packet(msb, 0); 
			
			send_packet(0x00, 1);
		}
	send_packet(0xB4, 0);
	for(volatile uint32_t y=0; y<102; y++)
		{
			volatile uint32_t lsb = y & 0x0F;
			volatile uint32_t msb = ((y & 0xF0) >> 4) | 0x10;
			send_packet(lsb, 0); 
			send_packet(msb, 0); 
			
			send_packet(0x00, 1);
		}
	send_packet(0xB5, 0);
	for(volatile uint32_t y=0; y<102; y++)
		{
			volatile uint32_t lsb = y & 0x0F;
			volatile uint32_t msb = ((y & 0xF0) >> 4) | 0x10;
			send_packet(lsb, 0); 
			send_packet(msb, 0); 
			
			send_packet(0x00, 1);
		}
	send_packet(0xB6, 0);
	for(volatile uint32_t y=0; y<102; y++)
		{
			volatile uint32_t lsb = y & 0x0F;
			volatile uint32_t msb = ((y & 0xF0) >> 4) | 0x10;
			send_packet(lsb, 0); 
			send_packet(msb, 0); 
			
			send_packet(0x00, 1);
		}
	send_packet(0xB7, 0);
	for(volatile uint32_t y=0; y<102; y++)
		{
			volatile uint32_t lsb = y & 0x0F;
			volatile uint32_t msb = ((y & 0xF0) >> 4) | 0x10;
			send_packet(lsb, 0); 
			send_packet(msb, 0); 
			
			send_packet(0x00, 1);
		}
		*/
}


void draw_dogs(){
	for(volatile uint32_t z=0; z<7; z++) //for page address
		{
			send_packet(0xB0&z, 0);
			for(volatile uint32_t y=0; y<102; y++) //for column address
				{
					volatile uint32_t lsb = y & 0x0F;
					volatile uint32_t msb = ((y & 0xF0) >> 4) | 0x10;
					send_packet(lsb, 0); 
					send_packet(msb, 0); 
					
					//send_packet(0x00, 1); from clear fn
					
					//volatile uint32_t val = current_screen[y][z];
					//send_packet(0xB&val, 1)
					
					
				}
		}
}

int static main() { 
	init_gpio(); 
	init_spi(); 
	init_dogs(); 
  
/*	while(1) { 
		draw_dogs();
	} 
*/
}
