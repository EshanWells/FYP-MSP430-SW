#include "SHT40.h"

void SHT_sendCommand(SHT_COMMAND_E command)
{
    uint8_t txData[1] = {command};
    I2C_write(SHT40_ADDR, txData, 1);
}

uint16_t SHT_getSerialNumber(void)
{
    
}
