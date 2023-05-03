/**
 * @file core.c
 * @author Eshan WElls (eshanwells@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "core.h"

void setLogState(LOG_FSM set)
{
    logState = set;
}

LOG_FSM getLogState(void)
{
    return logState;
}

void setNextLogState(LOG_FSM set)
{
    nextLogState = set;
}

LOG_FSM getNextLogState(void)
{
    return nextLogState;
}

void setCoreMode(CORE_MODE set)
{
    coreMode = set;
}

CORE_MODE getCoreMode(void)
{
    return coreMode;
}

unsigned long long ticks(void)
{
    return tickCount;
}

void incrementTicks(void)
{
    tickCount++;
}
