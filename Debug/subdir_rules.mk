################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/workset/BalancingWheel" --include_path="D:/workset/BalancingWheel/APP/PRINT" --include_path="D:/workset/BalancingWheel/Services/CIRCULAR_BUFFER" --include_path="D:/workset/BalancingWheel/APP/BL" --include_path="D:/workset/BalancingWheel/Services/common" --include_path="D:/workset/BalancingWheel/Services/MPU9150" --include_path="D:/workset/BalancingWheel/BSW/I2C" --include_path="D:/workset/BalancingWheel/Services/I2CDev" --include_path="D:/workset/BalancingWheel/APP/IMU" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/driverlib" --include_path="D:/workset/BalancingWheel/BSW/GPIO" --include_path="D:/workset/BalancingWheel/OS" --include_path="D:/workset/BalancingWheel/TASKS" --include_path="D:/workset/BalancingWheel/BoosterButtons" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/examples/boards/ek-tm4c123gxl-boostxl-senshub/drivers" --include_path="D:/workset/BalancingWheel/DIO" --include_path="D:/workset/BalancingWheel/PWM" --include_path="D:/workset/BalancingWheel/BSW/USART" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/inc" --include_path="C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


