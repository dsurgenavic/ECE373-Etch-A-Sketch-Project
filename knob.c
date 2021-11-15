#include "stm32l053xx.h"
#include "knob.h"
#include "queue.h"

extern queue_t input_queue;

static struct btn_struct udqa;
static struct btn_struct udqb;
static struct btn_struct lrqa;
static struct btn_struct lrqb;

static struct btn_struct pen_ud_btn;

static enum btn_edge e_udqa = INACTIVE;
static enum btn_edge e_udqb = INACTIVE;
static enum btn_edge e_lrqa = INACTIVE;
static enum btn_edge e_lrqb = INACTIVE;

static enum btn_edge e_pud = INACTIVE;

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
	
	if(e_udqa == ACTIVATING_EDGE) {
		GPIOC->ODR ^= 1<<8;
		GPIOC->ODR ^= 1<<8;
	}
}

void init_knobs(void){
	init_btn(1<<1, &(GPIOB->IDR), &udqa);
	init_btn(1<<2, &(GPIOB->IDR), &udqb);
	init_btn(1<<3, &(GPIOB->IDR), &lrqa);
	init_btn(1<<4, &(GPIOB->IDR), &lrqb);
	init_btn(1<<13, &(GPIOC->IDR), &pen_ud_btn);
}
