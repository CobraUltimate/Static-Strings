
/**
 * \mainpage Static Strings
 * \author Ramsés F. Pérez
 * \date August 2020
 * \version 1.0.1
 *
 * **Features:**
 *
 * - Developed for the STM32F103.
 * - Global scope strings.
 * - Configurable quantity and size of the memory arrays.
 * - No dynamic memory allocation.
 * - Customizable quantity and length of string types.
 * - Create custom string function to create local scope strings.
 * - String length function.
 * - String can be \\0 terminated and \\r\\n terminated.
 * - String split function.
 * - Fast string creation with save.
 * - Low level string creation with allocate.
 * - Reusable memory with deallocate.
 * - is_line function.
 * - String split.
 *
 * \n
 * **GETTING STARTED**
 *
 * \n
 * **Suggested names**
 * \n
 *
 * @code
 * static_strings_string_descriptor string_name;
 * uint8_t string_name_memory[];
 * @endcode
 *
 * \n
 * **Creating a string**
 * \n
 *
 * @code
 * uint8_t test_memory[] = "Hello Word\r\n";
 * static_strings_string_descriptor *test = static_strings_save(test_memory);
 * if(test == NULL){
 *   Error Handling.
 * }
 * else{
 *   Some work.
 *   static_strings_deallocate(test);
 * }
 * @endcode
 *
 * DON'T FORGET TO DEALLOCATE AFTER USING.\n
 *
 * \n
 * **Also a string can created this way**
 * \n
 *
 * @code
 * #include "string.h"
 *
 * uint8_t test_memory[] = "Hello Word\r\n";
 * uint16_t test_length = static_strings_strlen(test_memory);
 * static_strings_string_descriptor *test = static_strings_allocate(test_length);
 * if(test == NULL){
 *   Error Handling.
 * }
 * else{
 *   memcpy(test->string,test_memory,test_length);
 *   test->length = test_length;
 *   Some work.
 *   static_strings_deallocate(test);
 * }
 * @endcode
 *
 * DON'T FORGET TO DEALLOCATE AFTER USING.\n
 *
 * \n
 * **Split a local scope string**
 * \n
 *
 * @code
 * uint8_t split_memory[10] = "123,56,8\r\n";
 * static_strings_string_descriptor split.
 * static_strings_create_custom_string(&split,split_memory);
 * static_strings_string_descriptor token;
 * static_strings_string_splitter_set_parameters(split,',');
 * while(static_strings_string_splitter_get_next_token(&token)){
 *   HAL_UART_Transmit(&huart1,token.string,token.length,HAL_MAX_DELAY);
 * }
 * @endcode
 *
 * \n
 * **Configure quantity and size of the memory arrays**
 * \n
 *
 * Just edit these constants in static_strings.h
 *
 * @code
 * #define STATIC_STRINGS_VERY_SHORT_STRING_SIZE 50
 * #define STATIC_STRINGS_VERY_SHORT_STRING_QUANTITY 10
 *
 * #define STATIC_STRINGS_SHORT_STRING_SIZE 100
 * #define STATIC_STRINGS_SHORT_STRING_QUANTITY 6
 *
 * #define STATIC_STRINGS_MEDIUM_STRING_SIZE 200
 * #define STATIC_STRINGS_MEDIUM_STRING_QUANTITY 2
 *
 * #define STATIC_STRINGS_LONG_STRING_SIZE 500
 * #define STATIC_STRINGS_LONG_STRING_QUANTITY 1
 *
 * #define STATIC_STRINGS_VERY_LONG_STRING_SIZE 1000
 * #define STATIC_STRINGS_VERY_LONG_STRING_QUANTITY 1
 * @endcode
 *
 */

/** \file static_strings.h
 * \brief Strings allocation with static memory.
 */

#ifndef __STATIC_STRINGS_H
#define __STATIC_STRINGS_H

#include "stm32f1xx_hal.h"
#include "string.h"

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
#define STATIC_STRINGS_LONG_STRING_QUANTITY 1

#define STATIC_STRINGS_VERY_LONG_STRING_SIZE 1000
#define STATIC_STRINGS_VERY_LONG_STRING_QUANTITY 1
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
#define STATIC_STRINGS_ERROR_CODE_NO_MEMORY_AVAILABLE 0
#define STATIC_STRINGS_ERROR_CODE_INVALID_STRING 1
#define STATIC_STRINGS_ERROR_CODE_STRING_TOO_LONG 2

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

/** void static_strings_init()
 * \brief Link the descriptors with the arrays and initialize the status as deallocated.
 */
void static_strings_init();

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

/** void static_strings_string_splitter_set_parameters(static_strings_string_descriptor *string_descriptor,uint8_t delimiter)
 * \brief Bind the provided string descriptor with the next token data.
 * Can be placed in a while condition as it returns 1 if success or 0 if no token available and retrieves the token in the string_descriptor parameter.
 * If no delimiter the whole string is taken as token.
 * \param string_descriptor A pointer to a string descriptor that will contain the token.
 * \return 1 if success or 0 if no token is available.
 */
int static_strings_string_splitter_get_next_token(static_strings_string_descriptor *string_descriptor);

#endif
