################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
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

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
M24M01EEPROMdrv.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
M24M01EEPROMdrv.list \

OBJCOPY_BIN += \
M24M01EEPROMdrv.bin \


# All Target
all: M24M01EEPROMdrv.elf secondary-outputs

# Tool invocations
M24M01EEPROMdrv.elf: $(OBJS) $(USER_OBJS) /home/piotr/Desktop/Repos/M24M01EEPROMdrv/STM32F413CGUX_FLASH.ld
	arm-none-eabi-gcc -o "M24M01EEPROMdrv.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/home/piotr/Desktop/Repos/M24M01EEPROMdrv/STM32F413CGUX_FLASH.ld" --specs=nosys.specs -Wl,-Map="M24M01EEPROMdrv.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

M24M01EEPROMdrv.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "M24M01EEPROMdrv.list"
	@echo 'Finished building: $@'
	@echo ' '

M24M01EEPROMdrv.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "M24M01EEPROMdrv.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
