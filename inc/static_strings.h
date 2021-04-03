
/** \file static_strings.h
 * \brief Strings allocation with static memory.
 */

#ifndef __STATIC_STRINGS_H
#define __STATIC_STRINGS_H

#include "stm32f1xx_hal.h"
#include "string.h"
#include "int_types.h"
#include "stdarg.h"
#include "stdio.h"

/** \defgroup string_types_sizes_quantities String types size and quantity
 * Constants to reserve a memory for the different types of strings according to their length
 * @{
*/
#define STATIC_STRINGS_VERY_SHORT_STRING_SIZE 50
#define STATIC_STRINGS_VERY_SHORT_STRING_QUANTITY 10

#define STATIC_STRINGS_SHORT_STRING_SIZE 100
#define STATIC_STRINGS_SHORT_STRING_QUANTITY 6

#define STATIC_STRINGS_MEDIUM_STRING_SIZE 200
#define STATIC_STRINGS_MEDIUM_STRING_QUANTITY 2

#define STATIC_STRINGS_LONG_STRING_SIZE 500
#define STATIC_STRINGS_LONG_STRING_QUANTITY 2

#define STATIC_STRINGS_VERY_LONG_STRING_SIZE 1500
#define STATIC_STRINGS_VERY_LONG_STRING_QUANTITY 2
/**@}*/

/** \defgroup string_types String types
 * Constants to identify the different types of strings according to their length
 * @{
 */
#define STATIC_STRINGS_STRING_TYPE_VERY_SHORT 0
#define STATIC_STRINGS_STRING_TYPE_SHORT 1
#define STATIC_STRINGS_STRING_TYPE_MEDIUM 2
#define STATIC_STRINGS_STRING_TYPE_LONG 3
#define STATIC_STRINGS_STRING_TYPE_VERY_LONG 4
#define STATIC_STRINGS_STRING_TYPE_CUSTOM 5
/**@}*/

/** \defgroup string_status String status
 * Constants to define the status of a string
 * @{
 */
#define STATIC_STRINGS_STRING_STATUS_DEALLOCATED 0
#define STATIC_STRINGS_STRING_STATUS_ALLOCATED 1
#define STATIC_STRINGS_STRING_STATUS_CONSTANT 2
/**@}*/

/** \defgroup error_handling Error handling
 * \brief Error codes.
 */
///@{
#define STATIC_STRINGS_ERROR_CODE_NO_ERROR 0
#define STATIC_STRINGS_ERROR_CODE_NO_MEMORY_AVAILABLE 1
#define STATIC_STRINGS_ERROR_CODE_INVALID_STRING 2
#define STATIC_STRINGS_ERROR_CODE_STRING_TOO_LONG 3
#define STATIC_STRINGS_ERROR_CODE_SUBSTRING_START_INDEX_OUT_OF_RANGE 4
#define STATIC_STRINGS_ERROR_CODE_SUBSTRING_FINISH_INDEX_OUT_OF_RANGE 5
#define STATIC_STRINGS_ERROR_CODE_STRING_OVERFLOW 6
/** static_strings_error_code
 * \brief Global variable to store error code.
 */
uint8_t static_strings_error_code;
///@}

/** \struct static_strings_string_descriptor
 * \brief Meta data of a string
 */
typedef struct static_strings_string_descriptor{
	uint8_t *string;
	uint16_t length;
	uint8_t type;
	uint8_t status;
}static_strings_string_descriptor;

/** \struct static_strings_string_splitter_parameters
 * \brief Definition of the structure to hold the parameters to static_stirngs_string_splitter_get_next_token function.
 */
typedef struct static_strings_string_splitter_parameters{
	static_strings_string_descriptor *string_descriptor;
	uint8_t* next_token_start;
	uint8_t delimiter;
}static_strings_string_splitter_parameters;

/** Parameters to static_strings_string_splitter_get_next_token function. Initialized in null and \0. */
extern static_strings_string_splitter_parameters static_strings_string_splitter;

/** \defgroup static_memory_arrays Static memory arrays
 * \brief Static memory arrays to allocate strings.
 */
