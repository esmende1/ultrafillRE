# Makefile for MSP430F155 Microcontroller Project
# Builds ELF and HEX files for embedded deployment

# ===== Device and Toolchain Configuration =====
DEVICE = msp430f155
MCU = msp430f155

# Toolchain
CC = msp430-elf-gcc
OBJCOPY = msp430-elf-objcopy
SIZE = msp430-elf-size
RM = rm -f

# ===== Directories =====
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# ===== Source Files =====
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

# ===== Output Files =====
PROJECT_NAME = firmware
ELF_FILE = $(BUILD_DIR)/$(PROJECT_NAME)$(DEBUG_SUFFIX).elf
HEX_FILE = $(BUILD_DIR)/$(PROJECT_NAME)$(DEBUG_SUFFIX).hex
LST_FILE = $(BUILD_DIR)/$(PROJECT_NAME)$(DEBUG_SUFFIX).lst

# ===== Compiler Flags =====
# Debug flags for GDB remote debugging
DEBUG_FLAGS = -g3 -gdwarf-3 -O0

# Standard optimization flags (used when DEBUG is not set)
OPTIMIZE_FLAGS = -g -Os

# Use DEBUG_FLAGS if DEBUG=1 is passed (make DEBUG=1)
ifeq ($(DEBUG),1)
    CFLAGS_OPT = $(DEBUG_FLAGS)
    DEBUG_SUFFIX = -debug
else
    CFLAGS_OPT = $(OPTIMIZE_FLAGS)
    DEBUG_SUFFIX =
endif

CFLAGS = -I$(INC_DIR) \
         -I/opt/ti/msp430-gcc-9.3.1.11_linux64/include \
         -mmcu=$(MCU) \
         -Wall \
         -Wextra \
         -Werror \
         $(CFLAGS_OPT) \
         -std=c99 \
         -ffunction-sections \
         -fdata-sections \
         -fomit-frame-pointer \
		 -fshort-enums

# ===== Linker Flags =====
LDFLAGS = -mmcu=$(MCU) \
          -Wl,--gc-sections \
          -Wl,--print-memory-usage

# ===== Build Rules =====
.PHONY: all clean build hex size help debug debug-build

all: build hex size

build: $(ELF_FILE)

# Debug build target - compile with full debug symbols
debug: clean
	@make build DEBUG=1
	@echo "Debug build complete with full symbols: $(ELF_FILE)"

debug-build: DEBUG=1
debug-build: build

hex: $(HEX_FILE)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(ELF_FILE): $(OBJECTS)
	@echo "Linking: $@"
	@$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	@echo "Build complete: $@"

$(HEX_FILE): $(ELF_FILE)
	@echo "Creating HEX file: $@"
	@$(OBJCOPY) -O ihex $< $@
	@echo "HEX file generated: $@"

$(LST_FILE): $(ELF_FILE)
	@echo "Creating listing file: $@"
	@$(OBJCOPY) -O verilog $< $@

size: $(ELF_FILE)
	@echo "\n--- Memory Usage ---"
	@$(SIZE) $(ELF_FILE)

clean:
	@echo "Cleaning build artifacts..."
	@$(RM) -r $(BUILD_DIR)
	@echo "Clean complete"

help:
	@echo "MSP430F155 Makefile targets:"
	@echo "  make all         - Build project and generate HEX file (default)"
	@echo "  make build       - Build ELF file only"
	@echo "  make hex         - Generate HEX file from ELF"
	@echo "  make size        - Show memory usage"
	@echo "  make debug       - Build with full debug symbols (clean build)"
	@echo "  make debug-build - Build with debug symbols only"
	@echo "  make clean       - Remove build artifacts"
	@echo "  make help        - Display this help message"
	@echo ""
	@echo "Debug options:"
	@echo "  make DEBUG=1          - Build with debug symbols (max -O0)"
	@echo "  make DEBUG=1 all      - Debug build with HEX file"
	@echo ""
	@echo "Remote GDB debugging:"
	@echo "  1. Connect MSP430 via USB (Launchpad or compatible debugger)"
	@echo "  2. Start GDB server: mspdebug -j usbfet tilib gdb"
	@echo "  3. Run debug from VS Code (F5) or use: make debug && gdb -x .gdbinit"
 