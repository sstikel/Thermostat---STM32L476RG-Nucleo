################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Delay.c \
../Src/clock_config.c \
../Src/i2c-lcd.c \
../Src/i2c_dht20.c \
../Src/i2c_main.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/usart_main.c 

OBJS += \
./Src/Delay.o \
./Src/clock_config.o \
./Src/i2c-lcd.o \
./Src/i2c_dht20.o \
./Src/i2c_main.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/usart_main.o 

C_DEPS += \
./Src/Delay.d \
./Src/clock_config.d \
./Src/i2c-lcd.d \
./Src/i2c_dht20.d \
./Src/i2c_main.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/usart_main.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32L476xx -DSTM32L4 -DSTM32 -DNUCLEO_L476RG -DSTM32L476RGTx -c -I"C:/WorkZone/STM32/Chip Headers/CMSIS/Include" -I"C:/WorkZone/STM32/Chip Headers/CMSIS/Device/ST/STM32L4xx" -I../Inc -include"C:/WorkZone/STM32/Chip Headers/CMSIS/Device/ST/STM32L4xx/Include/stm32l4xx.h" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/Delay.cyclo ./Src/Delay.d ./Src/Delay.o ./Src/Delay.su ./Src/clock_config.cyclo ./Src/clock_config.d ./Src/clock_config.o ./Src/clock_config.su ./Src/i2c-lcd.cyclo ./Src/i2c-lcd.d ./Src/i2c-lcd.o ./Src/i2c-lcd.su ./Src/i2c_dht20.cyclo ./Src/i2c_dht20.d ./Src/i2c_dht20.o ./Src/i2c_dht20.su ./Src/i2c_main.cyclo ./Src/i2c_main.d ./Src/i2c_main.o ./Src/i2c_main.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/usart_main.cyclo ./Src/usart_main.d ./Src/usart_main.o ./Src/usart_main.su

.PHONY: clean-Src