///@{
uint8_t static_strings_very_short_string_memory[STATIC_STRINGS_VERY_SHORT_STRING_QUANTITY][STATIC_STRINGS_VERY_SHORT_STRING_SIZE];
uint8_t static_strings_short_string_memory[STATIC_STRINGS_SHORT_STRING_QUANTITY][STATIC_STRINGS_SHORT_STRING_SIZE];
uint8_t static_strings_medium_string_memory[STATIC_STRINGS_MEDIUM_STRING_QUANTITY][STATIC_STRINGS_MEDIUM_STRING_SIZE];
uint8_t static_strings_long_string_memory[STATIC_STRINGS_LONG_STRING_QUANTITY][STATIC_STRINGS_LONG_STRING_SIZE];
uint8_t static_strings_very_long_string_memory[STATIC_STRINGS_VERY_LONG_STRING_QUANTITY][STATIC_STRINGS_VERY_LONG_STRING_SIZE];
///@}

/** \defgroup string_descriptors String descriptors
 * \brief Descriptors for all the string types.
 */
///@{
static_strings_string_descriptor static_strings_very_short_strings_descriptors[STATIC_STRINGS_VERY_SHORT_STRING_QUANTITY];
static_strings_string_descriptor static_strings_short_strings_descriptors[STATIC_STRINGS_SHORT_STRING_QUANTITY];
static_strings_string_descriptor static_strings_medium_strings_descriptors[STATIC_STRINGS_MEDIUM_STRING_QUANTITY];
static_strings_string_descriptor static_strings_long_strings_descriptors[STATIC_STRINGS_LONG_STRING_QUANTITY];
static_strings_string_descriptor static_strings_very_long_strings_descriptors[STATIC_STRINGS_VERY_LONG_STRING_QUANTITY];
///@}

/** \defgroup constant_strings Constant strings
 * \brief Common use constant strings.
 */
///@{
extern static_strings_string_descriptor *static_strings_new_line;
extern static_strings_string_descriptor *static_strings_empty;
///@}

/** void static_strings_init()
 * \brief Link the descriptors with the arrays and initialize the status as deallocated.
 * Also can be used to reset the state of all the string descriptors.
 */
void static_strings_init();

/** int static_strings_get_string_max_length(static_strings_string_descriptor *string)
 * \brief get the maximum length allowed by the type of the string.
 * \param string A pointer to a string descriptor.
 * \return The maximum allowed length of the string as an integer.
 */
int static_strings_get_string_max_length(static_strings_string_descriptor *string);

/** static_strings_string_descriptor *static_strings_copy(static_strings_string_descriptor *copy_to,static_strings_string_descriptor *copy_from,uint16_t copy_to_offset)
 * \brief Copy a string into another at determinate offset.
 * Leaves intact the string values before the offset.
 * Can throw STATIC_STRINGS_ERROR_CODE_STRING_OVERFLOW.
 * \param copy_to Pointer to the string to copy in. String must have a defined type and length before use this function
 * \param copy_from Pointer to the string to copy from.
 * \param copy_to_offset Start copy index.
 * \return A pointer to the descriptor with the copied string if success, if an error occur return NULL, check static_strings_error_code for further information.
 */
static_strings_string_descriptor *static_strings_copy(static_strings_string_descriptor *copy_to,static_strings_string_descriptor *copy_from,uint16_t copy_to_offset);

/** static_strings_string_descriptor *static_strings_move(static_strings_string_descriptor *move_to,static_strings_string_descriptor *move_from,uint16_t move_to_offset)
 * \brief Move a string into another at determinate offset, if success the move_to string is deallocated.
 * Can throw STATIC_STRINGS_ERROR_CODE_STRING_OVERFLOW.
 * Leaves intact the string values before the offset.
 * \param move_to Pointer to the string to move in. String must have a defined type and length before use this function
 * \param move_from Pointer to the string to move from.
 * \param move_to_offset Start move index.
 * \return A pointer to the descriptor with the moved string if success, if an error occur return NULL, check static_strings_error_code for further information.
 */
