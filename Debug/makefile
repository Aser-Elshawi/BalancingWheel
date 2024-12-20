################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./tm4c123gh6pm_startup_ccs.obj" \
"./APP/BL/Blink.obj" \
"./APP/IMU/IMU.obj" \
"./APP/PRINT/print.obj" \
"./BSW/GPIO/GPIO.obj" \
"./BSW/I2C/I2C_IMU.obj" \
"./BSW/USART/UART.obj" \
"./BoosterButtons/Buttons.obj" \
"./DIO/DIO.obj" \
"./OS/OS.obj" \
"./PWM/PWM.obj" \
"./Services/CIRCULAR_BUFFER/CIR_buffer.obj" \
"./Services/I2CDev/I2Cdev.obj" \
"./Services/MPU9150/MPU9150.obj" \
"./Services/common/common.obj" \
"./TASKS/TASKS.obj" \
"../tm4c123gh6pm.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \
-l"C:/ti/TivaWare_C_Series-2.2.0.295/driverlib/ccs/Debug/driverlib.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include APP/BL/subdir_vars.mk
-include APP/IMU/subdir_vars.mk
-include APP/PRINT/subdir_vars.mk
-include BSW/GPIO/subdir_vars.mk
-include BSW/I2C/subdir_vars.mk
-include BSW/USART/subdir_vars.mk
-include BoosterButtons/subdir_vars.mk
-include DIO/subdir_vars.mk
-include OS/subdir_vars.mk
-include PWM/subdir_vars.mk
-include Services/CIRCULAR_BUFFER/subdir_vars.mk
-include Services/I2CDev/subdir_vars.mk
-include Services/MPU9150/subdir_vars.mk
-include Services/common/subdir_vars.mk
-include TASKS/subdir_vars.mk
-include subdir_rules.mk
-include APP/BL/subdir_rules.mk
-include APP/IMU/subdir_rules.mk
-include APP/PRINT/subdir_rules.mk
-include BSW/GPIO/subdir_rules.mk
-include BSW/I2C/subdir_rules.mk
-include BSW/USART/subdir_rules.mk
-include BoosterButtons/subdir_rules.mk
-include DIO/subdir_rules.mk
-include OS/subdir_rules.mk
-include PWM/subdir_rules.mk
-include Services/CIRCULAR_BUFFER/subdir_rules.mk
-include Services/I2CDev/subdir_rules.mk
-include Services/MPU9150/subdir_rules.mk
-include Services/common/subdir_rules.mk
-include TASKS/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
BalancingWheel.out 

EXE_OUTPUTS__QUOTED += \
"BalancingWheel.out" 


# All Target
all: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "BalancingWheel.out"

# Tool invocations
BalancingWheel.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"BalancingWheel.map" --heap_size=0x1000 --stack_size=0x4000 -i"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/lib" -i"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --reread_libs --diag_wrap=off --display_error_number --verbose_diagnostics --warn_sections --xml_link_info="BalancingWheel_linkInfo.xml" --rom_model -o "BalancingWheel.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "tm4c123gh6pm_startup_ccs.obj" "APP\BL\Blink.obj" "APP\IMU\IMU.obj" "APP\PRINT\print.obj" "BSW\GPIO\GPIO.obj" "BSW\I2C\I2C_IMU.obj" "BSW\USART\UART.obj" "BoosterButtons\Buttons.obj" "DIO\DIO.obj" "OS\OS.obj" "PWM\PWM.obj" "Services\CIRCULAR_BUFFER\CIR_buffer.obj" "Services\I2CDev\I2Cdev.obj" "Services\MPU9150\MPU9150.obj" "Services\common\common.obj" "TASKS\TASKS.obj" 
	-$(RM) "main.d" "tm4c123gh6pm_startup_ccs.d" "BSW\GPIO\GPIO.d" "BSW\I2C\I2C_IMU.d" "BoosterButtons\Buttons.d" "DIO\DIO.d" "OS\OS.d" "PWM\PWM.d" "Services\common\common.d" "TASKS\TASKS.d" 
	-$(RM) "APP\BL\Blink.d" "APP\IMU\IMU.d" "APP\PRINT\print.d" "BSW\USART\UART.d" "Services\CIRCULAR_BUFFER\CIR_buffer.d" "Services\I2CDev\I2Cdev.d" "Services\MPU9150\MPU9150.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

