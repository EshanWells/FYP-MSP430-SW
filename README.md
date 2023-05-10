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
 - [X] SLL Init
 - [X] Power Saving
 - [X] Implement ACLK, fix clocks and timers
 - [X] Update I2C functions to use pointers.
 - [X] Menu system
 - [X] EE Readback
 - [X] EE Erase
 - [X] Set up Timer0 as tick counter (in place of RTC)
 - [X] 1 minute logging intervals for demonstration and testing
 - [X] 5 minute logging interval
 - [X] 15 minute logging interval
 - [X] Validation mode

**Notes**
11/04/2023 So uint32_t ends up being the same size as uint16_t, and likewise with signed. This is a fundamental issue with stdint's implementation here, so I must use long to handle 32 bits. I discovered this while debugging the SHT40.

12/04/2023 I've become a master of pointers. Switched the I2C functions to use pointers instead of incrementing through arrays, this should give me support for packed structs. In one move I think more clicked about pointers than any other. Felt good.

03/05/2023 Haven't had major notes until this, but regarding the change of plan RE: RTC. I believe the crystal is dead, and I just can't get these 32KHz crystals playing nicely with anything. I've had to change to the VLO on the MCU side, which is far from optimal. As I can't reasonably get the RTC working, I'll have to set up Timer0 as a tick counter and set an alarm in software to get the ball rolling. For the purposes of this gathering data, it'll work.

08/05/2023 As of right now, I think this software is pretty much complete for the purposes of the dissertation.