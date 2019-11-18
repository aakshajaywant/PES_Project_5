#ifndef LOGGER_H_
#define LOGGER_H_



#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"


typedef enum
{
	test = 0,
	debug,
	status
}log_mode;

typedef enum
{
	buff_initialize = 0,
	buff_check_full,
	buff_check_empty,
	buff_add_item,
	buff_remove_item,
	buff_ptr_valid,
	buff_destroy,
	buff_resize
}log_func;

char ch_arr[40][40]={   "",
						"Temperature average",
						"Temperature alert mode",
						"Temperature Disconnect",
						"LED is initialized",
						"Switches to Other State Machine"
					};

#define mode debug
//#define func INITIALIZE_buffer

void log_level(log_mode mode);
void logger_func(log_func func_nm);
void log_messages(log_mode mode,log_func func_nm);

#endif
