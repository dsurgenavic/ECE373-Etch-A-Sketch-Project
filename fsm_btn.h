// Implement a Mealy state machine in C.


#include "stm32l053xx.h"
#include <stdint.h>

    // The state alphabet:
enum btn_status{UP, DOWN, MAYBE_PRESSED, MAYBE_RELEASED};

    // The state machine input values:
enum btn_level {BTN_ACTIVE, BTN_INACTIVE};

	// The state machine output values
enum btn_edge {ACTIVE, INACTIVE, ACTIVATING_EDGE, DEACTIVATING_EDGE};

    // The state machine's memory:
struct btn_struct{uint32_t mask_for_btn; 
                  volatile uint32_t *pin_ptr; 
                  enum btn_status state;};

    // Initialization:
void init_btn(uint32_t mask_for_btn, 
              volatile uint32_t *pin_ptr, 
              struct btn_struct *pb);

    // Collect input from HW and translate to state-input-alphabet 
enum btn_level read_btn(struct btn_struct *pb);
 
    // The state-transition table or Moore diagram written into C code
enum btn_edge update_btn(struct btn_struct *pb);



