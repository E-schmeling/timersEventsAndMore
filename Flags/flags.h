
/**
 * @file flags.h
 * @brief Simple flag implementation in C.
 * @author ERS
 *
 */
#ifndef FLAGS_H
#define FLAGS_H

/** =======================================================================
 *  Defines
 *  =======================================================================
 */
#include <stdint.h>
#include <stdbool.h>


/** =======================================================================
 *  Enumerations and Types
 *  =======================================================================
 */
/**
 * @brief Listical enumeration of flags, last index must be FLAG_COUNT, used in bounds checking and getting the appropriate amount of uint8_t
 */
typedef enum
{
    FLAG_1 = 0,
    FLAG_2,
    FLAG_3,

    FLAG_COUNT
} flag_t;

/** 
 * @brief Sets the specified flag.
 * 
 * @param flag The flag to set
 * 
 * @return return errors:
 *              0 - Success
 *              1 - Error: Invalid flag
 */
uint8_t flag_set(flag_t flag);

/** 
 * @brief Clears the specified flag.
 * 
 * @param flag The flag to clear
 * 
 * @return return errors:
 *              0 - Success
 *              1 - Error: Invalid flag
 */
uint8_t flag_clear(flag_t flag);

/** 
 * @brief Returns the status of the specific flag.
 * 
 * @param flag The flag to get
 * 
 * @return return errors:
 *              0 - Flag does not exist or is not set
 *              1 - Flag exists and is set
 */
bool flag_get(flag_t flag);


#endif // FLAGS_H