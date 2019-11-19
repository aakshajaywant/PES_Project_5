/*

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    project5.c
 * @brief   Application entry point.
 */
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