static_strings_string_descriptor *static_strings_move(static_strings_string_descriptor *move_to,static_strings_string_descriptor *move_from,uint16_t move_to_offset);

/** static_strings_string_descriptor *static_strings_clone(static_strings_string_descriptor *clone_from)
 * \brief Clone a string into a new one.
 * \param clone_from Pointer to the string to clone.
 * \return A pointer to the descriptor with the cloned string if success, if an error occur return NULL, check static_strings_error_code for further information.
 */
static_strings_string_descriptor *static_strings_clone(static_strings_string_descriptor *clone_from);

/** static_strings_string_descriptor *static_strings_allocate(uint16_t string_size)
 * \brief Request memory for a string with its size, the user must copy the string with the descriptor and specify the size.
 * Also see static_strings_save.
 * \param string_size Size of the string in uint16_t.
 * \return A pointer to the string descriptor, if NULL check static_strings_error_code.
 */
static_strings_string_descriptor *static_strings_allocate(uint16_t string_size);

/** static_strings_string_descriptor *static_strings_save(uint8_t *string)
 * \brief Calculate the string size, allocate memory, copy the string and set the size.
 * String must end with \\r\\n or \\0, if \\r is found but \\n is not found, it is added, size of string include line ending but not \\0.
 * Also see static_strings_allocate.
 * \param string A pointer to the string start.
 * \return A pointer to the string descriptor, if NULL check static_strings_error_code.
 */
static_strings_string_descriptor *static_strings_save(uint8_t *string);

/** void static_strings_create_custom_string(static_strings_string_descriptor *string_descriptor,uint8_t *string)
 * \brief Bind the provided string descriptor with the data of a string.
 * String must end with \\r\\n or \\0.
 * \param string_descriptor A pointer to a string descriptor.
 * \param string A pointer to the string to bind the descriptor.
 * \return Return the length of the string, if 0 check static_strings_error_code.
 */
int static_strings_create_custom_string(static_strings_string_descriptor *string_descriptor,uint8_t *string);

/** void static_strings_deallocate(static_strings_string_descriptor *string_descriptor)
 * \brief Set the descriptor status as deallocated. Custom strings can't be deallocated.
 * \param string_descriptor A pointer to the string descriptor to deallocate.
 */
void static_strings_deallocate(static_strings_string_descriptor *string_descriptor);

/** int static_strings_is_line(static_strings_string_descriptor *string_descriptor)
 * \brief Look at the last two characters of a string to see if the string has a line ending \\r\\n.
 * \param string A pointer to the string descriptor.
 * \return Return 0 if the string does't have a line ending \\r\\n and 1 if the string has a line ending \\r\\n.
 */
int static_strings_is_line(static_strings_string_descriptor *string_descriptor);

/** uint16_t static_strings_strlen(uint8_t *string)
 * \brief Calculate the length of a string that ends with \\r\\n or \\0, line ending is included in length.
 * Maximum length is STATIC_STRINGS_VERY_LONG_STRING_SIZE.
 * \param string A pointer to the string.
 * \return Length of the string in uint16_t. If 0 check static_strings_error_code.
 */
uint16_t static_strings_strlen(uint8_t *string);

/** void static_strings_string_splitter_set_parameters(static_strings_string_descriptor *string_descriptor,uint8_t delimiter)
 * \brief Set the parameters to the static_strings_string_splitter_get_next_token function.
 * \param string_descriptor A pointer to the string descriptor of the string to split.
 * \param delimiter The delimiter for the tokens.
 */
void static_strings_string_splitter_set_parameters(static_strings_string_descriptor *string_descriptor,uint8_t delimiter);

/** int static_strings_string_splitter_get_next_token(static_strings_string_descriptor **string_descriptor)
 * \brief Bind the provided string descriptor with the next token data.
 * Can be placed in a while condition as it returns 1 if success or 0 if no token available and retrieves the token in the string_descriptor parameter.
 * If no delimiter the whole string is taken as token.
 * The token is placed in a new string.
 * \param string_descriptor A pointer to a pointer to a string descriptor that will contain the token.
 * \return 1 if success or 0 if no token is available.
 */
