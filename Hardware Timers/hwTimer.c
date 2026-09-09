/**
 * @file hwTimer.c
 * @brief Hardware Timer framework implementaion.
 * @author ERS
 *
 * This module contains the implementation of the hardware timer framework. It is really not needed, but I am using it 
 */

/** =======================================================================
 *  Routine Defines
 *  =======================================================================
 */
#include <stdbool.h>

#include "hwTimer.h"

// Optional Feature
// #define ENABLE_HW_TIMER_FALLTHROUGH

/** =======================================================================
 *  Device-specific Defines
 *  =======================================================================
 */




/** =======================================================================
 *  Function prototypes for internal routines
 *  =======================================================================
 */

static uint8_t timer_resolve(hwTimer_t timer);


/** =======================================================================
 *  Device-specific function prototypes
 *  =======================================================================
 * 
 */
// These functions are device specific and their implementations should change based on the hardware platform.
static uint8_t hwtimer_backend_init();
static uint8_t hwtimer_backend_arm(hwTimer_t timer, uint32_t msTime);
static uint8_t hwtimer_backend_disarm(hwTimer_t timer);




/** =======================================================================
 *  Global Variables
 *  =======================================================================
 */

bool isInitialised = false;

uint8_t timerStatus[TIMER_COUNT] = {0};

hwTimer_Callback_t timerCallback[TIMER_COUNT] = {0};




/** =======================================================================
 *  Device-specific implementations (to be customized)
 *  =======================================================================
 */

static uint8_t hwtimer_backend_init()
{
    return 0;
}

static uint8_t hwtimer_backend_arm(hwTimer_t timer, uint32_t msTime)
{
    return 0;
}

static uint8_t hwtimer_backend_disarm(hwTimer_t timer)
{
    return 0;
}


//for any callback handlers, directly call into timer_resolve with the id of the timer 
void TC0_Handler(void)
{
    timer_resolve(TIMER_ONE);
}



/** =======================================================================
 *  Internal API
 *  =======================================================================
 */

/**
 * @internal
 * @brief Resolves the timer; Fall to here in all timer callback handler with the ID of the timer that expired,
 *          in the case that all timers run the same callback function you can probably modify this to make 
 * @param timer The ID of the timer that expired.
 * @return Error Codes
 *          0 - Success
 *          1 - Error: Invalid Timer ID
 */
static uint8_t timer_resolve(hwTimer_t timer)
{
    if (timer >= TIMER_COUNT)
    {
        return 1; // Error: Invalid Timer ID
    }
    // Stop the event source before the callback; ISR-context failures have no public error path.
    (void)hwtimer_backend_disarm(timer);
    timerCallback[timer]();
    timerStatus[timer] = false;
    timerCallback[timer] = 0; 

    return 0; // Success
}


/** =======================================================================
 *  Public API
 *  =======================================================================
 * see `hwTimer.h` for documentation.
 */

uint8_t hwTimers_init()
{
    uint8_t status = hwtimer_backend_init();
    if(status != 0)
    {
        return status; // Return the error code from initialising timers
    }
    isInitialised = true;
    return 0; // Success
}


uint8_t hwTimers_set(hwTimer_t timer, uint32_t msTime, hwTimer_Callback_t callback)
{
    if(timer >= TIMER_COUNT)
    {
       return 2; //Error: Invalid timer
    }
    if(timerStatus[timer] == 1)
    {
        return 1; //Error: Selected timer is already running
    }
    if(isInitialised == false)
    {
        return 3; //Error: Hardware timers are not initalised 
    }
    if(callback == 0)
    {
        return 4; //Error: Invalid callback function
    }
    if(msTime == 0)
    {
        return 5; //Error: Time cannot be zero
    }

    timerCallback[timer] = callback;
    timerStatus[timer] = 1;

    uint8_t status = hwtimer_backend_arm(timer, msTime);
    if(status != 0)
    {
        timerCallback[timer] = 0;
        timerStatus[timer] = 0;
        return 8 + status; //Error: User defined error in setting the timer 
    } 
    return 0; // Success

}

uint8_t hwTimers_disarm(hwTimer_t timer)
{
    if (timer >= TIMER_COUNT)
    {
        return 2; // Error: Invalid timer
    }
    if (isInitialised == false)
    {
        return 3; // Error: Hardware timers are not initialised
    }
    if (timerStatus[timer] == 0)
    {
        return 1; // Error: Selected timer is not running
    }

    uint8_t status = hwtimer_backend_disarm(timer);
    if (status != 0)
    {
        return 8 + status; // Error: User defined error in disarming the timer
    }

    timerCallback[timer] = 0;
    timerStatus[timer] = 0;
    return 0; // Success


}