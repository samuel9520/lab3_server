################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_ant_config.c \
../framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_ble_config.c \
../framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_common_config.c \
../framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_gfsk_bt_0p3_h_0p5_config.c \
../framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_gfsk_bt_0p5_h_0p32_config.c \
../framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_gfsk_bt_0p5_h_0p5_config.c \
../framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_gfsk_bt_0p5_h_0p7_config.c \
../framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_gfsk_bt_0p5_h_1p0_config.c \
../framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_gfsk_bt_0p7_h_0p5_config.c \
../framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_mode_datarate_config.c \
../framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_msk_config.c \
../framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_zgbe_config.c 

OBJS += \
./framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_ant_config.o \
./framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_ble_config.o \
./framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_common_config.o \
./framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_gfsk_bt_0p3_h_0p5_config.o \
./framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_gfsk_bt_0p5_h_0p32_config.o \
./framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_gfsk_bt_0p5_h_0p5_config.o \
./framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_gfsk_bt_0p5_h_0p7_config.o \
./framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_gfsk_bt_0p5_h_1p0_config.o \
./framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_gfsk_bt_0p7_h_0p5_config.o \
./framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_mode_datarate_config.o \
./framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_msk_config.o \
./framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_zgbe_config.o 

C_DEPS += \
./framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_ant_config.d \
./framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_ble_config.d \
./framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_common_config.d \
./framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_gfsk_bt_0p3_h_0p5_config.d \
./framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_gfsk_bt_0p5_h_0p32_config.d \
./framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_gfsk_bt_0p5_h_0p5_config.d \
./framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_gfsk_bt_0p5_h_0p7_config.d \
./framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_gfsk_bt_0p5_h_1p0_config.d \
./framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_gfsk_bt_0p7_h_0p5_config.d \
./framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_mode_datarate_config.d \
./framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_msk_config.d \
./framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/fsl_xcvr_zgbe_config.d 


# Each subdirectory must supply rules for building sources it contributes
framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/%.o: ../framework/XCVR/MKW41Z4/cfgs_kw4x_3x_2x/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCR_INTEGER_PRINTF -DDEBUG -DFRDM_KW41Z -DFREEDOM -DSDK_DEBUGCONSOLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DCPU_MKW41Z512VHT4 -DCPU_MKW41Z512VHT4_cm0plus -D__REDLIB__ -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/source" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/drivers" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/ieee_802.15.4/smac/interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/ieee_802.15.4/smac/source" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/ieee_802.15.4/smac/common" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/XCVR/MKW41Z4" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/utilities" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/Keyboard/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/ieee_802.15.4/phy/source/MKW41Z" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/Lists" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/OSAbstraction/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/MemManager/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/SerialManager/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/SerialManager/Source/SPI_Adapter" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/ieee_802.15.4/phy/interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/FunctionLib" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/GPIO" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/SerialManager/Source/I2C_Adapter" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/SerialManager/Source/UART_Adapter" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/Panic/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/Messaging/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/CMSIS" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/MWSCoexistence/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/TimersManager/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/TimersManager/Source" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/DCDC/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/board" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/ModuleInfo" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/SecLib" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/LED/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/Flash/Internal" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/RNG/Interface" -I"/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/framework/common" -O0 -fno-common -g -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -imacros "/home/samuel9520/Documents/MCUXpresso_10.0.2_411/workspace/lab3_server/source/app_preinclude.h" -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


