/**
 * @file RTC.h
 * @author Eshan Wells (eshanwells@gmail.com)
 * @brief driver for MCP7940
 * @version 0.1
 * @date 2023-04-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef RTC_H_
#define RTC_H_

#include "core.h"

#define MCP7940_ADDR 0x6F

typedef enum
{
    SUNDAY = 1,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
} DOW_E;

typedef enum 
{
    RTCSEC = 0x00,
    RTCMIN,
    RTCHOUR,
    RTCWKDAY,
    RTCDATE,
    RTCMTH,
    RTCYEAR,
    CONTROL,
    OSCTRIM,
    ALM0SEC,
    ALM0MIN,
    ALM0HOUR,
    ALM0WKDAY,
    ALM0DATE,
    ALM0MTH,
} RTC_REGS_E;

typedef struct  
{
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    DOW_E wkday;
    uint8_t day;
    uint8_t mth;
    uint8_t year;
} __attribute__((packed)) RTC_DT_REGS_S;

typedef struct 
{
    uint8_t address;
    RTC_DT_REGS_S date;
} __attribute__((packed)) RTC_REG_IF_S;

void RTC_BCDTODEC(RTC_DT_REGS_S *src, RTC_DT_REGS_S *dst);

void RTC_DECTOBCD(RTC_DT_REGS_S *src, RTC_DT_REGS_S *dst);

#endif
