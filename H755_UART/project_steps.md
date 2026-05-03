# Simple UART excercise

- Use HAL UART to set up a receiver
- Use HAL UART to transmit chars

## Things I learn on the go

- HAL_UART_Transmit
- HAL_UART_Receive
- HAL_UART_INITIALIZATION
- Memset for reseting arrays
- HAL_UART_Transmit should use the actual number of bytes to be transmitted, not the array size of the variable where the info is stored
- UART receives char values; it is possible to compare their literal values with '<value>' or know their equivalence in ASCII when comparing them directly with their number (char to int cast is done automatically since the char definition has this equivalence embedded)