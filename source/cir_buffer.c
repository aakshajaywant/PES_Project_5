//Reference: https://stackoverflow.com/questions/827691/how-do-you-implement-a-circular-buffer-in-c

#include "cir_buffer.h"


char *head_position=0;
uint8_t tail_position=0;
ring_status r_status;

ring_status buff_initialize(ring_buffer *p, uint8_t capacity)
{
	if(p == NULL || capacity <= 0)
	{
		return buffer_init_not_done;

	}
	else
	{
		p->buffer = (char*) malloc(sizeof(char)*capacity);
		p->head = 0;
		p->tail = 0;
		p->capacity = capacity;
		p->count = 0;
		p->head_count=0;
		PRINTF("\n\rhead positionnnnnnnnn in init is %d",p->head);
		PRINTF("\n\rCapacity isssssssssssssss:%d",capacity);
		PRINTF("\n\rhead_position is at: %p",head_position);
		return buffer_init_done;
		if(p == NULL)
		{
			return buffer_init_not_done;
		}

	}
}

ring_status buff_check_full(ring_buffer *p)
{

	if(p == NULL)
	{
		buff_ptr_valid(p);
	}
	else if(p->count == p->capacity)
	{
		return buffer_full;
	}
	else if (p->count == 0)
	{
		return buffer_empty;
	}

		return buffer_not_full;

}

ring_status buff_check_empty(ring_buffer *p)
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
	else if(p->count == p->capacity)
		{
			return buffer_full;
		}

			return buffer_not_empty;
}


ring_status buff_add_item(ring_buffer *p,char item)
{
uint8_t buff_read;
ring_status stat;
			if((p->head == (p->capacity - 1)) && ((buff_check_full(p) == buffer_empty) || (buff_check_full(p) == buffer_not_full)))
			{

				*(p->buffer + p->head) = item;
				PRINTF("\n\r wrap around p->buffer[p->head]: %c",*(p->buffer + p->head));
				PRINTF("\n\r wrap around address of p->head  %p",(p->buffer + p->head));
				p->head = 0;
				p->count++;
				p->head_count++;
				PRINTF("\n \r 1ST");
				return wrap_around;
			}
			else if(buff_check_full(p) == buffer_full)
			{
				return item_not_added_in_buff;
			}

//	else if(p->head == 0)
//		{
//
//			p->head = 0;
//			//*(p->head) = *(p->buffer);
//			*(p->buffer + p->head) = item;;
//			(p->count)++;
//			p->head_count++;
//			PRINTF("2nd");
//			return item_added_in_buff;
//		}
//	else if(p->head_count < p->tail_count)
//	{
//		PRINTF("3RD");
//			return item_not_a b dded_in_buff;
//	}
			else if((buff_check_full(p) == buffer_empty) || (buff_check_full(p) == buffer_not_full))
			{
				*(p->buffer + p->head) = item;
				PRINTF("\n\r p->buffer[p->head]: %c",*(p->buffer + p->head));
				PRINTF("\n\r address of p->head  %p",(p->buffer + p->head));
				p->head++;
				p->count++;
				p->head_count++;
				PRINTF("\n\rheads positionnnnnnnnn increment is now %d",p->head);
				PRINTF("\n\rhead countttttttttttttttttttttttttt is %d",p->head);
				PRINTF("\n\rhead count is %d",p->head_count);
				PRINTF("\n\r4TH");
				return item_added_in_buff;
			}



}


ring_status buff_remove_item(ring_buffer *p)
{

	uint8_t read;
		if((p->tail == (p->capacity - 1)) && ((buff_check_empty(p) == buffer_full) || (buff_check_empty(p) == buffer_not_empty)))
		  	{
					read = *(p->buffer + p->tail);
					p->tail = 0;
					p->tail_count++;
					p->count--;
					return wrap_around;
			}
//		else if(p->count == ((p->capacity)-1))
//			{
//				p->tail = 0;
//				read = (p->tail);
//				tail_position = (p->tail)++;
//				p->tail_count++;
//				(p->count)--;
//				return oldest_item_removed;
//			}
//		else if(p->head_count < p->tail_count)
//			{
//				return oldest_item_not_removed;
//			}
		else if(buff_check_empty(p) == buffer_empty)
		{
			return oldest_item_not_removed;
		}
		else if((buff_check_empty(p) == buffer_full) || (buff_check_empty(p) == buffer_not_empty))
			{
				read = *(p->buffer + p->tail);
				(p->tail)++;
				p->count--;
				p->tail_count++;
				return oldest_item_removed;
			}

}




ring_status buff_destroy(ring_buffer *p)
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


ring_status buff_ptr_valid(ring_buffer *p)
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


ring_status buff_resize(ring_buffer *p,char item)
{
	if(p->count == p->capacity)
	{
		PRINTF("\n \r *****************************************************");
		PRINTF("\n \r Buffer is extended");
		p->buffer_new = (char*) realloc(p->buffer, sizeof(char)*(p->capacity));
		r_status = buff_initialize(p->buffer_new, 6);
		PRINTF("\n \r Buffer is extended at address %p",p->buffer_new);
		PRINTF("\n\r New buffer Rx1 status is: %d",r_status);
		p->count=0;
		r_status=buff_add_item(p->buffer_new,item);
		PRINTF("\n \r The New buffer has values with status as %d \n \n \r",r_status);
		PRINTF("\n \r *****************************************************");
		return memory_reallocated;
	}

	else
	{
		return memory_not_reallocated;
	}
}
