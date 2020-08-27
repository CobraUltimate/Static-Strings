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

int static_strings_string_splitter_get_next_token(static_strings_string_descriptor *string_descriptor){
	if(static_strings_string_splitter.next_token_start == static_strings_string_splitter.string_descriptor->string + static_strings_string_splitter.string_descriptor->length){
		return 0;
	}
	uint8_t *current_position = static_strings_string_splitter.next_token_start;
	while(*current_position++ != static_strings_string_splitter.delimiter && current_position < static_strings_string_splitter.string_descriptor->string + static_strings_string_splitter.string_descriptor->length);
	string_descriptor->string = static_strings_string_splitter.next_token_start;
	if(current_position == static_strings_string_splitter.string_descriptor->string + static_strings_string_splitter.string_descriptor->length){
		string_descriptor->length = current_position - static_strings_string_splitter.next_token_start;
	}
	else{
		string_descriptor->length = current_position - static_strings_string_splitter.next_token_start - 1;
	}
	string_descriptor->type = STATIC_STRINGS_STRING_TYPE_CUSTOM;
	string_descriptor->status = STATIC_STRINGS_STRING_STATUS_CONSTANT;
	static_strings_string_splitter.next_token_start = current_position;
	return 1;
}
