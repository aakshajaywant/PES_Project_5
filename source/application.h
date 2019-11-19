
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

#define MODE ECHO_MODE//APPLICATION_MODE

void application_mode(char str);

#endif /* APPLICATION_H_ */
