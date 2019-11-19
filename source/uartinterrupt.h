/******************************************************************************
 *  					PES PROJECT 5
 *   AAKSHA JAYWANT (AAJA1276) & RUCHA BORWANKAR (RUBO1268)
 * 				Cross Platform IDE: MCUXpresso IDE v11
 * 					Cross-Compiler: ARM GCC
 * 						uartinterrupt.h
 ********************************************************************************/
/**********************************REFERENCE*********************************
http://cache.freescale.com/files/32bit/doc/quick_ref_guide/KLQRUG.pdf

*****************************************************************************/
#ifndef UARTINTERRUPT_H_
#define UARTINTERRUPT_H_
#include<stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*****************CRITICAL SECTION*********************/
#define START_CRITICAL __disable_irq()
#define END_CRITICAL  __enable_irq()
/*****************************************************/

#if UART_MODE == INTERRUPT_MODE
char UART0_int_getchar();
uint8_t UART0_int_check();
void UART0_int_tx(char data);
void UART0_int_putchar(char data);
uint8_t UART0_int_rec_check();
char UART0_int_rx();
char UART0_int_getchar();
void UART0_IRQHandler();
void uart_getstr(unsigned char *string);
void uart_putstr(unsigned char *string);
void putstr(unsigned char *string);
void uart_getstr_int(unsigned char *string);
#endif
#endif /* UARTINTERRUPT_H_ */
