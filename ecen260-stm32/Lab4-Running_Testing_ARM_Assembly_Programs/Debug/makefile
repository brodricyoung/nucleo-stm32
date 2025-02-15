################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Lab4-Running_Testing_ARM_Assembly_Programs
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Lab4-Running_Testing_ARM_Assembly_Programs.elf \

MAP_FILES += \
Lab4-Running_Testing_ARM_Assembly_Programs.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Lab4-Running_Testing_ARM_Assembly_Programs.list \


# All Target
all: main-build

# Main-build Target
main-build: Lab4-Running_Testing_ARM_Assembly_Programs.elf secondary-outputs

# Tool invocations
Lab4-Running_Testing_ARM_Assembly_Programs.elf Lab4-Running_Testing_ARM_Assembly_Programs.map: $(OBJS) $(USER_OBJS) C:\Users\young\OneDrive\Documents\-\ Hardware\ Labs\nucleo-stm32\ecen260-stm32\Lab4-Running_Testing_ARM_Assembly_Programs\STM32L476RGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Lab4-Running_Testing_ARM_Assembly_Programs.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\young\OneDrive\Documents\- Hardware Labs\nucleo-stm32\ecen260-stm32\Lab4-Running_Testing_ARM_Assembly_Programs\STM32L476RGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Lab4-Running_Testing_ARM_Assembly_Programs.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Lab4-Running_Testing_ARM_Assembly_Programs.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Lab4-Running_Testing_ARM_Assembly_Programs.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Lab4-Running_Testing_ARM_Assembly_Programs.elf Lab4-Running_Testing_ARM_Assembly_Programs.list Lab4-Running_Testing_ARM_Assembly_Programs.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
