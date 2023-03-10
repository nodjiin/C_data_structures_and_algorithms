/**
 * \file			datatype.h
 * \brief           header file containing the definition of the generic data type used in all the structures of this library.
 */

#ifndef DATATYPE
#define DATATYPE

#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \brief           macro representing a NULL definition for the chosen data type.
 * \hideinitializer
 */
#define NULL_DATA         0

/**
 * \brief           macro representing the minimum possible value of the chosen data type.
 * \hideinitializer
 */
#define MIN_DATA          INT_MIN

/**
 * \brief           macro representing the format to use while printing a data type.
 *                  TODO this won't work on complex data types like structures, probably a print macro would be better
 * \hideinitializer
 */
#define DATA_PRINT_FORMAT "%d"

/**
 * \brief           data type of the values contained in all the data structures of this library.
 */
typedef int data_type;

/**
 * \brief           function used to compare 2 data_type values.
 * \param[in]       a: first value used in the comparison.
 * \param[in]       2: second value used in the comparison.
 * \return          a value greater than 0 if a is greater than b, lesser than 0 is a is lesser than b and 0 if a is equal to b.
 */
typedef int (*data_type_compare_fn)(const data_type a, const data_type b);

/**
 * \brief           data type of the key values used in the data structures containing a key/value pair in this library.
 */
typedef char* key_type;

/**
 * \brief           function used to compare 2 key_type values.
 * \param[in]       a: first value used in the comparison.
 * \param[in]       2: second value used in the comparison.
 * \return          a value greater than 0 if a is greater than b, lesser than 0 is a is lesser than b and 0 if a is equal to b.
 */
typedef int (*key_type_compare_fn)(const key_type a, const key_type b);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // !DATATYPE
