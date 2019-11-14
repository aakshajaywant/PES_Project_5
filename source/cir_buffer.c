//Reference: https://stackoverflow.com/questions/827691/how-do-you-implement-a-circular-buffer-in-c

#include "cir_buffer.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

uint8_t *head_position;
uint8_t *tail_position;


circ_status buff_init(circ_buf_t *p, uint8_t capacity)
{
	if(p == NULL || capacity <= 0)
	{
		return buffer_init_not_done;
	}
	else
	{
		p->buffer = (uint8_t*) malloc(sizeof(uint8_t)*capacity);
		p->head = p->buffer;
		p->tail = p->buffer;
		p->capacity = capacity;
		p->count = 0;
		p->head_count=0;
		return buffer_init_done;
		if(p == NULL)
		{
			return buffer_init_not_done;
		}
	}
}

circ_status buff_check_full(circ_buf_t *p,uint8_t capacity)
{

	if(p == NULL)
	{
		buff_ptr_valid(p);
	}
//	else if(p->tail == (((p->head)+1)%capacity))
//	{
//		return buffer_full;
//	}
	else if(p->count == p->capacity)
	{
		return buffer_full;
	}
	//else
	//{
		return buffer_not_full;
	//}
}

circ_status buff_check_empty(circ_buf_t *p)
{
	if(p == NULL)
		{
		buff_ptr_valid(p);
		}
//		{
//			return buffer_empty;
//		}
	else if(p->count == 0)
		{
			return buffer_empty;
		}
	//else
		//{
			return buffer_not_empty;
		//}
}


circ_status buff_add_item(circ_buf_t *p,uint8_t item)
{

	if(p->head == (p->buffer + p->capacity - 1))
		{
			//p->head = ((p->capacity)-1);
			*p->head = item;
			p->head = p->buffer;
			p->head_count++;
			p->count++;
			return wrap_around;
		}
	else if(p->count == p->capacity)
		{
			p->head = p->buffer;
			//*(p->head) = *(p->buffer);
			item = *(p->head);
			head_position = p->head++;
			p->head_count++;
			(p->count)++;
			return item_added_in_buff;
		}
	else if(p->head_count > p->tail_count)
	{
			return item_not_added_in_buff;
	}
	else
		{
			*p->head = item;
			head_position = p->head++;
			p->head_count++;
			p->count++;
			return item_added_in_buff;
		}

}


circ_status buff_remove_item(circ_buf_t *p)
{

	uint8_t read;
		if(p->tail == (p->buffer + p->capacity - 1))
		  	{
					//p->tail = ((p->capacity)-1);
					read = *(p->tail);
					p->tail_count++;
					p->count--;
					p->tail = p->buffer;
					return wrap_around;
			}
		else if(p->count == ((p->capacity)-1))
			{
				p->tail = p->buffer;
				read = *(p->tail);
				tail_position = (p->tail)++;
				p->tail_count++;
				(p->count)--;
				return oldest_item_removed;
			}
		else if(p->head_count > p->tail_count)
			{
				return oldest_item_not_removed;
			}
		else
			{
				read = *(p->tail);
				tail_position = (p->tail)++;
				p->count--;
				p->tail_count++;
				return oldest_item_removed;
			}


}




circ_status buff_destroy(circ_buf_t *p)
{
		if(p == NULL)
		{
		buff_ptr_valid(p);
		}
		//else
		//{
		free(p->buffer);
		//free(buffer);
		return buffer_destroyed;
		//}

}


circ_status buff_ptr_valid(circ_buf_t *p)
{
	if(p == NULL)
		{
			return FAIL;
		}
	else
	{
		return SUCCESS;
	}
}


circ_status buff_resize(circ_buf_t *p, uint8_t capacity)
{
	if(p->count == p->capacity)
	{
		p->buffer_new = (uint8_t*)  realloc(p->buffer, sizeof(uint8_t)*capacity);
		return memory_reallocated;
	}
	else
	{
		return memory_not_reallocated;
	}
}
