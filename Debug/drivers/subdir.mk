################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_adc16.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_dspi.c \
../drivers/fsl_flash.c \
../drivers/fsl_gpio.c \
../drivers/fsl_i2c.c \
../drivers/fsl_llwu.c \
../drivers/fsl_lptmr.c \
../drivers/fsl_lpuart.c \
../drivers/fsl_ltc.c \
../drivers/fsl_pmc.c \
../drivers/fsl_rtc.c \
../drivers/fsl_smc.c \
../drivers/fsl_tpm.c \
../drivers/fsl_trng.c \
../drivers/fsl_tsi_v4.c 

OBJS += \
./drivers/fsl_adc16.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_dspi.o \
./drivers/fsl_flash.o \
./drivers/fsl_gpio.o \
./drivers/fsl_i2c.o \
./drivers/fsl_llwu.o \
./drivers/fsl_lptmr.o \
./drivers/fsl_lpuart.o \
./drivers/fsl_ltc.o \
./drivers/fsl_pmc.o \
./drivers/fsl_rtc.o \
./drivers/fsl_smc.o \
./drivers/fsl_tpm.o \
./drivers/fsl_trng.o \
./drivers/fsl_tsi_v4.o 

C_DEPS += \
./drivers/fsl_adc16.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_dspi.d \
./drivers/fsl_flash.d \
./drivers/fsl_gpio.d \
./drivers/fsl_i2c.d \
./drivers/fsl_llwu.d \
./drivers/fsl_lptmr.d \
./drivers/fsl_lpuart.d \
./drivers/fsl_ltc.d \
./drivers/fsl_pmc.d \
./drivers/fsl_rtc.d \
./drivers/fsl_smc.d \
./drivers/fsl_tpm.d \
./drivers/fsl_trng.d \
./drivers/fsl_tsi_v4.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCR_INTEGER_PRINTF -DDEBUG -DFRDM_KW41Z -DFREEDOM -DSDK_DEBUGCONSOLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DCPU_MKW41Z512VHT4 -DCPU_MKW41Z512VHT4_cm0plus -D__REDLIB__ -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/source" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/drivers" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/ieee_802.15.4/smac/interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/ieee_802.15.4/smac/source" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/ieee_802.15.4/smac/common" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/XCVR/MKW41Z4" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/utilities" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/Keyboard/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/ieee_802.15.4/phy/source/MKW41Z" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/Lists" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/OSAbstraction/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/MemManager/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/SerialManager/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/SerialManager/Source/SPI_Adapter" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/ieee_802.15.4/phy/interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/FunctionLib" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/GPIO" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/SerialManager/Source/I2C_Adapter" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/SerialManager/Source/UART_Adapter" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/Panic/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/Messaging/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/CMSIS" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/MWSCoexistence/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/TimersManager/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/TimersManager/Source" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/DCDC/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/board" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/ModuleInfo" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/SecLib" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/LED/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/Flash/Internal" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/RNG/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/common" -O0 -fno-common -g -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -imacros "/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/source/app_preinclude.h" -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


