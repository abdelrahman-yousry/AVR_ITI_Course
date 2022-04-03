################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/subdir.mk
-include HAL/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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
LSS += \
Task_1_Volume.lss \

FLASH_IMAGE += \
Task_1_Volume.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: Task_1_Volume.elf secondary-outputs

# Tool invocations
Task_1_Volume.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Task_1_Volume.map -mmcu=atmega32 -o "Task_1_Volume.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Task_1_Volume.lss: Task_1_Volume.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Task_1_Volume.elf  >"Task_1_Volume.lss"
	@echo 'Finished building: $@'
	@echo ' '

Task_1_Volume.hex: Task_1_Volume.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Task_1_Volume.elf  "Task_1_Volume.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Task_1_Volume.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Task_1_Volume.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Task_1_Volume.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
