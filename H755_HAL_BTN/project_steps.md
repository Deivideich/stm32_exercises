# Button press detection with HAL

- Use HAL to detect a pressed button from user
- Turn on a LED with this signal
- Use HAL UART to show the current state of the button 
- Check switch bouncing
  - From integrated USR button it is known that it has an integrated external resistor to process the signal
  - Implement a external button to check if the behavior is similar
  - Do debouncing with hardware/signal filtering and software methods
  - Consider bit manipulation to handle states in an efficient way

  ## Things I learned:

  - Modularization through header files to separate concerns
  - Use of polling for simple event detection
  - Non blocking polling for event and state identification
  - Use of HAL for GPIO initialization and tick retrieval
  