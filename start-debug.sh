#!/bin/bash
# Start MSPDebug GDB server for MSP-FET430UIF debugging
# This script should be run in a terminal before starting debugging in VS Code

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}MSP430 Debug Setup${NC}"
echo "=================="
echo ""

# Check if mspdebug is installed
if ! command -v mspdebug &> /dev/null; then
    echo -e "${RED}Error: mspdebug is not installed${NC}"
    echo "Install with: sudo apt install mspdebug"
    exit 1
fi

# Find the debugger port
echo -e "${YELLOW}Looking for MSP-FET430UIF debugger...${NC}"

# Try common ports
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
    echo -e "${YELLOW}Usage: $0 <PORT>${NC}"
    echo "Example: $0 /dev/ttyACM0"
    exit 1
fi

echo ""
echo -e "${GREEN}Starting MSPDebug GDB server...${NC}"
echo "Port: $DEBUGGER_PORT"
echo "GDB will connect to: localhost:2000"
echo ""
echo -e "${YELLOW}Note: Keep this terminal running while debugging in VS Code${NC}"
echo ""

# Start mspdebug with GDB server
# mspdebug prints "Bound to port 2000" when ready for connections
echo -e "${GREEN}Starting MSPDebug GDB server...${NC}"
mspdebug -d "$DEBUGGER_PORT" tilib "gdb"
