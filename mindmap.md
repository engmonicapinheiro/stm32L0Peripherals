---
title: STM32L0 peripherals
markmap:
    colorFreezeLevel: 2
---

## GPIOs
## UART
## ADC
## Handling IO events
Polling and interrupts are mechanisms for handling input/output (I/O) events. 
Polling requires the CPU to continuously check device status, which is simple but wastes cycles. 
Interrupts allow devices to signal the CPU when ready, enabling the CPU to handle tasks efficiently 
only as needed. Interrupts are best for real-time/unpredictable events; polling suits simple, 
predictable tasks


### Polling
### Interrupts
