/******************************************************************************
 *  					PES PROJECT 5
 *   AAKSHA JAYWANT (AAJA1276) & RUCHA BORWANKAR (RUBO1268)
 * 				Cross Platform IDE: MCUXpresso IDE v11
 * 					Cross-Compiler: ARM GCC
 * 						Project_5.c
 ********************************************************************************/

#include "uartinterrupt.h"
#include "uartpoll.h"
#include "cir_buffer.h"
#include "logger.h"
#include "application.h"
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "system.h"
#include "unittest.h"

char str[100];
ring_buffer *t_buff;
ring_buffer *r_buff;
ring_status receive_status;

unsigned char string[100];
int main()
{

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    Init_Systick();
    Init_UART0();
    init_LED();
    wait_receive_led();
 /*****************************BUFFER FUNCTIONS**************************************/
    r_buff = (ring_buffer*)malloc(sizeof(ring_buffer));
    PRINTF("\n\r %d",sizeof(ring_buffer));
    receive_status = buff_initialize(r_buff, 10);
    PRINTF("\n\r Rx1 status is: %d",receive_status);
//    receive_status=buff_check_empty(r_buff);
//    PRINTF("\n \r RX status is %d",receive_status);
	if(mode == test)
	{
		putstr("************************TEST MODE ON-START UNIT TEST***********************************");
		unit_test();
	}


//while(1){

	/*********APPLICATION AND ECHO MODE*******************************/
#if MODE == APPLICATION_MODE
	log_messages(mode,applicationmode);
	#if UART_MODE == POLLING_MODE

		uart_getstr_poll(str);
	 	 putstr(str);
	 	 putstr("\n\n");
	 	app_mode(str);
#endif

	 	#if UART_MODE == INTERRUPT_MODE

		#endif

#endif

#if MODE == ECHO_MODE
	 log_messages(mode,echomode);
	#if UART_MODE == POLLING_MODE
		char a = UART0_poll_getchar();
	 	 UART0_poll_putchar(a);

	#elif UART_MODE == INTERRUPT_MODE

	#endif



#endif

//}
return 0;
}
