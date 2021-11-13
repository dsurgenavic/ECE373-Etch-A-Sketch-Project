#include "storage.h"

uint8_t display_mem[102][8];
uint16_t cursor_x_pos = 0x01;
uint16_t cursor_y_pos = 0x01;
uint16_t pen_up_down;

void init_display_mem(void) {
	for(uint8_t i = 0; i < 102; i++) {
		for(uint8_t j = 0; j < 8; j++) {
			display_mem[i][j] = 0x00;
		}
	}
}

void update_cursor_location(void) {
	int16_t data;
	if(!read_q(&input_queue, &data)) return;
	switch(data){
		case(0): //TODO: Change '0' to x knob turning clockwise
			cursor_y_pos = (cursor_y_pos >= 101) ? 101 : (cursor_y_pos + 1);
			break;
		case(1): //TODO: Change '1' to x knob turning counterclockwise
			cursor_y_pos = (cursor_y_pos <= 0) ? 0 : (cursor_y_pos - 1);
			break;
		case(2): //TODO: Change '2' to y knob turning clockwise
			cursor_x_pos = (cursor_x_pos >= 63) ? 63 : (cursor_x_pos + 1);
			break;
		case(3): //TODO: Change '3' to y knob turning counterclockwise
			cursor_x_pos = (cursor_x_pos <= 0) ? 0 : (cursor_x_pos - 1);
			break;
		default:
			break;
	}
}

void toggle_pen(void) {
	int16_t data;
	if(!read_q(&input_queue, &data)) return;
	if(data == 4) pen_up_down ^= pen_up_down;//TODO: Change '0' to button rising edge detected.
	
}

void write_storage(void) {
	uint16_t page = cursor_y_pos / 8;
	uint16_t page_y = cursor_y_pos % 8;
	
	bool check = write_q(&display_mem_semaphore, 1);
	if(!check) return;
	
	if(!pen_up_down){
		display_mem[cursor_x_pos][page] &= ~(1<<page_y);
	}
	else{
		display_mem[cursor_x_pos][page] |= 1<<page_y;
	}
	
	int16_t dummy;
	check = read_q(&display_mem_semaphore, &dummy);
}

void update_storage(void) {
	toggle_pen();
	update_cursor_location();
	write_storage();
}
