//Display(task 3) header file
//Reads from array (from previous task)-> writes to display 
  
/*
WIRING: 
	DOGS	
		15|---||-GND 
		16|-------, 
		17|--||,  | 
		18|----'  | 
		19|----||-' 
		20|--GND 
		21|--GND 
		22|--3.3v 
		23|--3.3v 
		24|--SDA--NUCLEO PA7 --D11 
		25|--SCK--NUCLEO PA5 --D13 
		26|--CD---NUCLEO PA6 --D12 
		27|--RST--NUCLEO PA8 --D7 
		28|--CS0--NUCLEO PA4 --A2 
*/
#include "stm32l052xx.h" 
//extern queue - for importing the queue needed to use the array

void init_gpio(void); 
void init_spi(void); 
void send_packet(uint32_t packet, uint8_t CD); 
void init_dogs(void);
void clear_dogs(void);

void draw_dogs(void);
