/**
 * @file EE.c
 * @author Eshan Wells (eshanwells@gmail.com)
 * @brief Source file for 24LC512 EEPROM. May work with other 24 series. Requires I2C library.
 * @version 0.1
 * @date 2023-04-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "EE.h"

//in this instance, I'll assume that no read or write is gonna cross boundaries. Ultimately
//I handle this myself in the datalogger layer. It's not ideal but it keeps stuff speedy
//and potentially code small. Sorry future me.

void EE_read(uint16_t memAddr, uint8_t *pData, uint8_t length)
{
    uint8_t address[] = {(memAddr >> 8) & 0xFF, memAddr & 0xFF};
    I2C_write(EE_I2C_ADDR, address, 2);
    I2C_read(EE_I2C_ADDR, pData, length);
}

//TODO Test the heck outta this.
//TODO Surely I can do this with some fancy pointer magic.
//TODO Acknowledge polling???
void EE_write(uint16_t memAddr, uint8_t *pData, uint8_t length) //We are limited to 32bytes + address for writes. that's fine really.
{
    uint8_t address[] = {(memAddr >> 8) & 0xFF, memAddr & 0xFF};

    uint8_t lenToWrite = length + 2;
    uint8_t toWrite[34];
    toWrite[0] = address[0];
    toWrite[1] = address[1];
    uint8_t index;
    for(index = 0; index < length; index ++)
    {
        toWrite[(index+2)] = pData[index];
    }

    I2C_write(EE_I2C_ADDR, toWrite, lenToWrite);

}

void EE_ReadbackRaw(void)
{
    uint8_t data[16] = {0};
    uint16_t addressPointer = 0;
    uint16_t entryIndex = 0;

    for(entryIndex = 0; entryIndex < 4096; entryIndex++)
    {
        addressPointer = entryIndex<<4; //multiply by 16

        EE_read(addressPointer, data, 16);

        char entryPrint[64] = {0};
        sprintf(entryPrint, "%.2X %.2X %.2X %.2X %.2X %.2X %.2X %.2X %.2X %.2X %.2X %.2X %.2X %.2X %.2X %.2X\r\n",
        data[0],
        data[1],
        data[2],
        data[3],
        data[4],
        data[5],
        data[6],
        data[7],
        data[8],
        data[9],
        data[10],
        data[11],
        data[12],
        data[13],
        data[14],
        data[15]
        );

        uartPrintString(entryPrint, 64);
        
        if(getLogState() == MENU) //this situation indicates a cancel is requested.
        {
            break;
        }
    }
}
