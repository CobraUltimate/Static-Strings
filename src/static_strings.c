/** \file static_strings.c
 * \brief Strings allocation with static memory.
 */

#include "static_strings.h"

static_strings_string_splitter_parameters static_strings_string_splitter = {NULL,'\0'};

void static_strings_init(){
	int i;
	for(i = 0; i < STATIC_STRINGS_VERY_SHORT_STRING_QUANTITY;i++){
		static_strings_very_short_strings_descriptors[i].string = static_strings_very_short_string_memory[i];
		static_strings_very_short_strings_descriptors[i].type = STATIC_STRINGS_STRING_TYPE_VERY_SHORT;
		static_strings_very_short_strings_descriptors[i].status = STATIC_STRINGS_STRING_STATUS_DEALLOCATED;
	}
	for(i = 0; i < STATIC_STRINGS_SHORT_STRING_QUANTITY;i++){
		static_strings_short_strings_descriptors[i].string = static_strings_short_string_memory[i];
		static_strings_short_strings_descriptors[i].type = STATIC_STRINGS_STRING_TYPE_SHORT;
		static_strings_short_strings_descriptors[i].status = STATIC_STRINGS_STRING_STATUS_DEALLOCATED;
	}
	for(i = 0; i < STATIC_STRINGS_MEDIUM_STRING_QUANTITY;i++){
		static_strings_medium_strings_descriptors[i].string = static_strings_medium_string_memory[i];
		static_strings_medium_strings_descriptors[i].type = STATIC_STRINGS_STRING_TYPE_MEDIUM;
		static_strings_medium_strings_descriptors[i].status = STATIC_STRINGS_STRING_STATUS_DEALLOCATED;
	}
	for(i = 0; i < STATIC_STRINGS_LONG_STRING_QUANTITY;i++){
		static_strings_long_strings_descriptors[i].string = static_strings_long_string_memory[i];
		static_strings_long_strings_descriptors[i].type = STATIC_STRINGS_STRING_TYPE_LONG;
		static_strings_long_strings_descriptors[i].status = STATIC_STRINGS_STRING_STATUS_DEALLOCATED;
	}
	for(i = 0; i < STATIC_STRINGS_VERY_LONG_STRING_QUANTITY;i++){
		static_strings_very_long_strings_descriptors[i].string = static_strings_very_long_string_memory[i];
		static_strings_very_long_strings_descriptors[i].type = STATIC_STRINGS_STRING_TYPE_VERY_LONG;
		static_strings_very_long_strings_descriptors[i].status = STATIC_STRINGS_STRING_STATUS_DEALLOCATED;
	}
}

