################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
CMSIS_5/Device/ARM/ARMSC000/Source/IAR/%.obj: ../CMSIS_5/Device/ARM/ARMSC000/Source/IAR/%.s $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/workset/BalancingWheel" --include_path="D:/workset/BalancingWheel/CMSIS_5/CMSIS/Core/Include" --include_path="D:/workset/BalancingWheel/BSW/GPIO" --include_path="D:/workset/BalancingWheel/OS" --include_path="D:/workset/BalancingWheel/TASKS" --include_path="D:/workset/BalancingWheel/BoosterButtons" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/examples/boards/ek-tm4c123gxl-boostxl-senshub/drivers" --include_path="D:/workset/BalancingWheel/DIO" --include_path="D:/workset/BalancingWheel/PWM" --include_path="D:/workset/BalancingWheel/USART" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/inc" --include_path="C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="CMSIS_5/Device/ARM/ARMSC000/Source/IAR/$(basename $(<F)).d_raw" --obj_directory="CMSIS_5/Device/ARM/ARMSC000/Source/IAR" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


