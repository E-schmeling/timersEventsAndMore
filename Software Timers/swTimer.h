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

/** =======================================================================
 *  Enumerations and Types
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
} TimerID_t;


/** =======================================================================
 *  Public API 
 *  =======================================================================
 */

/**
 * @brief Set the delay for a timer.
 * 
 * @param which_Timer The id of the timer to set the delay for.
 * @param delayMs The new delay in milliseconds.
 * 
 * @return return errors:
 *              0 - Success
 *              1 - Error: Invalid Timer ID
 */
uint8_t timer_Set_Delay(TimerID_t which_Timer, uint32_t delayMs);

/**
 * @brief Get the delay for a timer.
 * 
 * @param which_Timer The id of the timer to get the delay for.
 * @param delayMs* Pointer to store the the current delay in milliseconds.
 * 
 * @return return errors:
 *              0 - Success
 *              1 - Error: Invalid Timer ID
 */
uint8_t timer_Get_Delay(TimerID_t which_Timer, uint32_t* delayMs);


/**
 * @brief Reset the timer.
 * 
 * @param which_Timer The id of the timer to reset.
 * 
 * @return return errors:
 *              0 - Success
 *              1 - Error: Invalid Timer ID
 * 
 * @note When starting a timer it must be reset or else it will immediately reset
 */
uint8_t timer_Reset(TimerID_t which_Timer);


/**
 * @brief Check if the timer has expired.
 * 
 * @param which_Timer The id of the timer to reset.
 * 
 * @return The timer status of the timer. 
 *              0 - Timer has expired
 *              1 - Timer has not expired
 *              2 - Error: Invalid Timer ID
 */
 uint8_t timer_Await(TimerID_t which_Timer);

#endif // TIMER_H