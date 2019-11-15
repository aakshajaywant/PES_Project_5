/*
 * uartinterrupt.h
 *
 *  Created on: Nov 13, 2019
 *      Author: rucha
 */

#ifndef UARTINTERRUPT_H_
#define UARTINTERRUPT_H_


#if UART_MODE == INTERRUPT_MODE
char UART0_int_getchar();
uint8_t UART0_int_check();
void UART0_int_tx(char data);
void UART0_int_putchar(char data);
uint8_t UART0_int_rec_check();
char UART0_int_rx();
char UART0_int_getchar();
void UART0_IRQHandler();
#endif
#endif /* UARTINTERRUPT_H_ */
