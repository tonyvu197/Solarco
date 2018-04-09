################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
bluetooth.obj: ../bluetooth.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/Program Files (x86)/TI/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --opt_for_speed=0 --include_path="C:/Users/tony4/CCS Projects/Solarco" --include_path="C:/Program Files (x86)/TI/TivaWare" --include_path="C:/Program Files (x86)/TI/TivaWare/driverlib" --include_path="C:/Program Files (x86)/TI/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="bluetooth.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

display.obj: ../display.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/Program Files (x86)/TI/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --opt_for_speed=0 --include_path="C:/Users/tony4/CCS Projects/Solarco" --include_path="C:/Program Files (x86)/TI/TivaWare" --include_path="C:/Program Files (x86)/TI/TivaWare/driverlib" --include_path="C:/Program Files (x86)/TI/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="display.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

keypad.obj: ../keypad.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/Program Files (x86)/TI/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --opt_for_speed=0 --include_path="C:/Users/tony4/CCS Projects/Solarco" --include_path="C:/Program Files (x86)/TI/TivaWare" --include_path="C:/Program Files (x86)/TI/TivaWare/driverlib" --include_path="C:/Program Files (x86)/TI/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="keypad.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/Program Files (x86)/TI/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --opt_for_speed=0 --include_path="C:/Users/tony4/CCS Projects/Solarco" --include_path="C:/Program Files (x86)/TI/TivaWare" --include_path="C:/Program Files (x86)/TI/TivaWare/driverlib" --include_path="C:/Program Files (x86)/TI/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

motor.obj: ../motor.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/Program Files (x86)/TI/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --opt_for_speed=0 --include_path="C:/Users/tony4/CCS Projects/Solarco" --include_path="C:/Program Files (x86)/TI/TivaWare" --include_path="C:/Program Files (x86)/TI/TivaWare/driverlib" --include_path="C:/Program Files (x86)/TI/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="motor.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

sensor.obj: ../sensor.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/Program Files (x86)/TI/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --opt_for_speed=0 --include_path="C:/Users/tony4/CCS Projects/Solarco" --include_path="C:/Program Files (x86)/TI/TivaWare" --include_path="C:/Program Files (x86)/TI/TivaWare/driverlib" --include_path="C:/Program Files (x86)/TI/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="sensor.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

tm4c123gh6pm_startup_ccs.obj: ../tm4c123gh6pm_startup_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/Program Files (x86)/TI/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --opt_for_speed=0 --include_path="C:/Users/tony4/CCS Projects/Solarco" --include_path="C:/Program Files (x86)/TI/TivaWare" --include_path="C:/Program Files (x86)/TI/TivaWare/driverlib" --include_path="C:/Program Files (x86)/TI/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="tm4c123gh6pm_startup_ccs.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uartstdio.obj: C:/Program\ Files\ (x86)/TI/TivaWare/utils/uartstdio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/Program Files (x86)/TI/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --opt_for_speed=0 --include_path="C:/Users/tony4/CCS Projects/Solarco" --include_path="C:/Program Files (x86)/TI/TivaWare" --include_path="C:/Program Files (x86)/TI/TivaWare/driverlib" --include_path="C:/Program Files (x86)/TI/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="uartstdio.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


