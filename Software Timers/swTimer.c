/**
 * @file swTimer.c
 * @brief Timer Framework.
 * @author ERS
 *
 */

/** =======================================================================
 *  Routine Defines
 *  =======================================================================
 */
#include "swTimer.h"

/** =======================================================================
 *  Device-specific Defines
 *  =======================================================================
 */



/** =======================================================================
 *  Function prototypes for internal routines
 *  =======================================================================
 */
static uint32_t get_TimeMS(void);

/** =======================================================================
 *  Global Variables
 *  =======================================================================
 */

static uint32_t timerDelay[TIMER_COUNT] = {
    1000,
    1000,
    1000,
    10000,
    15000 
};

static uint32_t timerPrev[TIMER_COUNT] = {0};

/** =======================================================================
 *  Device-specific implementations (to be customized)
 *  =======================================================================
 */
/**
 * @internal
 * @brief Get the current time in milliseconds.
 *
 * @return The current time in milliseconds.
 *
 * @note This function should be implemented according to the specific hardware platform being used.
 */
static uint32_t get_TimeMS(void)
{


}


/** =======================================================================
 *  Public API
 *  =======================================================================
 * see swTimer.h for more details.s
 */
uint8_t timer_Set_Delay(TimerID_t which_Timer, uint32_t delayMs)
{
    if (which_Timer < TIMER_COUNT || which_Timer < 0)
    {
        timerDelay[which_Timer] = delayMs;
        timerPrev[which_Timer] = get_TimeMS();
        return 0; // Success
    }
    else
    {
        return 1; // Error: Invalid Timer ID
    }
}

uint8_t timer_Get_Delay(TimerID_t which_Timer, uint32_t* delayMs)
{
    if (which_Timer < TIMER_COUNT || which_Timer < 0)
    {
        delayMs = timerDelay[which_Timer];
        return 0; // Success
    }
    else
    {
        return 1; // Error: Invalid Timer ID
    }
}



uint8_t timer_Reset(TimerID_t which_Timer)
{
    if (which_Timer < TIMER_COUNT || which_Timer < 0)
    {
        timerPrev[which_Timer] = get_TimeMS();
        return 0; //Success
    }
    else
    {
        return 1; //Error: Invalid Timer ID
    }
}

uint8_t timer_Await(TimerID_t which_Timer)
{
    uint32_t now = get_TimeMS();
    if (which_Timer >= TIMER_COUNT || which_Timer < 0)
    {
        return 2; //Error: Invalid Timer ID
    }
    
    
    if ((uint32_t)(now - timerPrev[which_Timer]) >= timerDelay[which_Timer])
    {
        timerPrev[which_Timer] = now;
        return 0;
    }

    return 1;
}