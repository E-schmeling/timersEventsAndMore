# Software timer framework

This is a software timer framework that allows you to set up timers with specific delays and check if they have expired. It provides functions to reset the timers and change their delays at runtime. The framework is designed to be device-agnostic, allowing you to implement the `get_Time` function according to your specific hardware requirements.

I assume most people reading this, are familiar with why I am specifying *software* timer. 
 
## Structure
 - `swTimer.h`: Header file containing the public API.
 - `swTimer.c`: Source file containing the implementation of the public API.
 - `Examples/`: Examples on how to use the framework.

## How to use

The key integration points are:

- `TimerID`: Enumerated type representing different timers.
- `await_Timer(TimerID which_Timer)`: 
- `timer_Reset(TimerID which_Timer)`:



## Public API

### `blah`


### `blah`


### `blah`


### `blah`


### `blah`


## Restrictions


## AI Use

AI was used here for documentation support, through the use of GitHub Copilot's inline suggestions and a local Gwen Coder 2.5 7B model when copilot's inline suggestions were not available.

## Short Example

