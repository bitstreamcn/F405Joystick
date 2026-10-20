################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Board/Board.c 

C_DEPS += \
./Drivers/Board/Board.d 

OBJS += \
./Drivers/Board/Board.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Board/%.o Drivers/Board/%.su Drivers/Board/%.cyclo: ../Drivers/Board/%.c Drivers/Board/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_MODEM_LORA -DUSE_BAND_915 -DUSE_TCXO -DUSE_HAL_DRIVER -DSTM32F405xx -DSTM32_THREAD_SAFE_STRATEGY=4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Core/ThreadSafe -I../Drivers/Radio -I"M:/STM32CubeIDE/workspace/F405Joystick/App" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Board

clean-Drivers-2f-Board:
	-$(RM) ./Drivers/Board/Board.cyclo ./Drivers/Board/Board.d ./Drivers/Board/Board.o ./Drivers/Board/Board.su

.PHONY: clean-Drivers-2f-Board

