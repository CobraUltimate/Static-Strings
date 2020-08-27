################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/carro/STM32CubeIDE/workspace_1.4.0/static_strings/src/static_strings.c 

OBJS += \
./src/static_strings.o 

C_DEPS += \
./src/static_strings.d 


# Each subdirectory must supply rules for building sources it contributes
src/static_strings.o: C:/Users/carro/STM32CubeIDE/workspace_1.4.0/static_strings/src/static_strings.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/carro/STM32CubeIDE/workspace_1.4.0/static_strings/test/static_strings_library_tests/../../inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/static_strings.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

