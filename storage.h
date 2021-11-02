#include "stdint.h"

#ifndef STORAGE_H_
#define STORAGE_H_

//This is an array of display data. Because we can't read what is on the screen at any given time,
//the program will use this array. This array will be written to and read from by the program.
//The display driver will read from this and write to the display
extern uint8_t display_mem[102][8];
	

static uint8_t cursor_x_pos;
static uint8_t cursor_y_pos;

void init_display_mem(void);



//This function will update the cursor's current location.
//This will use the knob state machine to update coordinates,
//and will blink an area in the display array depending on the coordinates.a
void update_cursor_location(void);



//This function will update the display array.
//It will use the cursor's current location and whether the pen
//is up or down to write a pixel in the display array.
void write_storage(void);
	




#endif //STORAGE_H_
