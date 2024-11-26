################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Modules/CommandModule.c \
../Core/Src/Modules/UsartModule.c 

OBJS += \
./Core/Src/Modules/CommandModule.o \
./Core/Src/Modules/UsartModule.o 

C_DEPS += \
./Core/Src/Modules/CommandModule.d \
./Core/Src/Modules/UsartModule.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Modules/%.o Core/Src/Modules/%.su Core/Src/Modules/%.cyclo: ../Core/Src/Modules/%.c Core/Src/Modules/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Modules

clean-Core-2f-Src-2f-Modules:
	-$(RM) ./Core/Src/Modules/CommandModule.cyclo ./Core/Src/Modules/CommandModule.d ./Core/Src/Modules/CommandModule.o ./Core/Src/Modules/CommandModule.su ./Core/Src/Modules/UsartModule.cyclo ./Core/Src/Modules/UsartModule.d ./Core/Src/Modules/UsartModule.o ./Core/Src/Modules/UsartModule.su

.PHONY: clean-Core-2f-Src-2f-Modules