static_strings_string_descriptor *static_strings_allocate(uint16_t string_size){
	int i;
	if(string_size <= STATIC_STRINGS_VERY_SHORT_STRING_SIZE){
		for(i = 0; i < STATIC_STRINGS_VERY_SHORT_STRING_QUANTITY;i++){
			if(static_strings_very_short_strings_descriptors[i].status == STATIC_STRINGS_STRING_STATUS_DEALLOCATED){
				static_strings_very_short_strings_descriptors[i].status = STATIC_STRINGS_STRING_STATUS_ALLOCATED;
				return &static_strings_very_short_strings_descriptors[i];
			}
		}
	}
	if(string_size <= STATIC_STRINGS_SHORT_STRING_SIZE){
		for(i = 0; i < STATIC_STRINGS_SHORT_STRING_QUANTITY;i++){
			if(static_strings_short_strings_descriptors[i].status == STATIC_STRINGS_STRING_STATUS_DEALLOCATED){
				static_strings_short_strings_descriptors[i].status = STATIC_STRINGS_STRING_STATUS_ALLOCATED;
				return &static_strings_short_strings_descriptors[i];
			}
		}
	}
	if(string_size <= STATIC_STRINGS_MEDIUM_STRING_SIZE){
		for(i = 0; i < STATIC_STRINGS_MEDIUM_STRING_QUANTITY;i++){
			if(static_strings_medium_strings_descriptors[i].status == STATIC_STRINGS_STRING_STATUS_DEALLOCATED){
				static_strings_medium_strings_descriptors[i].status = STATIC_STRINGS_STRING_STATUS_ALLOCATED;
				return &static_strings_medium_strings_descriptors[i];
			}
		}
	}
	if(string_size <= STATIC_STRINGS_LONG_STRING_SIZE){
		for(i = 0; i < STATIC_STRINGS_LONG_STRING_QUANTITY;i++){
			if(static_strings_long_strings_descriptors[i].status == STATIC_STRINGS_STRING_STATUS_DEALLOCATED){
				static_strings_long_strings_descriptors[i].status = STATIC_STRINGS_STRING_STATUS_ALLOCATED;
				return &static_strings_long_strings_descriptors[i];
			}
		}
	}
	if(string_size <= STATIC_STRINGS_VERY_LONG_STRING_SIZE){
		for(i = 0; i < STATIC_STRINGS_VERY_LONG_STRING_QUANTITY;i++){
			if(static_strings_very_long_strings_descriptors[i].status == STATIC_STRINGS_STRING_STATUS_DEALLOCATED){
				static_strings_very_long_strings_descriptors[i].status = STATIC_STRINGS_STRING_STATUS_ALLOCATED;
				return &static_strings_very_long_strings_descriptors[i];
			}
		}
	}
	if(string_size <= STATIC_STRINGS_VERY_LONG_STRING_SIZE){
		static_strings_error_code = STATIC_STRINGS_ERROR_CODE_NO_MEMORY_AVAILABLE;
	}
	else{
		static_strings_error_code = STATIC_STRINGS_ERROR_CODE_STRING_TOO_LONG;
	}
	return (static_strings_string_descriptor *)NULL;
}

static_strings_string_descriptor *static_strings_save(uint8_t *string){
	uint16_t string_length = static_strings_strlen(string);
	if(string_length == 0){
		return (static_strings_string_descriptor *)NULL;
	}
	static_strings_string_descriptor *descriptor = static_strings_allocate(string_length);
	if(descriptor == NULL){
		return descriptor;
	}
	memcpy(descriptor->string,string,string_length);
	descriptor->length = string_length;
	return descriptor;
}

int static_strings_create_custom_string(static_strings_string_descriptor *string_descriptor,uint8_t *string){
	string_descriptor->type = STATIC_STRINGS_STRING_TYPE_CUSTOM;
	string_descriptor->status = STATIC_STRINGS_STRING_STATUS_CONSTANT;
	string_descriptor->string = string;
	string_descriptor->length = static_strings_strlen(string_descriptor->string);
	return string_descriptor->length;
}

void static_strings_deallocate(static_strings_string_descriptor *string_descriptor){
	if(string_descriptor->type != STATIC_STRINGS_STRING_STATUS_CONSTANT){
		string_descriptor->status = STATIC_STRINGS_STRING_STATUS_DEALLOCATED;
	}
}

int static_strings_is_line(static_strings_string_descriptor *string_descriptor){
	if( *(string_descriptor->string + string_descriptor->length - 2) == '\r' || *(string_descriptor->string + string_descriptor->length - 1) == '\n'){
		return 1;
	}
	return 0;
}

uint16_t static_strings_strlen(uint8_t *string){
	uint16_t length;
	for(length = 0;length < STATIC_STRINGS_VERY_LONG_STRING_SIZE;length++){
		if( *(string + length) == '\r'){
			break;
		}
		if( *(string + length) == '\0'){
			return length;
		}
	}
	if(length >= 999){
		static_strings_error_code = STATIC_STRINGS_ERROR_CODE_INVALID_STRING;
		return 0;
	}
	else{
		if(*(string + length + 1) != '\n'){
			*(string + length + 1) = '\n';
		}
		return length + 2;
	}
}

