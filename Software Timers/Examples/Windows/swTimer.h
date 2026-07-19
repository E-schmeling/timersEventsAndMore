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
    TIMER_ONE = 0,
    TIMER_TWO,
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
 * @param[out] delayMs* Pointer to store the the current delay in milliseconds.
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
 * @param which_Timer The id of the timer to read and reset.
 * 
 * @return The timer status of the timer. 
 *              0 - Timer has expired
 *              1 - Timer has not expired
 *              2 - Error: Invalid Timer ID
 * 
 * @note Note the odd return value, this should be able to sorta be treated as a bool 
 *       but will need to be !await_timer() or await_timer()==0.
 *       This choice was made as to keep the return to an answer to the "is the timer
 *       expired" question but still report if the TimerID is out of index, doing this
 *       with this arrangement, where 0 means true and 1 means false is odd but lets 
 *       you use 'simpler' checks and not consider an ID error as a 'success' 
 */
 uint8_t timer_Await(TimerID_t which_Timer);

#endif // TIMER_H