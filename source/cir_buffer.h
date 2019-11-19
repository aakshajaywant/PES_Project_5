

#ifndef CIR_BUFFER_H_
#define CIR_BUFFER_H_

#include "uartpoll.h"
#include "uartinterrupt.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "logger.h"
#include "led.h"

typedef struct ring_buf{
    char *buffer;
    uint8_t head;
    uint8_t tail;
    uint8_t capacity;
    uint8_t count;
    uint8_t head_count;
    uint8_t tail_count;
    char *buffer_new;
}ring_buffer;


typedef enum{
SUCCESS = 0,
FAIL,
buffer_full,
buffer_not_full,
buffer_empty,
buffer_not_empty,
buffer_init_done,
buffer_init_not_done,
buffer_ptr_valid,
buffer_ptr_invalid,
buffer_destroyed,
buffer_not_destoryed,
item_added_in_buff,
item_not_added_in_buff,
oldest_item_removed,
oldest_item_not_removed,
wrap_around,
memory_reallocated,
memory_not_reallocated
}ring_status;

ring_status buff_initialize(ring_buffer *p, uint8_t capacity);
ring_status buff_check_full(ring_buffer *p);
ring_status buff_check_empty(ring_buffer *p);
ring_status buff_add_item(ring_buffer *p,char item);
ring_status buff_remove_item(ring_buffer *p);
ring_status buff_ptr_valid(ring_buffer *p);
ring_status buff_resize(ring_buffer *p,char item);
ring_status buff_destroy(ring_buffer *p);
#endif




