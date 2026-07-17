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

static uint32_t timer_Delay[TIMER_COUNT] = {
    1000,
    1000,
    1000,
    10000,
    15000 
};

static uint32_t timer_Prev[TIMER_COUNT] = {0};

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
void timer_Set_Delay(TimerID which_Timer, uint32_t delayMs)
{
    if (which_Timer < TIMER_COUNT)
    {
        timer_Delay[which_Timer] = delayMs;
    }
}

void timer_Reset(TimerID which_Timer)
{
    if (which_Timer < TIMER_COUNT)
    {
        timer_Prev[which_Timer] = get_Time();
    }
}

bool await_Timer(TimerID which_Timer)
{
    uint32_t now = get_Time();
    if ((uint32_t)(now - timer_Prev[which_Timer]) >= timer_Delay[which_Timer])
    {
        timer_Prev[which_Timer] = now;
        return true;
    }
    return false;
}
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
 */
uint8_t timerSetDelay(TimerID whichTimer, uint32_t delayMs)
{
    if (whichTimer < TIMER_COUNT)
    {
        timerDelay[whichTimer] = delayMs;
    }
    else
    {
        return 1; // Error: Invalid Timer ID
    }
}

uint8_t timerReset(TimerID whichTimer)
{
    if (whichTimer < TIMER_COUNT)
    {
        timerPrev[whichTimer] = get_Time();
    }
    else
    {
        return 1; //Error: Invalid Timer ID
    }
}

uint8_t timerAwait(TimerID whichTimer)
{
    uint32_t now = get_TimeMS();
    if (whichTimer >= TIMER_COUNT)
    {
        return 2; //Error: Invalid Timer ID
    }
    
    
    if ((uint32_t)(now - timerPrev[whichTimer]) >= timerDelay[whichTimer])
    {
        timerPrev[whichTimer] = now;
        return 0;
    }

    return 1;
}