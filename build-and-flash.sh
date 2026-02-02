#!/bin/bash
# Build and flash release firmware to MSP430F155
# This script builds the release firmware and flashes it to the device

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}MSP430 Release Build and Flash${NC}"
echo "================================"
echo ""

# Check if mspdebug is installed
if ! command -v mspdebug &> /dev/null; then
    echo -e "${RED}Error: mspdebug is not installed${NC}"
    echo "Install with: sudo apt install mspdebug"
    exit 1
fi

# Check if make is installed
if ! command -v make &> /dev/null; then
    echo -e "${RED}Error: make is not installed${NC}"
    exit 1
fi

# Build the release firmware
echo -e "${YELLOW}Building release firmware...${NC}"
make clean
make all
echo -e "${GREEN}Build complete${NC}"
echo ""

# Find the debugger port
echo -e "${YELLOW}Looking for MSP-FET430UIF debugger...${NC}"

DEBUGGER_PORT=""
for port in /dev/ttyACM0 /dev/ttyUSB0 /dev/ttyACM1 /dev/ttyUSB1; do
    if [ -e "$port" ]; then
        echo -e "${GREEN}Found device at: $port${NC}"
        DEBUGGER_PORT="$port"
        break
    fi
done

if [ -z "$DEBUGGER_PORT" ]; then
    echo -e "${YELLOW}Auto-detection failed. Common ports:${NC}"
    ls -la /dev/ttyACM* /dev/ttyUSB* 2>/dev/null || echo "  No USB devices found"
    echo ""
    echo -e "${YELLOW}Usage: Specify port manually${NC}"
    echo "Example: PORT=/dev/ttyACM0 $0"
    exit 1
fi

echo ""
echo -e "${YELLOW}Flashing firmware to device...${NC}"
echo "Port: $DEBUGGER_PORT"
echo "Firmware: build/firmware.elf"
echo ""

# Flash the firmware using mspdebug
mspdebug -d "$DEBUGGER_PORT" tilib "prog build/firmware.elf"

echo ""
echo -e "${GREEN}Flash complete!${NC}"
echo ""