int static_strings_string_splitter_get_next_token(static_strings_string_descriptor **string_descriptor);

/** static_strings_string_descriptor *static_strings_substring(static_strings_string_descriptor* string_descriptor,uint16_t start_index,uint16_t finish_index)
 * \brief Return a new string with the characters between the start_index and the finish_index.
 * Not including the character at finish_index.
 * Returned string has to be deallocated.
 * To get all the string from a start index use the length in the finish_index.
 * \param string_descriptor A pointer to the string which contains the substring.
 * \param start_index The index of the first character.
 * \param finish_index The index of the last character, not included.
 * \return A pointer to the string descriptor of the substring, if NULL check static_strings_error_code.
 */
static_strings_string_descriptor *static_strings_substring(static_strings_string_descriptor* string,uint16_t start_index,uint16_t finish_index);

/** static_strings_string_descriptor *static_strings_concatenate(static_strings_string_descriptor* concatenate_at,static_strings_string_descriptor* concatenate)
 * \brief Concatenate the second string at the end of the first in a new string.
 * \param concatenate_at A pointer to the string to concatenate at.
 * \param concatenate A pointer to the string to concatenate at the end of the concatenate_at string.
 * \return A pointer to the string descriptor with the concatenated string, if NULL check static_strings_error_code.
 */
static_strings_string_descriptor *static_strings_concatenate(static_strings_string_descriptor* concatenate_at,static_strings_string_descriptor* concatenate);

/** static_strings_string_descriptor *static_strings_concatenate_and_clean(static_strings_string_descriptor* concatenate_at,static_strings_string_descriptor* concatenate)
 * \brief Concatenate the second string at the end of the first in a new string and deallocate the concatenate at parameter if success.
 * \param concatenate_at A pointer to the string to concatenate at, it is deallocates if success.
 * \param concatenate A pointer to the string to concatenate at the end of the concatenate_at string.
 * \return A pointer to the string descriptor with the concatenated string, if NULL check static_strings_error_code.
 */
static_strings_string_descriptor *static_strings_concatenate_and_clean(static_strings_string_descriptor* concatenate_at,static_strings_string_descriptor* concatenate);

/** static_strings_string_descriptor *static_strings_concatenate_and_clean(static_strings_string_descriptor* concatenate_at,static_strings_string_descriptor* concatenate)
 * \brief Concatenate the second string at the end of the first in a new string and deallocate both parameters.
 * \param concatenate_at A pointer to the string to concatenate at, it is deallocates if success.
 * \param concatenate A pointer to the string to concatenate at the end of the concatenate_at string, it is deallocates if success.
 * \return A pointer to the string descriptor with the concatenated string, if NULL check static_strings_error_code.
 */
static_strings_string_descriptor *static_strings_concatenate_and_clean_both(static_strings_string_descriptor* concatenate_at,static_strings_string_descriptor* concatenate);

/** static_strings_string_descriptor *static_strings_concatenate_all(uint16_t arguments_quantity,...)
 * \brief Concatenates multiple strings in the order of the arguments, the number of arguments must be provided in the first parameter.
 * This function must be used careful.
 * \param arguments_quantity The number of strings to concatenate.
 * \param ... Multiple arguments of type static_strigs_string_descriptor pointer.
 * \return A pointer to the string descriptor with the concatenated string, if NULL check static_strings_error_code.
 */
static_strings_string_descriptor *static_strings_concatenate_all(uint16_t arguments_quantity,...);

/** static_strings_string_descriptor *static_strings_concatenate_all(uint16_t arguments_quantity,...)
 * \brief Concatenates multiple strings in the order of the arguments, the number of arguments must be provided in the first parameter.
 * All the parameters are deallocated if success.
 * This function must be used careful.
 * \param arguments_quantity The number of strings to concatenate.
 * \param ... Multiple arguments of type static_strigs_string_descriptor pointer, these parameters are deallocated if success.
 * \return A pointer to the string descriptor with the concatenated string, if NULL check static_strings_error_code.
 */
