/*
 * uartinterrupt.c
 *
 *  Created on: Nov 13, 2019
 *      Author: rucha
 */

//https://github.com/AlbandeCrevoisier/se203/blob/c571e86efed68c293fe762fd3538e3d9f76f9203/td/uart.c

#include "uartpoll.h"
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"


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
	PRINTF("Receiving DATA\n \r");
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
 __enable_irq();

}

#endif





















//void
//uart_puts(const char *s)
//{
//	int i= 0;
//	while (s[i] != '\0')
//		uart_int_putchar(s[i++]);
//}
//
//void
//uart_gets(char *s, int size)
//{
//	char c;
//	int i;
//	for(i = 0; i < size; i++) {
//		c = uart_int_getchar();
//		if (c == '\n' || c == '\r') {
//			s[i++] = c;
//			break;
//		} else if (c == 0) {
//			break;
//		} else {
//			s[i] = c;
//		}
//	}
//	s[i] = '\0';
//}