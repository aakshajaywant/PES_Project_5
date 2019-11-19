#include "led.h"

void init_LED(void);
void start(void);
void error(void);
void _end(void);

void init_LED(void)
{
      LED_BLUE_INIT(1);
      LED_RED_INIT(1);
      LED_GREEN_INIT(1);
}

void wait_receive_led(void)		//temp alert state
{
	LED_RED_OFF();
	LED_GREEN_OFF();
	LED_BLUE_ON();
	delay(10);
}

void error_led(void)	//error or disconnected state
{
	LED_GREEN_OFF();
	LED_BLUE_OFF();
	LED_RED_ON();
	delay(10);
}

void wait_transmit_led(void)	//temp reading state
{
	LED_RED_OFF();
	LED_BLUE_OFF();
	LED_GREEN_ON();
	delay(10);
}

void delay(uint32_t d)
{
	uint32_t count = d*7000;	/****** As clock is 8MHz *****/
	while(count!=0)
	{
count--;/***** Wasting MCU cycles to get the desired delay ******/
	}
}


