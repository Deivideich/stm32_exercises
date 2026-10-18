PROJECT = firmware
OPENCM3_DIR = ../libopencm3

CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS  += -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS  += -O3 -g3 -Wall -I$(OPENCM3_DIR)/include -DSTM32G4

# CLAVE: Añadimos -nostartfiles para evitar el conflicto con crt0.o
LDFLAGS += -nostartfiles -L$(OPENCM3_DIR)/lib -lopencm3_stm32g4 -Tstm32g431kb.ld --specs=nosys.specs

all: build/$(PROJECT).bin

build/$(PROJECT).elf: src/main.c
	mkdir -p build
	$(CC) src/main.c $(CFLAGS) $(LDFLAGS) -o build/$(PROJECT).elf

build/$(PROJECT).bin: build/$(PROJECT).elf
	$(OBJCOPY) -O binary build/$(PROJECT).elf build/$(PROJECT).bin

clean:
	rm -rf build
