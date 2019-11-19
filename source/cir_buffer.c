//Reference: https://stackoverflow.com/questions/827691/how-do-you-implement-a-circular-buffer-in-c

#include "cir_buffer.h"


char *head_position=0;
uint8_t tail_position=0;
ring_status r_status;
uint8_t flag = 0;


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
		p->tail_count=0;
		PRINTF("\n\rhead positionnnnnnnnn in init is %d",p->head);
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
				PRINTF("\n\rADD buffer full");
				return item_not_added_in_buff;
			}

			else if((buff_check_full(p) == buffer_empty) || (buff_check_full(p) == buffer_not_full))
			{
				*(p->buffer + p->head) = item;
				PRINTF("**************************************************************");
				PRINTF("\n\r p->buffer[p->head] character: %c",*(p->buffer + p->head));
				PRINTF("\n\r address of p->head  %p",(p->buffer + p->head));
				p->head++;
				p->count++;
				p->head_count++;
				PRINTF("\n\rhead positionnnnnnnnn incremented is now %d",p->head);
				PRINTF("\n\rhead count is %d",p->count);
				PRINTF("\n\r4TH");
				return item_added_in_buff;
			}

return 0;
}


ring_status buff_remove_item(ring_buffer *p)
{
if(p->head_count > p->tail_count)
{
	uint8_t read;
		if((p->tail == (p->capacity - 1)) && ((buff_check_empty(p) == buffer_full) || (buff_check_empty(p) == buffer_not_empty)))
		  	{
					read = *(p->buffer + p->tail);
					PRINTF("\n\r wrap around p->buffer[p->tail]: %c",read);
					PRINTF("\n\r wrap around address of p->tail  %p",(p->buffer + p->tail));
					p->tail = 0;
					p->tail_count++;
					p->count--;
					return wrap_around;
			}

		else if(buff_check_empty(p) == buffer_empty)
		{
			PRINTF("ITEM not removedddddddddddddddddd because fullllll");
			return oldest_item_not_removed;
		}
		else if((buff_check_empty(p) == buffer_full) || (buff_check_empty(p) == buffer_not_empty))
			{
				read = *(p->buffer + p->tail);
				PRINTF("\n\r p->buffer[p->tail] character: %c",read);
				PRINTF("\n\r address of p->tail  %p",(p->buffer + p->tail));
				(p->tail)++;
				p->count--;
				p->tail_count++;
				PRINTF("\n\rtail positionnnnnnnnn incremented is now %d",p->tail);
				PRINTF("\n\rcountttttttttttttttttttttttttt  nowwwwww is %d",p->count);
				return oldest_item_removed;
			}
}
else
{
	PRINTF("waitttttttttttttt");
}
return 0;
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

		p->buffer_new = (char*) realloc(p->buffer, sizeof(char)*2*(p->capacity));

		return memory_reallocated;
	}

	else
	{
		return memory_not_reallocated;
	}
}
