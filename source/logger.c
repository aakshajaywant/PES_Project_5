/******************************************************************************
 *  					PES PROJECT 5
 *   AAKSHA JAYWANT (AAJA1276) & RUCHA BORWANKAR (RUBO1268)
 * 				Cross Platform IDE: MCUXpresso IDE v11
 * 					Cross-Compiler: ARM GCC
 * 					       logger.c
 ********************************************************************************/
/**********************************REFERENCE*********************************
http://cache.freescale.com/files/32bit/doc/quick_ref_guide/KLQRUG.pdf

*****************************************************************************/

#include "logger.h"

long int timecount=0;

/******************SYSTICK HANDLER FOR TIMER**********************************
 WE USE THE SYSTICK HANDLER FOR 10 HZ I.E 0.1 SEC TIME WHICH INTIIATES AT THE START OF THE PROGRAM
*****************************************************************************************/
void Init_Systick()
{
SysTick->LOAD =  48000000/100;
NVIC_SetPriority(SysTick_IRQn,3);
SysTick->VAL = 0;
SysTick->CTRL = 0x7;
}
/*******WE USE THE START AND END CRITICAL SECTIONS HERE***********************/
void SysTick_Handler(){
START_CRITICAL;
timecount++;
END_CRITICAL;
}

uint8_t sec=0,min=0,hour=0;
extern long int timecount;

/******************TIMESTAMPS**********************************
 USING THE TIMECOUNTER FROM SYSTICK HANDLER WE MAKE THE TIMESTAMPS FUNCTION
 WHICH CALCULATES THE HOURS,MINS AND SECS
*****************************************************************************************/
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

printf("\t %02d:%02d:%02d:%02lu \n ",hour,min,sec,timer);
}


/******************LOG LEVEL FUNCTIONS**********************************
 	 	 	 	PRINTS THE TYPE OF MODE USED
************************************************************************/
void log_level(log_mode mode)
{
    if(mode == test)
    {
        putstr("\n\rMODE: Test");
    }
    else if(mode == debug)
    {
         putstr("\n\rMODE: Debug");
    }
    else if(mode == status)
    {
        putstr("\n\r MODE: Status");
    }
}

/******************LOG STRING MESSAGES**********************************
 THIS ARRAY GIVES THE STRING FOR PARTICULAR APPLICATION
*****************************************************************************************/
char ch_arr[40][40]={   "\t Initialize the buffer",
						"\t Checks if Buffer is full",
						"\t Checks if Buffer is Empty",
						"\t Add element to the Buffer",
						"\t Remove element from the Buffer",
						"\t Checks if Pointer to Buffer is valid",
						"\t Destroys the Buffer"
						"\t Resizes the Buffer"
						"\t Application mode"
						"\t Echo mode"
					};

void logger_func(log_func func_nm)
{
	if(func_nm == buffinitialize)
	{
		//PRINTF("\r \t buff_initialize");
		putstr("\t buff_initialize");
		putstr(ch_arr[0]);
	}
	else if(func_nm == buffcheck_full)
	{
		putstr("\t buff_check_full");
		putstr(ch_arr[1]);
	}
	else if(func_nm == buffcheck_empty)
	{
		putstr("\tbuff_check_empty");
		putstr(ch_arr[2]);
	}
	else if(func_nm == buffadd_item)
	{
		putstr("\t buff_add_item");
		putstr(ch_arr[3]);
	}
	else if(func_nm == buffremove_item)
	{
		putstr("\t buff_remove_item");
		putstr(ch_arr[4]);
	}
	else if(func_nm == buffptr_valid)
	{
		putstr("\t buff_ptr_valid");
		putstr(ch_arr[5]);

	}
	else if(func_nm == buffdestroy)
	{
		putstr("\t buff_destroy");
		putstr(ch_arr[6]);
	}
	else if(func_nm == buffresize)
	{
		putstr("\tbuff_resize");
		putstr(ch_arr[7]);
	}
	else if(func_nm == applicationmode)
	{
		putstr("\t app_mode");
		putstr(ch_arr[8]);
	}
	else
	{
		putstr("\t echo_mode");
		putstr(ch_arr[9]);
	}
}
/******************LOG MESSAGES**********************************************************
 In this function we print log mode,function name and string along with timestamps
*****************************************************************************************/
void log_messages(log_mode mode,log_func func_nm)
{
	log_level(mode);
	logger_func(func_nm);
	timestamps(timecount);
}