static_strings_string_descriptor *static_strings_concatenate_and_clean_all(uint16_t arguments_quantity,...);

/** int static_strings_contains_string(static_strings_string_descriptor* search_in,static_strings_string_descriptor* search_for)
 * \brief Search a string in other string.
 * \param search_in A pointer to the string in which the character will be search.
 * \param search_for A pointer to the searched string.
 * \return 1 if the string is found, 0 if not.
 */
int static_strings_contains_string(static_strings_string_descriptor* search_in,static_strings_string_descriptor* search_for);

/** int static_strings_contains_char(static_strings_string_descriptor* search_in,uint8_t search_for)
 * \brief Search a character in a string.
 * \param search_in A pointer to the string in which the character will be search.
 * \param search_for The searched character.
 * \return 1 if the character is found, 0 if not.
 */
int static_strings_contains_char(static_strings_string_descriptor* search_in,uint8_t search_for);

/** int static_strings_compare(static_strings_string_descriptor* compare_string_one,static_strings_string_descriptor* compare_string_two)
 * \brief Compare two strings to see if they are equals.
 * \param compare_string_one A pointer to the first string to compare.
 * \param compare_string_two A pointer to the second string to compare.
 * \return A pointer to the string descriptor with the concatenated string, if NULL check static_strings_error_code.
 */
int static_strings_compare(static_strings_string_descriptor* compare_string_one,static_strings_string_descriptor* compare_string_two);

/** static_strings_string_descriptor *static_strings_uint8_to_string(uint8_t uint8)
 * \brief Create a string with the value of the parameter.
 * \param uint8 8 bits unsigned integer.
 * \return A pointer to the string descriptor with the parameter as string.
 */
static_strings_string_descriptor *static_strings_uint8_to_string(uint8_t uint8);

/** static_strings_string_descriptor *static_strings_uint16_to_string(uint16_t uint16)
 * \brief Create a string with the value of the parameter.
 * \param uint16 16 bits unsigned integer.
 * \return A pointer to the string descriptor with the parameter as string.
 */
static_strings_string_descriptor *static_strings_uint16_to_string(uint16_t uint16);

/** static_strings_string_descriptor *static_strings_uint32_to_string(uint32_t uint32)
 * \brief Create a string with the value of the parameter.
 * \param uint32 32 bits unsigned integer.
 * \return A pointer to the string descriptor with the parameter as string.
 */
static_strings_string_descriptor *static_strings_uint32_to_string(uint32_t uint32);

/** static_strings_string_descriptor *static_strings_int8_to_string(int8_t int8)
 * \brief Create a string with the value of the parameter.
 * \param int8 8 bits signed integer.
 * \return A pointer to the string descriptor with the parameter as string.
 */
static_strings_string_descriptor *static_strings_int8_to_string(int8_t int8);

/** static_strings_string_descriptor *static_strings_int16_to_string(int16_t int16)
 * \brief Create a string with the value of the parameter.
 * \param int16 16 bits signed integer.
 * \return A pointer to the string descriptor with the parameter as string.
 */
static_strings_string_descriptor *static_strings_int16_to_string(int16_t int16);

/** static_strings_string_descriptor *static_strings_int32_to_string(int32_t int32)
 * \brief Create a string with the value of the parameter.
 * \param int32 32 bits signed integer.
 * \return A pointer to the string descriptor with the parameter as string.
 */
static_strings_string_descriptor *static_strings_int32_to_string(int32_t int32);

/** static_strings_string_descriptor *static_strings_float_to_string(float float_arg)
 * \brief Create a string with the value of the parameter.
 * \param float_arg 16 bits signed float.
 * \return A pointer to the string descriptor with the parameter as string.
 */
static_strings_string_descriptor *static_strings_float_to_string(float float_arg);

/** static_strings_string_descriptor *static_strings_double_to_string(double double_arg)
 * \brief Create a string with the value of the parameter.
 * \param double_arg 32 bits signed float (double).
 * \return A pointer to the string descriptor with the parameter as string.
 */
static_strings_string_descriptor *static_strings_double_to_string(double double_arg);

#endif
