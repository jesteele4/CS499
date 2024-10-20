################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me -O3 --include_path="C:/Users/Jeff/Desktop/Computer Science/CS350/2-2 Milestone" --include_path="C:/Users/Jeff/Desktop/Computer Science/CS350/2-2 Milestone/MCU+Image" --include_path="C:/ti/simplelink_cc32xx_sdk_7_10_00_13/source" --include_path="C:/ti/simplelink_cc32xx_sdk_7_10_00_13/kernel/nortos" --include_path="C:/ti/simplelink_cc32xx_sdk_7_10_00_13/kernel/nortos/posix" --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=DeviceFamily_CC3220 --define=NORTOS_SUPPORT -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/Jeff/Desktop/Computer Science/CS350/2-2 Milestone/MCU+Image/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-642115183: ../pwmled2.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1_12_0/sysconfig_cli.bat" --script "C:/Users/Jeff/Desktop/Computer Science/CS350/2-2 Milestone/pwmled2.syscfg" -o "syscfg" -s "C:/ti/simplelink_cc32xx_sdk_7_10_00_13/.metadata/product.json" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_config.c: build-642115183 ../pwmled2.syscfg
syscfg/ti_drivers_config.h: build-642115183
syscfg/ti_utils_build_linker.cmd.genlibs: build-642115183
syscfg/syscfg_c.rov.xs: build-642115183
syscfg: build-642115183

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me -O3 --include_path="C:/Users/Jeff/Desktop/Computer Science/CS350/2-2 Milestone" --include_path="C:/Users/Jeff/Desktop/Computer Science/CS350/2-2 Milestone/MCU+Image" --include_path="C:/ti/simplelink_cc32xx_sdk_7_10_00_13/source" --include_path="C:/ti/simplelink_cc32xx_sdk_7_10_00_13/kernel/nortos" --include_path="C:/ti/simplelink_cc32xx_sdk_7_10_00_13/kernel/nortos/posix" --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=DeviceFamily_CC3220 --define=NORTOS_SUPPORT -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/Jeff/Desktop/Computer Science/CS350/2-2 Milestone/MCU+Image/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


