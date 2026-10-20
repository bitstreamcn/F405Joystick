################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/board.c \
../system/delay.c \
../system/fifo.c \
../system/gpio-board.c \
../system/rtc-board.c \
../system/spi-board.c \
../system/sx126x-board.c \
../system/system_gpio.c \
../system/timer.c 

C_DEPS += \
./system/board.d \
./system/delay.d \
./system/fifo.d \
./system/gpio-board.d \
./system/rtc-board.d \
./system/spi-board.d \
./system/sx126x-board.d \
./system/system_gpio.d \
./system/timer.d 

OBJS += \
./system/board.o \
./system/delay.o \
./system/fifo.o \
./system/gpio-board.o \
./system/rtc-board.o \
./system/spi-board.o \
./system/sx126x-board.o \
./system/system_gpio.o \
./system/timer.o 


# Each subdirectory must supply rules for building sources it contributes
system/%.o system/%.su system/%.cyclo: ../system/%.c system/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -DSTM32_THREAD_SAFE_STRATEGY=4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Core/ThreadSafe -I../Drivers/Radio -I../system -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-system

clean-system:
	-$(RM) ./system/board.cyclo ./system/board.d ./system/board.o ./system/board.su ./system/delay.cyclo ./system/delay.d ./system/delay.o ./system/delay.su ./system/fifo.cyclo ./system/fifo.d ./system/fifo.o ./system/fifo.su ./system/gpio-board.cyclo ./system/gpio-board.d ./system/gpio-board.o ./system/gpio-board.su ./system/rtc-board.cyclo ./system/rtc-board.d ./system/rtc-board.o ./system/rtc-board.su ./system/spi-board.cyclo ./system/spi-board.d ./system/spi-board.o ./system/spi-board.su ./system/sx126x-board.cyclo ./system/sx126x-board.d ./system/sx126x-board.o ./system/sx126x-board.su ./system/system_gpio.cyclo ./system/system_gpio.d ./system/system_gpio.o ./system/system_gpio.su ./system/timer.cyclo ./system/timer.d ./system/timer.o ./system/timer.su

.PHONY: clean-system

