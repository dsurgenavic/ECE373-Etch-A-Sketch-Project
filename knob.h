#ifndef KNOB_H_
#define KNOB_H_

#include "stdint.h"
#include "fsm_btn.h"


enum input_messages {UD_UP, UD_DOWN, LR_RIGHT, LR_LEFT, BTN_PRESS};

void update_inputs(void);

void init_knobs(void);

#endif
