#include "logger.h"


long int timecount=0;
void Init_Systick()
{
SysTick->LOAD =  48000000/100;
NVIC_SetPriority(SysTick_IRQn,3);
SysTick->VAL = 0;
SysTick->CTRL = 0x7;
}

void SysTick_Handler(){
timecount++;
//printf("%d",timecount);
//printf("SYSTICK WORKS");
//LED_RED_TOGGLE();
//timestamps(timecount);
}



uint8_t sec=0,min=0,hour=0;
extern long int timecount;

void timestamps(long int timer){

if(timer>600){
timer=0;
}
if(timer%10==0){
sec++;
}
if(sec!=0 && sec%60==0)
{
min++;
sec=0;
}
if(min!=0 && min%60==0)
{
hour++;
min=0;
}
if(hour>24)
  {
hour=0;
}

printf("\n \r %02d:%02d:%02d:%02lu",hour,min,sec,timer);
}



void log_level(log_mode mode)
{
    if(mode == test)
    {
        PRINTF("\n\rMODE: Test");
    }
    else if(mode == debug)
    {
         PRINTF("\n\rMODE: Debug");
    }
    else if(mode == status)
    {
        PRINTF("\n\rMODE: Status");
    }
}

void logger_func(log_func func_nm)
{
	if(func_nm == buff_initialize)
	{
		PRINTF("\r \t buff_initialize");
	}
	else if(func_nm == buff_check_full)
	{
		PRINTF("\r\tbuff_check_full");
	}
	else if(func_nm == buff_check_empty)
	{
		PRINTF("\r\tbuff_check_empty");
	}
	else if(func_nm == buff_add_item)
	{
		PRINTF("\r\tbuff_add_item");
	}
	else if(func_nm == buff_remove_item)
	{
		PRINTF("\r\tbuff_remove_item");
	}
	else if(func_nm == buff_ptr_valid)
	{
		PRINTF("\r\tbuff_ptr_valid");
	}
	else if(func_nm == buff_destroy)
	{
		PRINTF("\r\tbuff_destroy");
	}
	else
	{
		PRINTF("\r\tbuff_resize");
	}
}

void log_messages(log_mode mode,log_func func_nm)
{
	log_level(mode);
	logger_func(func_nm);
	timestamps(timecount);
}
