# PES_Project_5

Author: AAKSHA JAYWANT & RUCHA BORWANKAR
Project Name: UART Communications with PC 

---------------------
|| FILE CONTENTS:- ||
---------------------

PES_Project_5

	-Includes
	-CMSIS
	-board
	-drivers
	-source
		-application.c
   		-application.h
   		-cir_buffer.c
  		-cir_buffer.h
		-led.c
		-led.h
		-logger.c
		-logger.h
		-Project_5.c
		-system.c
		-system.h
		-uartinterrupt.c
		-uartinterrupt.h
		-uartpoll.c
		-uartpoll.h
		-unittest.c
		-unittest.h
	-startup
	-utilities
	-Debug
	-README.md

-------------------------------
|| EXECUTION INSTRUCTIONS :- ||
-------------------------------

Following listed steps should be used for running the program in MCUXPresso IDE:-


1)Change the "#define UART_MODE INTERRUP_MODE //POLLING_MODE" in the "uartpoll.h" file to swtich between interrupt mode or polling mode.

2)Change the "#define MODE APPLICATION_MODE //ECHO_MODE" in the "application.h" file to switch between application mode or echo mode.

3)To choose amongst test, debug and status mode, change the "#define mode debug //test //status" in the "logger.h" file.

4)To check remove buffer function go to ->"uartpoll.c" ->"UART0_poll_getchar()" ->uncomment "ring_status remove_buff = buff_remove_item(r_buff); AND 
					"PRINTF("\n\n\rremove_buff statussssss %d",remove_buff);"

5)Build the program

6)Debug as GDB PEMicro Interface Debugger

-------------------------
|| TASKS UNDERTAKEN :- ||
-------------------------

Part 1. UART-based Communications with PC Terminal Program

1)Circular Buffer
c-Function to add a new item to a buffer 

	-Function to remove oldest item from a buffer
	-Function to check is buffer full
	-Function to check is buffer empty
	-Function to verify buffer is initialized
	-Function to verify the buffer pointer is valid
	-Function to initialize a buffer
	-Function to destroy a buffer

2)UART Device Driver 1 – Blocking/Polled

3)UART Device Driver 2 – Non-blocking/Interrupt

4)Unit Testing

	-Create a buffer
	-Test data access
	-Verify wrap remove 
	-Verify wrap add 
	-Overfill 
	-Over empty 
	-Destroy the buffer

5)Identify Critical Sections i.e. operations that should not be interrupted in systick and UART0_IRQHandler()

6)Logging – added timestamps using systick handler at 10Hz

7)LEDs

8)Extra Credit (10 points) – Extending Circular Buffers
	-function added to (reallocate) memory to resize a circular buffer in a situation (such as the report storage) when an overfill error occurs
	-Included test of this function in the uCUnit test case suite


Part 2. Capture Oscilloscope trace of UART traffic between KL25Z and the PC
		-Annotate the image of the UART transaction showing start, data and stop bits.

Part 3. FMEA (Failure Modes and Effects Analysis) document for the project











 


 
					
