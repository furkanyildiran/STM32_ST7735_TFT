################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ST7735/Src/st7735.c 

OBJS += \
./ST7735/Src/st7735.o 

C_DEPS += \
./ST7735/Src/st7735.d 


# Each subdirectory must supply rules for building sources it contributes
ST7735/Src/%.o ST7735/Src/%.su ST7735/Src/%.cyclo: ../ST7735/Src/%.c ST7735/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/MONSTER/STM32CubeIDE/workspace_1.11.0/ST7735_STM32F103/ST7735/Inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-ST7735-2f-Src

clean-ST7735-2f-Src:
	-$(RM) ./ST7735/Src/st7735.cyclo ./ST7735/Src/st7735.d ./ST7735/Src/st7735.o ./ST7735/Src/st7735.su

.PHONY: clean-ST7735-2f-Src

