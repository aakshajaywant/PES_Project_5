#ifndef LED_H_

#define LED_H_
#include <stdint.h>
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "logger.h"
#include "uartinterrupt.h"
#include "uartpoll.h"
#include "fsl_debug_console.h"
#include "cir_buffer.h"
#include "unittest.h"
#include "system.h"
#include "application.h"


void init_LED(void);
void wait_receive_led(void);
void wait_transmit_led(void);
void delay(uint32_t d);
void error_led();
#endif
