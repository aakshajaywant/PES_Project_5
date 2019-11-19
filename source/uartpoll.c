/*****************************************************************************
 	 	 				PES PROJECT 5
  	  	  	  	  	  	  uartpoll.h


 *http://cache.freescale.com/files/32bit/doc/quick_ref_guide/KLQRUG.pdf
****************************************************************************/

#include "uartpoll.h"
#include "logger.h"
#include "uartinterrupt.h"
#include "cir_buffer.h"
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "led.h"
#include "system.h"
#include "unittest.h"


extern ring_buffer *t_buff;
extern ring_buffer *r_buff;

void Init_UART0() {

	//set port a and uart 0 for use
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	//set clock source for uart0-MCGPLLCLK
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
	SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;

	// Set pins to UART0 Rx and Tx
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Rx
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Tx

	//clear TE and RE before setting baud rate
	UART0->C2 &= ~ (UART0_C2_TE_MASK| UART0_C2_RE_MASK);

// Nested Vector Interrupt Controller (NVIC) module for interrupt mode of UART0 operation
#if UART_MODE == INTERRUPT_MODE
NVIC_EnableIRQ(UART0_IRQn);
NVIC_SetPriority(UART0_IRQn, 2);
#endif


	//UART0 set baud registers -48Mhz clock,115200 baud rate and  as oversampling
//sbr=48Mhz/(115200*16)=26
	UART0->BDH = 0x00;	//00
	UART0->BDL = 0x1A;	//26
	UART0->C4 = 0x0F;	//osr=16

	// 8-bit communication, no parity, one stop bit, LSB first, no inversion configuration

	UART0->C1 = 0x00;	//8bit,no parity check,even parity,no loop mode
	UART0->C3 = 0x00;
	UART0->MA1 = 0x00;
	UART0->MA2 = 0x00;	//
	UART0->S1 |= 0x1F;	//all errors
	UART0->S2 |= 0xC0;

#if UART_MODE == INTERRUPT_MODE
UART0->C2 = UART0_C2_RIE_MASK;
#endif
//enable transmitter and receiver
UART0->C2 |= UART0_C2_TE_MASK| UART0_C2_RE_MASK;

}

void UART0_Transmit_Poll(char data) {
	while(!(UART0->S1&UART_S1_TDRE_MASK) && !(UART0->S1&UART_S1_TC_MASK));
		UART0->D = data;
}

uint8_t UART0_check()
{
	while(!(UART0->S1&UART_S1_TDRE_MASK) && !(UART0->S1&UART_S1_TC_MASK));

	return 0;
}

void UART0_poll_tx(char data) {
	//PRINTF("TRANSMITTING DATA\n \r");
	UART0->D = data;
}

void UART0_poll_putchar(char data)			//tx
{
	init_LED();
	wait_transmit_led();
	if( UART0_check() == 0 )
	{
		UART0_poll_tx(data);

		//ring_status remove_buff = buff_remove_item(r_buff);
	}
}

char UART0_Receive_Poll(void) {
		while (!(UART0->S1 & UART0_S1_RDRF_MASK))
			;
		return UART0->D;
}

uint8_t UART0_rec_check()
{
	while(!(UART0->S1 & UART0_S1_RDRF_MASK));
		return 0;
}


char UART0_poll_rx()
{
	//PRINTF("Receiving DATA\n \r");
	return UART0->D;
}

char UART0_poll_getchar()			//rx
{
	init_LED();
	wait_receive_led();
	char rec_data;
		if( UART0_rec_check() == 0 )
		{
			rec_data = UART0_poll_rx();
#if MODE == ECHO_MODE
			ring_status add_buff = buff_add_item(r_buff, rec_data);
			PRINTF("\n \r Add_buff status %d",add_buff);
//			ring_status remove_buff = buff_remove_item(r_buff);
//			PRINTF("\n\n\rremove_buff statussssss %d",remove_buff);
#endif
		}
		return rec_data;
}


void uart_getstr_poll(unsigned char *string)  //Receive a character until carriage return or newline
{
unsigned char i=0,a=0;
while((a!='\n') && (a!='\r'))
{

if( UART0_rec_check() == 0 )
{
*(string+i)= UART0_poll_rx();
}

UART0_poll_putchar(*(string+i));

a = *(string+i);
i++;
}

//i++;
*(string+i) = '\0';
putstr(string);
}



