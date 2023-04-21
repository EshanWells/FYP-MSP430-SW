/**
 * @file RTC.c
 * @author Eshan Wells (eshanwells@gmail.com)
 * @brief driver for MCP7940
 * @version 0.1
 * @date 2023-04-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "RTC.h"

void RTC_BCDTODEC(RTC_DT_REGS_S *src, RTC_DT_REGS_S *dst)
{
    dst->sec   = (src->sec & 0x0f) + (10* ((src->sec>>4) & 0x07));
    dst->min   = (src->min & 0x0f) + (10* ((src->min>>4) & 0x07));
    dst->hour  = (src->hour & 0x0f) + (10* ((src->hour>>4) & 0x07));
    dst->wkday = src->wkday & 0x07;
    dst->day   = (src->day & 0x0f) + (10* ((src->day>>4) & 0x0f));
    dst->mth   = (src->mth & 0x0f) + (10* ((src->mth>>4) & 0x01));
    dst->year  = (src->year & 0x0f) + (10* ((src->year>>4) & 0x0f));
}

void RTC_DECTOBCD(RTC_DT_REGS_S* src, RTC_DT_REGS_S *dst)
{
    dst->sec = ((src->sec / 10) <<4) + (src->sec % 10);
    dst->min = ((src->min / 10) <<4) + (src->min % 10);
    dst->hour = ((src->hour / 10) <<4) + (src->hour % 10);
    dst->sec = (uint8_t)(src->sec % 10);
    dst->day = ((src->day / 10) <<4) + (src->day % 10);
    dst->mth = ((src->mth / 10) <<4) + (src->mth % 10);
    dst->year = ((src->year / 10) <<4) + (src->year % 10);
}
