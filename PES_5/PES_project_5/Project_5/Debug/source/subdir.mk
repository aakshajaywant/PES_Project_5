################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Project_5.c \
../source/application.c \
../source/cir_buffer.c \
../source/led.c \
../source/logger.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/system.c \
../source/uartinterrupt.c \
../source/uartpoll.c \
../source/unittest.c 

OBJS += \
./source/Project_5.o \
./source/application.o \
./source/cir_buffer.o \
./source/led.o \
./source/logger.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/system.o \
./source/uartinterrupt.o \
./source/uartpoll.o \
./source/unittest.o 

C_DEPS += \
./source/Project_5.d \
./source/application.d \
./source/cir_buffer.d \
./source/led.d \
./source/logger.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/system.d \
./source/uartinterrupt.d \
./source/uartpoll.d \
./source/unittest.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


