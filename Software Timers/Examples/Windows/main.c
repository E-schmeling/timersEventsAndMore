#include <stdio.h>
#include <windows.h>


#include "swTimer.h"

int main(void)
{
    printf("hello WORLD:\n");

    swTimer_setDelay(TIMER_ONE,1000);
    swTimer_setDelay(TIMER_TWO,2500);

    while(1)
    {
        if(swTimer_await(TIMER_ONE) == 0)
        {
            printf("timer ONE\n");

        }
        if(swTimer_await(TIMER_TWO) == 0)
        {
            printf("timer TWO \n");

        }
    
    }
    return 0;
}