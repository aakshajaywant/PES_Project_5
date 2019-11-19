/******************************************************************************
 *  					PES PROJECT 5
 *   AAKSHA JAYWANT (AAJA1276) & RUCHA BORWANKAR (RUBO1268)
 * 				Cross Platform IDE: MCUXpresso IDE v11
 * 					Cross-Compiler: ARM GCC
 * 						uartinterrupt.c
 ********************************************************************************/
 /**************References******************************************************
  https://www.pantechsolutions.net/blog/how-to-receive-a-string-from-uart/
*********************************************************************************/
#include "uartinterrupt.h"
#include "uartpoll.h"
#include "cir_buffer.h"
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

extern char str[100];
extern ring_buffer *r_buff;
ring_status	rx_status;

/***************************UART INTERRUPT MODE FUNCTIONS**********************
 In this file we have set of functions we use to transmit and receive characters
 using UART0 INTERRUPT MODE.
*****************************************************************************/
#if UART_MODE == INTERRUPT_MODE

//void UART0_Transmit_Poll(char data) {
//	while(!(UART0->S1&UART_S1_TDRE_MASK) && !(UART0->S1&UART_S1_TC_MASK));
//		UART0->D = data;
//}
/*********UART INTERRUPT MODE FUNCTION-Checks for transmission**********************
 In this function the Initial condition of transmission i.e we use
 it to check if transmit is availabe.
*****************************************************************************/

uint8_t UART0_int_check()
{
	while(!(UART0->S1&UART_S1_TDRE_MASK) && !(UART0->S1&UART_S1_TC_MASK));

	return 0;
}

/*********UART INTERRUPT MODE FUNCTION-Transmits data**********************************
 In this function we take a character and transmit data assuming transmit is available.
*****************************************************************************************/
void UART0_int_tx(char data) {
	//PRINTF("TRANSMITTING DATA\n \r");
	UART0->D = data;
}
/*********UART INTERRUPT MODE FUNCTION-Transmits data**********************************
 In this function we take a character in function and use the above functions to transmit data.
*****************************************************************************************/
void UART0_int_putchar(char data)			//tx
{
	if( UART0_int_check() == 0 )
	{
		UART0_int_tx(data);
	}
}

//char UART0_Receive_Poll(void) {
//		while (!(UART0->S1 & UART0_S1_RDRF_MASK))
//			;
//		return UART0->D;
//}

/*********UART INTERRUPT MODE FUNCTION-Checks for receiving condition**********************
 In this function the Initial condition of receiving data i.e we use
 it to check if receive is available.
*****************************************************************************/

uint8_t UART0_int_rec_check()
	{
		while(!(UART0->S1 & UART0_S1_RDRF_MASK));
		return 0;
	}

/*********UART INTERRUPT MODE FUNCTION-Receives data**********************************
 In this function we return a character assuming receive is available.
*****************************************************************************************/
char UART0_int_rx()
{
	//PRINTF("Receiving DATA\n \r");
	return UART0->D;
}
/******************UART INTERRUPT MODE FUNCTION-Receives data**********************************
 In this function we return character and use the above 2 functions to receive data.
*****************************************************************************************/
char UART0_int_getchar()			//rx
{
	char a;
		if( UART0_int_rec_check() == 0 )
		{
			a=UART0_int_rx();
		}
		return a;
}

/******************UART INTERRUPT MODE FUNCTION-Receives data**********************************
 In this function we get string from the user.
*****************************************************************************************/
void uart_getstr_int(unsigned char *string)  //Receive a character until carriage return or newline
{
unsigned char i=0,a=0;
while((a!='\n') && (a!='\r'))
{
*(string+i)= UART0_int_getchar();
UART0_int_putchar(*(string+i));
a = *(string+i);
i++;
}

//i++;
*(string+i) = '\0';

}
/***************************UART INTERRUPT HANDLER**********************
 In this IRQ handler,when interrupt occurs then it jumps to this as service routine
 and executes the following:
 1.transmits data
 2.receives data
 3.In application mode,it gets string from user and when enter key is pressed
 it presents a report of all the characters entered to the terminal
 4.In echo mode,it stores data to buffer
 5.We use the start and end critical sections here.
*****************************************************************************/
void UART0_IRQHandler()
{
//__disable_irq();
START_CRITICAL;
	char c;
#if MODE==APPLICATION_MODE
 PRINTF("\n \r APPLICATION MODE ON \n \r");
 uart_getstr_int(str);
 putstr(str);
 putstr("\n \n");
 app_mode(str);

#endif


  if (UART0->S1 & UART_S1_RDRF_MASK)
  {
  //c = UART0->D;
  init_LED();
  wait_receive_led();
  c=UART0_int_getchar();

  if (!(UART0->S1&UART_S1_TDRE_MASK) && !(UART0->S1&UART_S1_TC_MASK))
  {
  //UART0->D = c;
  init_LED();
  wait_transmit_led();
  UART0_int_putchar(c);
  }
  }

#if MODE==ECHO_MODE
     rx_status = buff_add_item(r_buff,c);
  PRINTF("\n\rRx2 status is: %d",rx_status);
  rx_status=buff_resize(r_buff,c);
#endif
 //__enable_irq();
END_CRITICAL;
}

#endif

/***************************UART FUNCTIONS*********************************************
 This is the putstring condition in case we need to print strings without standard APIs.
***************************************************************************************/

void putstr(unsigned char *string)
{

//unsigned char a=0;
while(*string){
//for(uint32_t i=0;i<=strlen(str);i++)

#if UART_MODE == INTERRUPT_MODE
UART0_int_putchar(*string++);
#endif

UART0_poll_putchar(*(string++));

//UART0_poll_putchar(*(string+strlen(str))) = '\0';
}
}

