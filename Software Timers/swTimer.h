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



bool await_Timer(TimerID which_Timer);

void timer_Reset(TimerID which_Timer);

void timer_Set_Delay(TimerID which_Timer, uint32_t delay_Ms);

#endif // TIMER_H