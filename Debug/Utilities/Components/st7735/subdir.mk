################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/Components/st7735/st7735.c 

OBJS += \
./Utilities/Components/st7735/st7735.o 

C_DEPS += \
./Utilities/Components/st7735/st7735.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/Components/st7735/%.o: ../Utilities/Components/st7735/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -DSTM32F746G_DISCO -DSTM32F746NGHx -DSTM32F7 -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -I"/Users/ryuichi/Documents/workspace/CAN_Test/inc" -I"/Users/ryuichi/Documents/workspace/CAN_Test/CMSIS/core" -I"/Users/ryuichi/Documents/workspace/CAN_Test/CMSIS/device" -I"/Users/ryuichi/Documents/workspace/CAN_Test/HAL_Driver/Inc/Legacy" -I"/Users/ryuichi/Documents/workspace/CAN_Test/HAL_Driver/Inc" -I"/Users/ryuichi/Documents/workspace/CAN_Test/Utilities/Components/adv7533" -I"/Users/ryuichi/Documents/workspace/CAN_Test/Utilities/Components/ampire480272" -I"/Users/ryuichi/Documents/workspace/CAN_Test/Utilities/Components/ampire640480" -I"/Users/ryuichi/Documents/workspace/CAN_Test/Utilities/Components/Common" -I"/Users/ryuichi/Documents/workspace/CAN_Test/Utilities/Components/exc7200" -I"/Users/ryuichi/Documents/workspace/CAN_Test/Utilities/Components/ft5336" -I"/Users/ryuichi/Documents/workspace/CAN_Test/Utilities/Components/ft6x06" -I"/Users/ryuichi/Documents/workspace/CAN_Test/Utilities/Components/mfxstm32l152" -I"/Users/ryuichi/Documents/workspace/CAN_Test/Utilities/Components/mx25l512" -I"/Users/ryuichi/Documents/workspace/CAN_Test/Utilities/Components/n25q128a" -I"/Users/ryuichi/Documents/workspace/CAN_Test/Utilities/Components/n25q512a" -I"/Users/ryuichi/Documents/workspace/CAN_Test/Utilities/Components/otm8009a" -I"/Users/ryuichi/Documents/workspace/CAN_Test/Utilities/Components/ov9655" -I"/Users/ryuichi/Documents/workspace/CAN_Test/Utilities/Components/rk043fn48h" -I"/Users/ryuichi/Documents/workspace/CAN_Test/Utilities/Components/s5k5cag" -I"/Users/ryuichi/Documents/workspace/CAN_Test/Utilities/Components/st7735" -I"/Users/ryuichi/Documents/workspace/CAN_Test/Utilities/Components/st7789h2" -I"/Users/ryuichi/Documents/workspace/CAN_Test/Utilities/Components/stmpe811" -I"/Users/ryuichi/Documents/workspace/CAN_Test/Utilities/Components/ts3510" -I"/Users/ryuichi/Documents/workspace/CAN_Test/Utilities/Components/wm8994" -I"/Users/ryuichi/Documents/workspace/CAN_Test/Utilities/Fonts" -I"/Users/ryuichi/Documents/workspace/CAN_Test/Utilities/Log" -I"/Users/ryuichi/Documents/workspace/CAN_Test/Utilities/STM32746G-Discovery" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


