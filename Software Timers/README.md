# Software timer framework

This is a software timer framework that allows you to set up timers with specific delays and check if they have expired. It provides functions to reset the timers and change their delays at runtime. The framework is designed to be device-agnostic, allowing you to implement the `get_Time` function according to your specific hardware requirements.

I assume most people reading this, are familiar with why I am specifying *software* timer. If not, alot of devices have hardware timers built into the device that are accessible via a register or memory location. These hardware timers are typically used for tasks such as generating periodic interrupts, timing events, and managing timeouts.

This implementation does not hook into these hardware timers but instead relies on a "time since boot" value(preferably in milliseconds but, techincally, it could be in seconds or microseconds, as long as the delay duration is converted as well). Which from what I have seen is commonly available. 

 
## Structure
 - `swTimer.h`: Header file containing the public API.
 - `swTimer.c`: Source file containing the implementation of the public API.
 - `Examples/`: Examples on how to use the framework.

## How to use

In `swTimer.c` the functions that need to be modify are:

- `get_TimeMS(void)`: Function that returns the current time in milliseconds.

Additionally, the struct:
- `TimerID_t`: Enumerated type representing different timers.

needs to be modified in `swTimer.h` to include the list of timers for the project. Besides these; the minimium required functions/features to get started with the framework are:
- `await_Timer(TimerID)`: Timer Expiration check function.
- `timer_Reset(TimerID)`: Reset timer function.

Additional features to get and set the delay of a timer are:
- `uint8_t timer_Get_Delay(TimerID_t, uint32_t*)`: Get current delay of a timer.
- `uint8_t timer_Set_Delay(TimerID_t, uint32_t)`: Set current delay of a timer.

> Note the await_Timer function will Reset the timer if it has expired. This is mostly to simplify use in a cyclical case where "I need to do this every X seconds". If you need to do something only once after X seconds, then you should reset the timer when you wish to start the countdown.


> Note that if the hardware requires any initialisation, initialisation needs to be done before the first use of timer functions. There is no software check on this side as there is no INIT. <p> At somepoint I may write this to require a struct pass-in like the state machine framwork which would give the requirement of an init function where I could add in a hardware specific init function. But when I started this today, I wasnot happy with how things were shaping out with it as it required alot more overhead for each function then I really wanted, so I decided to put it off for a while longer. <p> I really didnt like the declaration of a timer struct as{id, delay, prevTime} as including the prev time as a configurable variable is not really something I want to allow as its strange and could easily lead to bugs. 


## Public API

### `timer_Await(TimerID_t which_Timer)`
Querries the specified time to see if it has expired.

It will return:
- 0 if it has expired 
- \>0 if it has not expired or a configuration error:
    - 1 if timer has expired
    - 2 if invalid Timer ID

This design choice was made to keep the function with a simple return with a boolean value while still reporting an out of index ID value. The ways to check this value in a simple boolean is:
- `if( !timer_await(ID) )`
- `if( timer_await(ID) == 0 )`

these methods will enter the if statement when the timer has expired, but on error or unexpired will not. 

> If the timer has expired the timer will automatically reset when the function is called. 

### `timer_Reset(TimerID_t which_Timer)`

Resets the specified timer, setting the previous alarm time to the present time value. this is used when you want a known start point for a timer.

It will return:
- 0 - Success
- 1 - Error: Invalid Timer ID


### `timer_Set_Delay(TimerID_t which_Timer, uint32_t delayMS)`

Changes the duration which a timer will count for. If you have a timer that you resuse for multiple purposes or its use can vary in length this can be used to reconfigure the time. 

It will return:
- 0 - Success
- 1 - Error: Invalid Timer ID

> Note that setting a new timer duration will reset the timer countdown this is to keep a consistent behaviour dispite the changing timeout duration. 

> Note setting the delay to the same time as before will also reset the timer countdown, again consitency.



### `timer_Get_Delay(TimerID_t which_Timer, uint32_t* delayMs)`
Feeds the current Delay for a specific Timer to the pointer provided by the user. This is useful if you need to know how long a timer will count down.

It will return:

- 0 - Success
- 1 - Error: Invalid Timer ID

and the provided `uint32_t delayMs` pointer will contain the current duration of timer. 


## Restrictions
Due to the use of the `uint32_t` type to store the delay the maximum duration that can be set is 2^32 or 4,294,967,295 milliseconds or 49.7 days, if you need more than this, what are you doing??? please let me know! 

Alternatively:
- Seconds: >136 years
- MicroSeconds: 1.1 hours

But lets be clear if you are using microseconds you should be using hardware timers and also not using my code. Please let me know if you need help with that! It's quite easy to not use my code, I can provide simple instructions!

Otherwise, the code is designed to be simple and easy to understand, with no complex algorithms or data structures. It should work on any platform that supports the standard C and should take up minimal RAM and Flash memory. At some point I will determine exactly how much each of these modules takes up, but that is not today. 

## AI Use

AI was used exclusively for documentation support, through the use of GitHub Copilot's inline suggestions and a local Gwen Coder 2.5 7B model when copilot's inline suggestions were not available.

## Example

See `Examples/` if its empty, you got this, but I will likely* add examples as I implement this 