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
static uint32_t get_Time(void);

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
static uint32_t get_Time(void)
{


}


/** =======================================================================
 *  Public API
 *  =======================================================================
 */

// Set the delay for a timer at runtime
void timerSetDelay(TimerID whichTimer, uint32_t delayMs)
{
    if (whichTimer < TIMER_COUNT)
    {
        timerDelay[whichTimer] = delayMs;
    }
}

void timerReset(TimerID whichTimer)
{
    if (whichTimer < TIMER_COUNT)
    {
        timerPrev[whichTimer] = get_Time();
    }
}

bool awaitTimer(TimerID whichTimer)
{
    uint32_t now = get_Time();
    if ((uint32_t)(now - timerPrev[whichTimer]) >= timerDelay[whichTimer])
    {
        timerPrev[whichTimer] = now;
        return true;
    }
    return false;
}
