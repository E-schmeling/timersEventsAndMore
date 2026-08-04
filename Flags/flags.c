/**
 * @file flags.c
 * @brief Simple flag implementation in C.
 * @author ERS
 *
 */

 /** =======================================================================
 *  Routine Defines
 *  =======================================================================
 */
#include <stdint.h>
#include <stdbool.h>

#include "flags.h"

#ifdef __cplusplus
    extern "C" 
        {
#endif


/** =======================================================================
 *  Global Variables
 *  =======================================================================
 */

/**
 * @brief Flag bitfield to store the flag
 * 
 * @note This implementation should hopefully adapt to the number of flags but i havent actually tested yet as of writing this docs.
 */
uint8_t flagBitField[FLAG_COUNT / 8 + 1] = {0};

/** =======================================================================
 *  Public API
 *  =======================================================================
 * see flags.h for more details.
 */

uint8_t flag_set(flag_t flag)
{
    if (flag < FLAG_COUNT)
    {
        uint32_t index = flag / 8;
        //Hopefully, due to being a power of 2, this will be optimised by the compiler.
        uint32_t bitPosition = flag % 8;
        flagBitField[index] |= (1U << bitPosition);
        return 0; // Success
    }
    return 1; // Error: Invalid flag
}

uint8_t flag_clear(flag_t flag)
{
    if (flag < FLAG_COUNT)
    {
        uint32_t index = flag / 8;
        uint32_t bitPosition = flag % 8;
        flagBitField[index] &= ~(1U << bitPosition);
        return 0; // Success
    }
    return 1; // Error: Invalid flag
}

bool flag_get(flag_t flag)
{
    if (flag < FLAG_COUNT)
    {
        uint32_t index = flag / 8;
        uint32_t bitPosition = flag % 8;
        return (flagBitField[index] & (1U << bitPosition)) != 0;
    }
    return false; // Error: Invalid flag
}

#ifdef __cplusplus
    }
#endif