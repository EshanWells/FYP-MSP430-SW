/**
 * @file SHT40.c
 * @author Eshan Wells (eshanwells@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "SHT40.h"

void SHT_sendCommand(SHT_COMMAND_E command)
{
    uint8_t txData[1] = {command};
    I2C_write(SHT40_ADDR, txData, 1); //This is where I learned that I can only send arrays here...
}

uint16_t SHT_getSerialNumber(void)
{
    uint8_t rxData[2];
    SHT_sendCommand(SER_NUM);
    __delay_cycles(250); //apparently we need this delay... oh god...
    I2C_read(SHT40_ADDR, rxData, 2);
    uint16_t serNum = (rxData[0] << 8) | rxData[1];
    return serNum;
}

#define MULT 10

int16_t SHT_getMedReading(void)
{
    uint8_t rxData[6];
    SHT_sendCommand(TRH_MID);
    __delay_cycles(5000);
    I2C_read(SHT40_ADDR, rxData, 6);
    
    uint16_t tempMeas = (rxData[0] << 8) | rxData[1];
    int16_t result = (int16_t)tempMeas * (175*MULT);
    result /= 65535;
    result -= (45*MULT);
    return result;
}


