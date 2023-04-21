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

void setLOGState(LOG_FSM set)
{
    logState = set;
}

LOG_FSM getLOGState(void)
{
    return logState;
}

void setNextLOGState(LOG_FSM set)
{
    nextLogState = set;
}

LOG_FSM getNextLOGState(void)
{
    return nextLogState;
}
