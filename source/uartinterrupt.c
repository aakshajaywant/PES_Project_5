/*
 * uartinterrupt.c
 *
 *  Created on: Nov 13, 2019
 *      Author: rucha
 */
//https://www.pantechsolutions.net/blog/how-to-receive-a-string-from-uart/

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

#if UART_MODE == INTERRUPT_MODE

//void UART0_Transmit_Poll(char data) {
//	while(!(UART0->S1&UART_S1_TDRE_MASK) && !(UART0->S1&UART_S1_TC_MASK));
//		UART0->D = data;
//}

uint8_t UART0_int_check()
{
	while(!(UART0->S1&UART_S1_TDRE_MASK) && !(UART0->S1&UART_S1_TC_MASK));

	return 0;
}

void UART0_int_tx(char data) {
	//PRINTF("TRANSMITTING DATA\n \r");
	UART0->D = data;
}

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

uint8_t UART0_int_rec_check()
{
	while(!(UART0->S1 & UART0_S1_RDRF_MASK));
		return 0;
}


char UART0_int_rx()
{
	//PRINTF("Receiving DATA\n \r");
	return UART0->D;
}

char UART0_int_getchar()			//rx
{
		if( UART0_int_rec_check() == 0 )
		{
			UART0_int_rx();
		}
}




void UART0_IRQHandler()
{
	__disable_irq();
	char c;

 if (UART0->S1&UART_S1_RDRF_MASK)
 {
	 //c = UART0->D;
	 c=UART0_int_getchar();

 if (!(UART0->S1&UART_S1_TDRE_MASK) && !(UART0->S1&UART_S1_TC_MASK))
 	 	 {
 //UART0->D = c;
	 	 	 UART0_int_putchar(c);
 	 	 }
 }
     rx_status = buff_add_item(r_buff,c);
 	 PRINTF("\n\rRx2 status is: %d",rx_status);
 	 rx_status=buff_resize(r_buff,c);

 __enable_irq();

}

#endif


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

