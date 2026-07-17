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
} TimerID;


/** =======================================================================
 *  Public API 
 *  =======================================================================
 */


/**
 * @brief Reset the timer.
 * 
 * @param whichTimer The id of the timer to reset.
 * 
 * @return return errors:
 *              0 - Success
 *              1 - Error: Invalid Timer ID
 * 
 * @note When starting a timer it must be reset or else it will immediately reset
 */
uint8_t timerReset(TimerID whichTimer);

/**
 * @brief Set the delay for a timer.
 * 
 * @param whichTimer The id of the timer to set the delay for.
 * @param delayMs The new delay in milliseconds.
 * 
 * @return return errors:
 *              0 - Success
 *              1 - Error: Invalid Timer ID
 */
uint8_t timerSetDelay(TimerID whichTimer, uint32_t delayMs);

/**
 * @brief Check if the timer has expired.
 * 
 * @param whichTimer The id of the timer to reset.
 * 
 * @return The timer status of the timer. 
 *              0 - Timer has expired
 *              1 - Timer has not expired
 *              2 - Error: Invalid Timer ID
 */
 uint8_t timerAwait(TimerID whichTimer);

#endif // TIMER_H