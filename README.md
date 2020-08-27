 ## **Features:**

 - Developed for the STM32F103.
 - Global scope strings.
 - No dynamic memory allocation.
 - Customizable quantity and length of string types.
 - Create custom string function to create local scope strings.
 - String length function.
 - String can be \\0 terminated and \\r\\n terminated.
 - String split function.
 - Fast string creation with save.
 - Low level string creation with allocate.
 - Reusable memory with deallocate.
 - is_line function.
 - String split.
 
 # **GETTING STARTED**
 
 ## **Suggested names**
 
 ```C
 static_strings_string_descriptor string_name;
 uint8_t string_name_memory[];
 ```
 
 ## **Creating a string**
 
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
 
 DON'T FORGET TO DEALLOCATE AFTER USING.\n
 
 ## **Also a string can created this way**
 
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
 
 DON'T FORGET TO DEALLOCATE AFTER USING.\n
 
 ## **Split a local scope string**
 
 ```C
 uint8_t split_memory[10] = "123,56,8\r\n";
 static_strings_string_descriptor split.
 static_strings_create_custom_string(&split,split_memory);
 static_strings_string_descriptor token;
 static_strings_string_splitter_set_parameters(split,',');
 while(static_strings_string_splitter_get_next_token(&token)){
   HAL_UART_Transmit(&huart1,token.string,token.length,HAL_MAX_DELAY);
 }
 ```
