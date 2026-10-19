# 1. Safety settings to allow local scripts
set auto-load safe-path /
set confirm off

# 2. Automatic connection to GDB server (GDB Remote Protocol)
# OpenOCD opens default port :3333 on localhost
target remote localhost:3333

# 3. Monitor and synch state of the chip
# Command to reset the chip program
monitor reset halt

# 4. Custom macros definitions
# pbin command is defined to print varibales in binary format
define pbin
  print/t $arg0
end
document pbin
  Prints an entire 32-bit variable in binary format
  Use: pbin variable
end

# Macro used for reading a 32-bit register in binary directly using its address
define xbin
  x/1wt $arg0
end

# 5. Automate debugging flow in initialization
# Auotomatically attachs a breakpoint in main function
break main

# Program runs until reaching main
continue
