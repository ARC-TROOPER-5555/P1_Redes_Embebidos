################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mdio/fsl_enet_mdio.c 

C_DEPS += \
./mdio/fsl_enet_mdio.d 

OBJS += \
./mdio/fsl_enet_mdio.o 


# Each subdirectory must supply rules for building sources it contributes
mdio/%.o: ../mdio/%.c mdio/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DPRINTF_ADVANCED_ENABLE=1 -DFRDM_K66F -DFREEDOM -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\REDES\Practicas\P1_Hernandez_Alfaro\P1_H_D_enet_txrx_transfer\source" -I"D:\REDES\Practicas\P1_Hernandez_Alfaro\P1_H_D_enet_txrx_transfer\mdio" -I"D:\REDES\Practicas\P1_Hernandez_Alfaro\P1_H_D_enet_txrx_transfer\phy" -I"D:\REDES\Practicas\P1_Hernandez_Alfaro\P1_H_D_enet_txrx_transfer\utilities" -I"D:\REDES\Practicas\P1_Hernandez_Alfaro\P1_H_D_enet_txrx_transfer\drivers" -I"D:\REDES\Practicas\P1_Hernandez_Alfaro\P1_H_D_enet_txrx_transfer\device" -I"D:\REDES\Practicas\P1_Hernandez_Alfaro\P1_H_D_enet_txrx_transfer\component\uart" -I"D:\REDES\Practicas\P1_Hernandez_Alfaro\P1_H_D_enet_txrx_transfer\component\lists" -I"D:\REDES\Practicas\P1_Hernandez_Alfaro\P1_H_D_enet_txrx_transfer\CMSIS" -I"D:\REDES\Practicas\P1_Hernandez_Alfaro\P1_H_D_enet_txrx_transfer\board" -I"D:\REDES\Practicas\P1_Hernandez_Alfaro\P1_H_D_enet_txrx_transfer\frdmk66f\driver_examples\enet\txrx_transfer" -O0 -fno-common -g3 -gdwarf-4 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-mdio

clean-mdio:
	-$(RM) ./mdio/fsl_enet_mdio.d ./mdio/fsl_enet_mdio.o

.PHONY: clean-mdio

