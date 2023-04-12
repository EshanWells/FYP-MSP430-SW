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
 - [X] SHT40 Driver
 - [ ] RTC Driver
 - [X] EEPROM Driver
 - [ ] SLL Alg
 - [ ] Power Saving
 - [X] Implement ACLK, fix clocks and timers
 - [X] Update I2C functions to use pointers.

**Notes**
11/04/23 So uint32_t ends up being the same size as uint16_t, and likewise with signed. This is a fundamental issue with stdint, so I must use long to handle 32 bits. I discovered this while debugging the SHT40.

12/04/23 I've become a master of pointers. Switched the I2C functions to use pointers instead of incrementing through arrays, this should give me support for packed structs. In one move I think more clicked about pointers than any other. Felt good.