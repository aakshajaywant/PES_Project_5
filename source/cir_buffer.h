#include <stdint.h>

#ifndef CIR_BUFFER_H_
#define CIR_BUFFER_H_

typedef struct circ_buf{
    uint8_t *buffer;
    uint8_t *head;
    uint8_t *tail;
    uint8_t capacity;
    uint8_t count;
    uint8_t head_count;
    uint8_t tail_count;
    uint8_t *buffer_new;
} circ_buf_t;


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
}circ_status;

circ_status buff_init(circ_buf_t *p, uint8_t capacity);
circ_status buff_check_full(circ_buf_t *p,uint8_t capacity);
circ_status buff_check_empty(circ_buf_t *p);
circ_status buff_add_item(circ_buf_t *p,uint8_t item);
circ_status buff_remove_item(circ_buf_t *p);
circ_status buff_ptr_valid(circ_buf_t *p);
circ_status buff_resize(circ_buf_t *p, uint8_t capacity);
#endif




