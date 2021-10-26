#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include  <stdlib.h> // malloc
// #define DEBUG
typedef struct {int16_t * buffer;
                uint16_t head;
                uint16_t tail;
                uint16_t max_index;
                } queue_t;
// ACQUIRE BUFFER USING MALLOC AT INITIALIZATION.

//API
void init_queue(queue_t * ptr_to_existing_q, int max_items);
bool read_q(queue_t *q0, int16_t *datum);
bool write_q(queue_t *q0, int16_t datum);
//queue_t x;
void init_q(queue_t *q0, int16_t bufsize); // Can hold (capacity = bufsize-1) integers

#endif // QUEUE_H_
