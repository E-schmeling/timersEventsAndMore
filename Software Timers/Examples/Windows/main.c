#include <stdio.h>
#include <windows.h>


#include "swTimer.h"

int main(void)
{
    printf("hello WORLD:\n");

    timer_Set_Delay(TIMER_ONE,1000);
    timer_Set_Delay(TIMER_TWO,2500);

    while(1)
    {
        if(timer_Await(TIMER_ONE) == 0)
        {
            printf("timer ONE\n");

        }
        if(timer_Await(TIMER_TWO) == 0)
        {
            printf("timer TWO \n");

        }
    
    }
    return 0;
}