# Name of the final binary file
PROJECT = blinky

# Relative path to the G431KB shared files
SHARED_DIR = ../shared/g431kb

# Tools from the Ubuntu ARM toolchain
CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

# Project source files (local main + shared startup)
SRCS = main.c $(SHARED_DIR)/startup.c

# Compilation options
CFLAGS  = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS += -O0 -g3 -Wall -ffunction-sections -fdata-sections -I$(SHARED_DIR)

# Linker options pointing to the shared linker script
LDFLAGS = -T $(SHARED_DIR)/linker.ld -nostartfiles -Wl,--gc-sections -Wl,-Map=build/$(PROJECT).map

# Default rule: Compile the project
all: build/$(PROJECT).elf

build/$(PROJECT).elf: $(SRCS)
	@mkdir -p build
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRCS) -o build/$(PROJECT).elf
	$(OBJCOPY) -O binary build/$(PROJECT).elf build/$(PROJECT).bin
	@echo "\n--- Firmware Size ---"
	$(SIZE) build/$(PROJECT).elf

# Rule to flash using the centralized openocd.cfg configuration file
flash: build/$(PROJECT).elf
	openocd -f $(SHARED_DIR)/openocd.cfg -c "program build/$(PROJECT).elf verify reset exit"

# Clean locally generated files
clean:
	rm -rf build
