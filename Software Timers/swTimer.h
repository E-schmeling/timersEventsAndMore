/**
 * @file swTimer.h
 * @brief Timer Framework.
 * @author ERS
 *
 */
#ifndef TIMER_H
#define TIMER_H


/** =======================================================================
 *  Defines
 *  =======================================================================
 */
#include <stdint.h>
#include <stdbool.h>

/** =======================================================================
 *  
 *  =======================================================================
 */
typedef enum
{
    radioPulse = 0,
    countDownTimer,
    apogeeTimer,
    ascentTimer,
    descentTimer,
    TIMER_COUNT
} TimerID;



bool awaitTimer(TimerID whichTimer);

void timerReset(TimerID whichTimer);

void timerSetDelay(TimerID whichTimer, uint32_t delayMs);

#endif // TIMER_H