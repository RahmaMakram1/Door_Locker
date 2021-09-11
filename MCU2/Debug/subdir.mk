################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Eeprom.c \
../Functions.c \
../I2c.c \
../Timer0.c \
../main.c \
../uart.c 

OBJS += \
./Eeprom.o \
./Functions.o \
./I2c.o \
./Timer0.o \
./main.o \
./uart.o 

C_DEPS += \
./Eeprom.d \
./Functions.d \
./I2c.d \
./Timer0.d \
./main.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


