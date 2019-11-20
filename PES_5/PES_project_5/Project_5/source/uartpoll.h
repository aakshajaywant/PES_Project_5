/******************************************************************************
 *  					PES PROJECT 5
 *   AAKSHA JAYWANT (AAJA1276) & RUCHA BORWANKAR (RUBO1268)
 * 				Cross Platform IDE: MCUXpresso IDE v11
 * 					Cross-Compiler: ARM GCC
 * 						uartpoll.h
 ********************************************************************************/
/**********************************REFERENCE*********************************
http://cache.freescale.com/files/32bit/doc/quick_ref_guide/KLQRUG.pdf
*****************************************************************************/
#ifndef UARTPOLL_H_
#define UARTPOLL_H_

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#define POLLING_MODE 0
#define INTERRUPT_MODE 1

#define UART_MODE INTERRUPT_MODE //POLLING_MODE //		/**************CHANGE HERE*******************/


//extern void uart0_isr(void);
#undef VECTOR_028
#define VECTOR_028 UART0_IRQHandler()

//void uart0_isr(void);
void Init_UART0();
void UART0_Transmit_Poll(char data);
uint8_t UART0_check();
void UART0_poll_tx(char data);
void UART0_poll_putchar(char data)	;
char UART0_Receive_Poll(void);
uint8_t UART0_rec_check();
char UART0_poll_rx();
char UART0_poll_getchar();
void uart_getstr_poll(unsigned char *string);

#endif /* UARTPOLL_H_ */
