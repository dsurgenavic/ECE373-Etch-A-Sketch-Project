#include "storage.h"

void init_display_mem(void) {
	for(uint8_t i = 0; i < 102; i++) {
		for(uint8_t j = 0; j < 8; j++) {
			display_mem[i][j] = 0x00;
		}
	}
}

void update_cursor_location() {
	
}

void write_storage() {

}
