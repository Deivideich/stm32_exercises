# Name of the final binary file
PROJECT = level_1_bitwise_memory

# Relative path to the G431KB shared files
SHARED_DIR = ../shared/g431kb

# Tools from the Ubuntu ARM toolchain
CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

# Project source files (local main + shared startup)
SRCS = main.c $(SHARED_DIR)/startup.c

# Dynamically map object files to the build folder
OBJS = build/main.o build/startup.o

# Compilation options
CFLAGS  = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS += -O0 -g3 -Wall -ffunction-sections -fdata-sections -I$(SHARED_DIR)

# Linker options pointing to the shared linker script
LDFLAGS = -T $(SHARED_DIR)/linker.ld -nostartfiles -Wl,--gc-sections -Wl,-Map=build/$(PROJECT).map

# Default rule: Compile the project
all: build/$(PROJECT).elf

# Step 1: Pattern rules to compile source files to object files independently
build/main.o: main.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c main.c -o build/main.o

build/startup.o: $(SHARED_DIR)/startup.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $(SHARED_DIR)/startup.c -o build/startup.o

# Step 2: Link target utilizing separate object files and LDFLAGS cleanly
build/$(PROJECT).elf: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o build/$(PROJECT).elf
	$(OBJCOPY) -O binary build/$(PROJECT).elf build/$(PROJECT).bin
	@echo "\n--- Firmware Size ---"
	$(SIZE) build/$(PROJECT).elf

# Rule to flash using the centralized openocd.cfg configuration file
flash: build/$(PROJECT).elf
	openocd -f $(SHARED_DIR)/openocd.cfg -c "program build/$(PROJECT).elf verify reset exit"

# Clean locally generated files
clean:
	rm -rf build

# Debug through remote call to gdb multi archo functions defined in common .gdbinit
debug: build/$(PROJECT).elf
	@echo "Verifying OpenOCD server..."
	@if ! pgrep -x "openocd" > /dev/null; then \
		echo "OpenOCD is not running. Initialiazing process..."; \
		openocd -f $(SHARED_DIR)/openocd.cfg > /dev/null 2>&1 & \
		sleep 1; \
	else \
		echo "OpenOCD is active."; \
	fi
	@echo "file build/$(PROJECT).elf" > .gdb_target
	@echo "source $(SHARED_DIR)/.gdbinit" >> .gdb_target
	@if [ -f .gdb_breakpoints ]; then \
		echo "Found local breakpoints. Injecting into target..."; \
		echo "source .gdb_breakpoints" >> .gdb_target; \
	fi
	-gdb-multiarch -x .gdb_target
	@echo "Cleaning up local targets and closing OpenOCD..."
	@rm -f .gdb_target
	-@killall openocd > /dev/null 2>&1

# Separate instruction to kill hanging processes
kill:	
	@echo "Cleaning up local targets and closing OpenOCD..."
	@rm -rf .gdb_target
	-@killall openocd > /dev/null 2>&1
