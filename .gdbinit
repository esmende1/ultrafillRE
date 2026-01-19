# GDB initialization script for remote MSP430F155 debugging
# Usage: gdb -x .gdbinit

# Set target to remote debugger
# MSPDebug typically runs GDB server on localhost:2000
target remote localhost:2000

# Load the firmware ELF file
file build/firmware-debug.elf

# Set architecture (MSP430)
set architecture msp430

# Enable history
set history expansion on
set history save on
set history size 256
set history filename ~/.gdb_msp430_history

# Break on main function
break main

# Display instructions before each command
display/i $pc

# Useful settings
set print pretty on
set print array on
set print array-indexes on

# Connect and load the program into target memory
load

# Continue to main
continue
