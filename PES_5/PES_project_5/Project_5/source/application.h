/******************************************************************************
 *  					PES PROJECT 5
 *   AAKSHA JAYWANT (AAJA1276) & RUCHA BORWANKAR (RUBO1268)
 * 				Cross Platform IDE: MCUXpresso IDE v11
 * 					Cross-Compiler: ARM GCC
 * 						application.h
 ********************************************************************************/
/**********************************REFERENCE*********************************
https://www.programmingsimplified.com/c-program-find-characters-frequency
*****************************************************************************/
#ifndef APPLICATION_H_
#define APPLICATION_H_

#define ECHO_MODE 0
#define APPLICATION_MODE 1

#include "uartpoll.h"
#include "logger.h"
#include "uartpoll.h"
#include "uartinterrupt.h"
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "cir_buffer.h"
#include "led.h"
#include "unittest.h"
#include "system.h"

#define MODE ECHO_MODE//APPLICATION_MODE//			/**************CHANGE HERE*******************/

void app_mode(char string[]);

#endif /* APPLICATION_H_ */
