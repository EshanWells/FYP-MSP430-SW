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

SHT_RESULT_S SHT_getMedReading(void)
{
    uint8_t rxData[6];
    SHT_sendCommand(TRH_MID);
    __delay_cycles(5000);
    I2C_read(SHT40_ADDR, rxData, 6);
    
    uint16_t tempMeas = (rxData[0] << 8) | rxData[1];
    long tempResult = (long)tempMeas * (175 * T_MULT);
    tempResult /= 65535;
    tempResult -= (45 * T_MULT);

    uint16_t humMeas = (rxData[3] << 8) | rxData[4];
    long humResult = (long)humMeas * (125 * H_MULT);
    humResult /= 65535;
    humResult -= (6*H_MULT);
    if(humResult < 0)
    {
        humResult = 0;
    }
    if(humResult > (100*H_MULT))
    {
        humResult = (100*H_MULT);
    }

    SHT_RESULT_S result;
    result.temp = (int16_t)tempResult;
    result.rHum = (uint8_t)humResult;
    
    return result;
}


