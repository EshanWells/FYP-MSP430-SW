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
