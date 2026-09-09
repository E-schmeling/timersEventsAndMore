/**
 * @file hwTimer.h
 * @brief Hardware Timer Framework.
 * @author ERS
 *
 */
#ifndef HWTIMER_H
#define HWTIMER_H

/** =======================================================================
 *  Defines
 *  =======================================================================
 */
#include <stdint.h>


/** =======================================================================
 *  Enumerations and Types
 *  =======================================================================
 */
typedef enum {
    TIMER_ONE = 0,
    TIMER_TWO,
    TIMER_THREE,

    TIMER_COUNT,
} hwTimer_t;

/**
 * @brief Callback type for hardware timers.
 */
typedef uint8_t (*hwTimer_Callback_t)();





/** =======================================================================
 *  Public API 
 *  =======================================================================
 */
/**
 * @brief Initialises all hardware timers and sets up their callbacks
 * 
 * @return Error Codes
 *          0 - Success
 *          n - Back end init error n
 */
uint8_t hwTimers_init();

/**
 * @brief Starts a timer with the specified time and callback function.
 * 
 * @param timer The timer to start.
 * @param msTime The time in milliseconds for the timer to expire at.
 * @param callback The function to call when the timer expires.
 *
 * The callback runs in interrupt context and must be brief and non-blocking.
 * Do not globally disable interrupts for callback execution, and do not call
 * this function for the same timer until its current callback has returned.
 * 
 * @return Error codes
 *          0 - Success
 *          1 - Selected timer is already running
 *          2 - Invalid timer
 *          3 - Hardware timers are not initialised
 *          4 - Invalid Callback Function
 *          5 - Time cannot be zero
 *      8 + n - Backend arm error n
 */
uint8_t hwTimers_set(hwTimer_t timer, uint32_t msTime, hwTimer_Callback_t callback);

/**
 * @brief Stops a running timer and clears its callback.
 *
 * The backend must prevent future events from the timer and clear any stale
 * pending interrupt condition. Target-specific code must protect shared
 * manager state when foreground code can disarm while an ISR may resolve the
 * same timer.
 *
 * @param timer The timer to stop.
 *
 * @return Error codes
 *          0 - Success
 *          1 - Timer is not running
 *          2 - Invalid timer
 *          3 - Hardware timers are not initialised
 *      8 + n - Backend disarm error n
 */
uint8_t hwTimers_disarm(hwTimer_t timer);
#endif // HWTIMER_H