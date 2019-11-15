
 
/**
 * @file    Project_5.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "uartinterrupt.h"
#include "uartpoll.h"
#include "cir_buffer.h"


int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    PRINTF("Hello World\n");

    char a;
       while(1){
// 		UART0_Transmit_Poll(a);
//		char read=UART0_Receive_Poll();
//		PRINTF("\n \r %d",read);
//      while(1){
//      char read=UART0_Receive_Poll();
//      UART0_Transmit_Poll(read);
//      UART0_rec_check();
//      char i=UART0_poll_rx();
//      UART0_rec_check();
       a=UART0_poll_getchar();
       UART0_poll_putchar(a);

   }

    return 0 ;
}
