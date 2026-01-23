# GDB initialization script for MSP430F155 debugging with MSP-FET430UIF
# NOTE: VS Code launch.json now handles target and file loading
# This script is kept for manual debugging with: gdb -x .gdbinit

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
