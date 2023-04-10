## **Container Logger Final Year Project Software - MSP430 Version**

**Introduction**
Development repo for MSP430 based container environment logger.

**To Do**
In a very loose order
 - [x] Blink
 - [x] Clock setup
 - [x] Interrupt blink
 - [x] UART Driver
 - [X] Fix GPIO.c and .h
 - [X] Implement I2C Drivers
 - [ ] SHT40 Driver
 - [ ] RTC Driver
 - [X] EEPROM Driver
 - [ ] SLL Alg
 - [ ] Power Saving
 - [X] Implement ACLK, fix clocks and timers

**Notes**
So uint32_t ends up being the same size as uint16_t, and likewise with signed. This is a fundamental issue with stdint, so I must use long to handle 32 bits. I discovered this while debugging the SHT40.