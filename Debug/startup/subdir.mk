################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../startup/startup_MKW41Z4.S 

OBJS += \
./startup/startup_MKW41Z4.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -D__REDLIB__ -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/source" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/drivers" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/ieee_802.15.4/smac/interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/ieee_802.15.4/smac/source" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/ieee_802.15.4/smac/common" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/XCVR/MKW41Z4" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/utilities" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/Keyboard/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/ieee_802.15.4/phy/source/MKW41Z" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/Lists" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/OSAbstraction/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/MemManager/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/SerialManager/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/SerialManager/Source/SPI_Adapter" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/ieee_802.15.4/phy/interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/FunctionLib" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/GPIO" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/SerialManager/Source/I2C_Adapter" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/SerialManager/Source/UART_Adapter" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/Panic/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/Messaging/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/CMSIS" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/MWSCoexistence/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/TimersManager/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/TimersManager/Source" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/DCDC/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/board" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/ModuleInfo" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/SecLib" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/LED/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/Flash/Internal" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/RNG/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/common" -g3 -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -specs=redlib.specs -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


