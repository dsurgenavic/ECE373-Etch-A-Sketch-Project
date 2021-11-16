#include "stm32l053xx.h"
#include "knob.h"
#include "queue.h"

extern queue_t input_queue;

static struct btn_struct udqa = {
		.mask_for_btn= 0<<0, 
		.pin_ptr = &(GPIOC->IDR),
		.state = UP };
static struct btn_struct udqb = {
		.mask_for_btn= 0<<0, 
		.pin_ptr = &(GPIOC->IDR),
		.state = UP };
static struct btn_struct lrqa = {
		.mask_for_btn= 0<<0, 
		.pin_ptr = &(GPIOC->IDR),
		.state = UP };
static struct btn_struct lrqb = {
		.mask_for_btn= 0<<0, 
		.pin_ptr = &(GPIOC->IDR),
		.state = UP };

static struct btn_struct pen_ud_btn = {
		.mask_for_btn= 0<<0, 
		.pin_ptr = &(GPIOC->IDR),
		.state = UP };

static enum btn_edge e_udqa;
static enum btn_edge e_udqb;
static enum btn_edge e_lrqa;
static enum btn_edge e_lrqb;

static enum btn_edge e_pud;

void update_inputs(void) {
	e_udqa = update_btn(&udqa);
	e_udqb = update_btn(&udqb);
	e_lrqa = update_btn(&lrqa);
	e_lrqb = update_btn(&lrqb);
	e_pud = update_btn(&pen_ud_btn);
	
	uint16_t message;
	
	if(e_udqa == ACTIVATING_EDGE && e_udqb == INACTIVE) {
		message = 0;
		write_q(&input_queue, message);
	} else if(e_udqa == INACTIVE && e_udqb == ACTIVATING_EDGE) {
		message = 1;
		write_q(&input_queue, message);
	}
	if(e_lrqa == ACTIVATING_EDGE && e_lrqb == INACTIVE) {
		message = 2;
		write_q(&input_queue, message);
	} else if(e_lrqa == INACTIVE && e_lrqb == ACTIVATING_EDGE) {
		message = 3;
		write_q(&input_queue, message);
	}
	if(e_pud == ACTIVATING_EDGE) {
		message = 4;
		write_q(&input_queue, message);
	}
}

void init_knobs(void){
	init_btn(1<<0, &(GPIOC->IDR), &udqa);
	init_btn(1<<1, &(GPIOC->IDR), &udqb);
	init_btn(1<<2, &(GPIOC->IDR), &lrqa);
	init_btn(1<<3, &(GPIOC->IDR), &lrqb);
	init_btn(1<<13, &(GPIOC->IDR), &pen_ud_btn);
}