void static_strings_string_splitter_set_parameters(static_strings_string_descriptor *string_descriptor,uint8_t delimiter){
	static_strings_string_splitter.string_descriptor = string_descriptor;
	static_strings_string_splitter.next_token_start = string_descriptor->string;
	static_strings_string_splitter.delimiter = delimiter;
}

int static_strings_string_splitter_get_next_token(static_strings_string_descriptor **string_descriptor){
	if(static_strings_string_splitter.next_token_start == static_strings_string_splitter.string_descriptor->string + static_strings_string_splitter.string_descriptor->length){
		return 0;
	}
	uint8_t *current_position = static_strings_string_splitter.next_token_start;
	while(*current_position++ != static_strings_string_splitter.delimiter && current_position < static_strings_string_splitter.string_descriptor->string + static_strings_string_splitter.string_descriptor->length);

	int token_length;
	if(current_position == static_strings_string_splitter.string_descriptor->string + static_strings_string_splitter.string_descriptor->length){
		token_length = current_position - static_strings_string_splitter.next_token_start;
	}
	else{
		token_length = current_position - static_strings_string_splitter.next_token_start - 1;
	}
	*string_descriptor = static_strings_allocate(token_length);
	memcpy((*string_descriptor)->string,static_strings_string_splitter.next_token_start,token_length);
	(*string_descriptor)->length = token_length;
	static_strings_string_splitter.next_token_start = current_position;
	return 1;
}

static_strings_string_descriptor *static_strings_substring(static_strings_string_descriptor* string,uint16_t start_index,uint16_t finish_index){
	if(start_index < 0 || start_index >= string->length){
		static_strings_error_code = STATIC_STRINGS_ERROR_CODE_SUBSTRING_START_INDEX_OUT_OF_RANGE;
		return NULL;
	}
	if(finish_index <= 0 || finish_index > string->length){
		static_strings_error_code = STATIC_STRINGS_ERROR_CODE_SUBSTRING_FINISH_INDEX_OUT_OF_RANGE;
		return NULL;
	}
	uint16_t substring_length = finish_index - start_index;
	static_strings_string_descriptor *substring = static_strings_allocate(substring_length);
	if(substring == NULL){
		return substring;
	}
	memcpy(substring->string,string->string + start_index,substring_length);
	substring->length = substring_length;
	return substring;
}

static_strings_string_descriptor *static_strings_concatenate(static_strings_string_descriptor* concatenate_at,static_strings_string_descriptor* concatenate){
	int concatenated_string_length = concatenate_at->length + concatenate->length;
	static_strings_string_descriptor *concatenated_string = static_strings_allocate(concatenated_string_length);
	if(concatenated_string == NULL){
		return concatenated_string;
	}
	memcpy(concatenated_string->string,concatenate_at->string,concatenate_at->length);
	memcpy(concatenated_string->string + concatenate_at->length,concatenate->string,concatenate->length);
	concatenated_string->length = concatenated_string_length;
	return concatenated_string;
}

int static_strings_contains_string(static_strings_string_descriptor* search_in,static_strings_string_descriptor* search_for){
	if(search_in->length < search_for->length){
		return 0;
	}
	int i,j;
	int searched_string_found;
	for(i = 0;search_for->length <= search_in->length - i;i++){
		searched_string_found = 1;
		for(j = 0; j < search_for->length;j++){
			if( *(search_in->string + i + j) != *(search_for->string + j) ){
				searched_string_found = 0;
				break;
			}
		}
		if(searched_string_found){
			return 1;
		}
	}
	return 0;
}

int static_strings_contains_char(static_strings_string_descriptor* search_in,uint8_t search_for){
	int i;
	for(i = 0;i < search_in->length;i++){
		if( *(search_in->string + i) == search_for){
			return 1;
		}
	}
	return 0;
}

int static_strings_compare(static_strings_string_descriptor* compare_string_one,static_strings_string_descriptor* compare_string_two){
	if(compare_string_one->length != compare_string_two->length){
		return 0;
	}
	return static_strings_contains_string(compare_string_one,compare_string_two);
}
