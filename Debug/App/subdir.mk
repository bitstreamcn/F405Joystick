################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/AdcToChannel.c \
../App/Application.c \
../App/CRSFRadio.c 

C_DEPS += \
./App/AdcToChannel.d \
./App/Application.d \
./App/CRSFRadio.d 

OBJS += \
./App/AdcToChannel.o \
./App/Application.o \
./App/CRSFRadio.o 


# Each subdirectory must supply rules for building sources it contributes
App/%.o App/%.su App/%.cyclo: ../App/%.c App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_MODEM_LORA -DUSE_BAND_915 -DUSE_TCXO -DUSE_HAL_DRIVER -DSTM32F405xx -DSTM32_THREAD_SAFE_STRATEGY=4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Core/ThreadSafe -I../Drivers/Radio -I"M:/STM32CubeIDE/workspace/F405Joystick/App" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App

clean-App:
	-$(RM) ./App/AdcToChannel.cyclo ./App/AdcToChannel.d ./App/AdcToChannel.o ./App/AdcToChannel.su ./App/Application.cyclo ./App/Application.d ./App/Application.o ./App/Application.su ./App/CRSFRadio.cyclo ./App/CRSFRadio.d ./App/CRSFRadio.o ./App/CRSFRadio.su

.PHONY: clean-App

