Static Strings {#mainpage}
============

## Features:

 - Developed for the STM32F103.
 - Global scope strings.
 - No dynamic memory allocation.
 - Customizable quantity and size of string types.
 - Create custom string function to create local scope strings.
 - String length function.
 - String can be \\0 terminated and \\r\\n terminated.
 - String split function.
 - Fast string creation with save.
 - Low level string creation with allocate.
 - Reusable memory with deallocate.
 - is_line function.
 - Substring, concatenate, concatenate and clean, concatenate all.
 - Contains string, contains char and compare function.
 - Transforms integers and floats to strings
 - Get string maximum length.

 # Getting Started

 ## Suggested names

 ```C
 static_strings_string_descriptor string_name;
 uint8_t string_name_memory[];
 ```

 ## First of all initialize the library

 ```C
 static_strings_init();
 ```

 ## Creating a string

 ```C
 uint8_t test_memory[] = "Hello Word\r\n";
 static_strings_string_descriptor *test = static_strings_save(test_memory);
 if(test == NULL){
   Error Handling.
 }
 else{
   Some work.
   static_strings_deallocate(test);
 }
 ```

 DON'T FORGET TO DEALLOCATE AFTER USING.

 ## Also a string can created this way

 ```C
 #include "string.h"
 
 uint8_t test_memory[] = "Hello Word\r\n";
 uint16_t test_length = static_strings_strlen(test_memory);
 static_strings_string_descriptor *test = static_strings_allocate(test_length);
 if(test == NULL){
   Error Handling.
 }
 else{
   memcpy(test->string,test_memory,test_length);
   test->length = test_length;
   Some work.
   static_strings_deallocate(test);
 }
 ```

 DON'T FORGET TO DEALLOCATE AFTER USING.

 ## Split a local scope string

 ```C
 uint8_t split_memory[10] = "123,56,8\r\n";
 static_strings_string_descriptor split.
 static_strings_create_custom_string(&split,split_memory);
 static_strings_string_descriptor *token;
 static_strings_string_splitter_set_parameters(split,',');
 while(static_strings_string_splitter_get_next_token(&token)){
   HAL_UART_Transmit(&huart1,token->string,token->length,HAL_MAX_DELAY);
 }
 ```

 ## Getting a substring

 ```C
 uint8_t custom[10] = "123,56,89\0";
 static_strings_create_custom_string(string_descriptor,custom);
 static_strings_string_descriptor *substring = static_strings_substring(string_descriptor,2,8);
 if(substring != NULL){
   HAL_UART_Transmit(&huart1,substring->string,substring->length,HAL_MAX_DELAY);
   static_strings_deallocate(substring);
 }
 ```

 ## Concatenate two strings and search for a substring and a character in the result

 ```C
 uint8_t concatenate_at_memory[] = "Hello \0";
 static_strings_string_descriptor concatenate_at;
 static_strings_create_custom_string(&concatenate_at,concatenate_at_memory);
 uint8_t concatenate_memory[] = "World\r\n";
 static_strings_string_descriptor concatenate;
 static_strings_create_custom_string(&concatenate,concatenate_memory);
 static_strings_string_descriptor *concatenated;
 concatenated = static_strings_concatenate(&concatenate_at,&concatenate);
 if (concatenated != NULL) {
   HAL_UART_Transmit(&huart1,concatenated->string,concatenated->length,HAL_MAX_DELAY);
   if(static_strings_contains_string(concatenated,&concatenate_at)){
     HAL_UART_Transmit(&huart1,(uint8_t *)"1\r\n",3,HAL_MAX_DELAY);
   }
   else{
     HAL_UART_Transmit(&huart1,(uint8_t *)"0\r\n",3,HAL_MAX_DELAY);
   }
   if(static_strings_contains_string(concatenated,'W')){
     HAL_UART_Transmit(&huart1,(uint8_t *)"1\r\n",3,HAL_MAX_DELAY);
   }
   else{
     HAL_UART_Transmit(&huart1,(uint8_t *)"0\r\n",3,HAL_MAX_DELAY);
   }
   static_strings_deallocate(concatenated);
 }
 ```

 ## Compare two equals and non equals strings

 ```C
 uint8_t equal_a_memory[] = "Hall\0";
 static_strings_string_descriptor equal_a;
 uint8_t equal_b_memory[] = "Hall\0";
 static_strings_string_descriptor equal_b;
 uint8_t non_equal_memory[] = "oil\0";
 static_strings_string_descriptor non_equal;
 static_strings_create_custom_string(&equal_a,equal_a_memory);
 static_strings_create_custom_string(&equal_b,equal_b_memory);
 static_strings_create_custom_string(&non_equal,non_equal_memory);
 if(static_strings_compare(&equal_a,&equal_b)){
   HAL_UART_Transmit(&huart1,(uint8_t *)"1\r\n",3,HAL_MAX_DELAY);
 }
 else{
   HAL_UART_Transmit(&huart1,(uint8_t *)"0\r\n",3,HAL_MAX_DELAY);
 }
 if(static_strings_compare(&equal_a,&non_equal)){
   HAL_UART_Transmit(&huart1,(uint8_t *)"1\r\n",3,HAL_MAX_DELAY);
 }
 else{
   HAL_UART_Transmit(&huart1,(uint8_t *)"0\r\n",3,HAL_MAX_DELAY);
 }
 ```

 ## Transform a integer and a float to a string
 ```C
 static_strings_string_descriptor *var_string;
 uint8_t uint8 = 200;
 var_string = static_strings_uint8_to_string(uint8);
 if(var_string != NULL){
   HAL_UART_Transmit(&huart1,var_string->string,var_string->length,HAL_MAX_DELAY);
   static_strings_deallocate(var_string);
 }
 
 float float_number = 19.60232;
 var_string = static_strings_float_to_string(float_number);
 if(var_string != NULL){
   HAL_UART_Transmit(&huart1,var_string->string,var_string->length,HAL_MAX_DELAY);
   static_strings_deallocate(var_string);
 }
 ```

## Copy, move and clone a string

 ```C
static_strings_string_descriptor *copy_test_source_string = static_strings_save((uint8_t *)"I am a copy test\r\n");
    if(copy_test_source_string != NULL){
        static_strings_string_descriptor *copy_test_target_string = static_strings_allocate(100);
        if(static_strings_copy(copy_test_target_string,copy_test_source_string,0) != NULL){
            HAL_UART_Transmit(&huart1,copy_test_target_string->string,copy_test_target_string->length,HAL_MAX_DELAY);
            static_strings_deallocate(copy_test_source_string);
            static_strings_deallocate(copy_test_target_string);
        }
    }
}

static_strings_string_descriptor *move_test_source_string = static_strings_save((uint8_t *)"I am a move test\r\n");
if(copy_test_source_string != NULL){
    static_strings_string_descriptor *move_test_target_string = static_strings_allocate(100);
    *move_test_target_string->string = '.';
    if(static_strings_move(move_test_target_string,move_test_source_string,1) != NULL){
        HAL_UART_Transmit(&huart1,move_test_target_string->string,move_test_target_string->length,HAL_MAX_DELAY);
        static_strings_deallocate(move_test_source_string);
    }
}

static_strings_string_descriptor *clone_test_source_string = static_strings_save((uint8_t *)"I am a clone test\r\n");
if(copy_test_source_string != NULL){
    static_strings_string_descriptor *clone_test_target_string = static_strings_clone(clone_test_source_string);
    if(clone_test_target_string != NULL){
        HAL_UART_Transmit(&huart1,clone_test_target_string->string,clone_test_target_string->length,HAL_MAX_DELAY);
        static_strings_deallocate(clone_test_source_string);
        static_strings_deallocate(clone_test_target_string);
    }
}
 ```

## Concatenate and clean two strings

 ```C
static_strings_string_descriptor *concatenate_at = static_strings_save((uint8_t *)"I am a ");
static_strings_string_descriptor *concatenate = static_strings_save((uint8_t *)"concatenate test\r\n");
if(concatenate_at != NULL && concatenate != NULL){
	static_strings_string_descriptor *concatenated_string = static_strings_concatenate_and_clean(concatenate_at,concatenate);
	if(concatenated_string != NULL){
    	HAL_UART_Transmit(&huart1,concatenated_string->string,concatenated_string->length,HAL_MAX_DELAY);
		static_strings_deallocate(concatenate);
		static_strings_deallocate(concatenated_string);
    }
}
 ```

## Concatenate multiple strings

 ```C
static_strings_string_descriptor *one = static_strings_save((uint8_t *)"I am a ");
static_strings_string_descriptor *two = static_strings_save((uint8_t *)"concatenate all ");
static_strings_string_descriptor *three = static_strings_save((uint8_t *)"test\r\n");
if(one != NULL && two != NULL && three != NULL){
	static_strings_string_descriptor *concatenated_string = static_strings_concatenate_all(3,one,two,three);
	if(concatenated_string != NULL){
    	HAL_UART_Transmit(&huart1,concatenated_string->string,concatenated_string->length,HAL_MAX_DELAY);
		static_strings_deallocate(one);
        static_strings_deallocate(two);
        static_strings_deallocate(three);
		static_strings_deallocate(concatenated_string);
    }
}
 ```

 ## Configure quantity and size of the memory arrays

 Just edit these constants in static_strings.h

 ```C
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
 ```
