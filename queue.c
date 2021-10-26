#include "queue.h"

void init_queue(queue_t * ptr_to_existing_q, int max_items)
{
    int16_t * new_buff = (int16_t *const) malloc((max_items+1) * sizeof(int16_t));
    ptr_to_existing_q ->buffer = new_buff;
    ptr_to_existing_q ->head = 0;
    ptr_to_existing_q ->tail = 0;
    ptr_to_existing_q ->max_index = max_items;
}


bool read_q(queue_t *q0, int16_t *datum){
    // datum is writable parameter.
    // Can write to *q0, but cannot change q0
    #ifdef DEBUG
        printf("Head @ %d, Tail @ %d\n", (int)(q0->head), (int)(q0->tail));
    #endif
    bool success = false;
//// BEGIN CRITICAL SECTION – NO INTERRUPTS ////
    if (q0->head == q0->tail){ // empty
      *datum = 0;
      success = false; //{datum==0,success == false}
    }else{
         *datum = (q0->buffer)[q0->head]; // acquire data @(buffer[head])
         q0->head++;
         if ((q0->head) > q0->max_index) q0->head=0;
         success = true;
    }
//// END CRITICAL SECTION ////
    return success;
}


bool write_q(queue_t *q0, int16_t datum){
    #ifdef DEBUG
        printf("Head @ %d, Tail @ %d\n", (int)(q0->head), (int)(q0->tail));
    #endif
    uint16_t new_tail = q0->tail + 1;
    if (new_tail > q0->max_index) new_tail = 0;
    if (new_tail == q0->head) return false; //queue full = error
    else{
        (q0->buffer)[q0->tail] = datum;  // access as (ptr)[int] see read_q
        q0->tail = new_tail;
    }
    return true;
}
