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

int static_strings_get_string_max_length(static_strings_string_descriptor *string){
	if(string->type == STATIC_STRINGS_STRING_TYPE_CUSTOM){
		return string->length;
	}
	else{
		switch(string->type){
			case STATIC_STRINGS_STRING_TYPE_VERY_SHORT:
				return STATIC_STRINGS_VERY_SHORT_STRING_SIZE;
				break;
			case STATIC_STRINGS_STRING_TYPE_SHORT:
				return STATIC_STRINGS_SHORT_STRING_SIZE;
				break;
			case STATIC_STRINGS_STRING_TYPE_MEDIUM:
				return STATIC_STRINGS_MEDIUM_STRING_SIZE;
				break;
			case STATIC_STRINGS_STRING_TYPE_LONG:
				return STATIC_STRINGS_LONG_STRING_SIZE;
				break;
			case STATIC_STRINGS_STRING_TYPE_VERY_LONG:
				return STATIC_STRINGS_VERY_LONG_STRING_SIZE;
				break;
		}
	}
	return 0;
}

static_strings_string_descriptor *static_strings_copy(static_strings_string_descriptor *copy_to,static_strings_string_descriptor *copy_from,uint16_t copy_to_offset){
	if(copy_to == NULL || copy_from == NULL){
		return NULL;
	}
	if(static_strings_get_string_max_length(copy_to) <= copy_from->length + copy_to_offset){
		static_strings_error_code = STATIC_STRINGS_ERROR_CODE_STRING_OVERFLOW;
		return NULL;
	}
	memcpy(copy_to->string + copy_to_offset,copy_from->string,copy_from->length);
	copy_to->length = copy_from->length + copy_to_offset;
	return copy_to;
}

static_strings_string_descriptor *static_strings_move(static_strings_string_descriptor *move_to,static_strings_string_descriptor *move_from,uint16_t move_to_offset){
	if(static_strings_copy(move_to,move_from,move_to_offset) == NULL){
		return NULL;
	}
	static_strings_deallocate(move_from);
	return move_to;
}

static_strings_string_descriptor *static_strings_clone(static_strings_string_descriptor *clone_from){
	if(clone_from == NULL){
		return NULL;
	}
	static_strings_string_descriptor *cloned_string = static_strings_allocate(clone_from->length);
	if(cloned_string == NULL){
		return NULL;
	}
	memcpy(cloned_string->string,clone_from->string,clone_from->length);
	cloned_string->length = clone_from->length;
	return cloned_string;
}

static_strings_string_descriptor *static_strings_allocate(uint16_t string_size){
	int i;
	if(string_size <= STATIC_STRINGS_VERY_SHORT_STRING_SIZE){
		for(i = 0; i < STATIC_STRINGS_VERY_SHORT_STRING_QUANTITY;i++){
			if(static_strings_very_short_strings_descriptors[i].status == STATIC_STRINGS_STRING_STATUS_DEALLOCATED){
				static_strings_very_short_strings_descriptors[i].status = STATIC_STRINGS_STRING_STATUS_ALLOCATED;
				static_strings_very_short_strings_descriptors[i].length = 0;
				memset(static_strings_very_short_strings_descriptors[i].string,0,STATIC_STRINGS_VERY_SHORT_STRING_SIZE);
				return &static_strings_very_short_strings_descriptors[i];
			}
		}
	}
	if(string_size <= STATIC_STRINGS_SHORT_STRING_SIZE){
		for(i = 0; i < STATIC_STRINGS_SHORT_STRING_QUANTITY;i++){
			if(static_strings_short_strings_descriptors[i].status == STATIC_STRINGS_STRING_STATUS_DEALLOCATED){
				static_strings_short_strings_descriptors[i].status = STATIC_STRINGS_STRING_STATUS_ALLOCATED;
				static_strings_short_strings_descriptors[i].length = 0;
				memset(static_strings_short_strings_descriptors[i].string,0,STATIC_STRINGS_SHORT_STRING_SIZE);
				return &static_strings_short_strings_descriptors[i];
			}
		}
	}
	if(string_size <= STATIC_STRINGS_MEDIUM_STRING_SIZE){
		for(i = 0; i < STATIC_STRINGS_MEDIUM_STRING_QUANTITY;i++){
			if(static_strings_medium_strings_descriptors[i].status == STATIC_STRINGS_STRING_STATUS_DEALLOCATED){
				static_strings_medium_strings_descriptors[i].status = STATIC_STRINGS_STRING_STATUS_ALLOCATED;
				static_strings_medium_strings_descriptors[i].length = 0;
				memset(static_strings_medium_strings_descriptors[i].string,0,STATIC_STRINGS_MEDIUM_STRING_SIZE);
				return &static_strings_medium_strings_descriptors[i];
			}
		}
	}
	if(string_size <= STATIC_STRINGS_LONG_STRING_SIZE){
		for(i = 0; i < STATIC_STRINGS_LONG_STRING_QUANTITY;i++){
			if(static_strings_long_strings_descriptors[i].status == STATIC_STRINGS_STRING_STATUS_DEALLOCATED){
				static_strings_long_strings_descriptors[i].status = STATIC_STRINGS_STRING_STATUS_ALLOCATED;
				static_strings_long_strings_descriptors[i].length = 0;
				memset(static_strings_long_strings_descriptors[i].string,0,STATIC_STRINGS_LONG_STRING_SIZE);
				return &static_strings_long_strings_descriptors[i];
			}
		}
	}
	if(string_size <= STATIC_STRINGS_VERY_LONG_STRING_SIZE){
		for(i = 0; i < STATIC_STRINGS_VERY_LONG_STRING_QUANTITY;i++){
			if(static_strings_very_long_strings_descriptors[i].status == STATIC_STRINGS_STRING_STATUS_DEALLOCATED){
				static_strings_very_long_strings_descriptors[i].status = STATIC_STRINGS_STRING_STATUS_ALLOCATED;
				static_strings_very_long_strings_descriptors[i].length = 0;
				memset(static_strings_very_long_strings_descriptors[i].string,0,STATIC_STRINGS_VERY_LONG_STRING_SIZE);
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
	if(string_descriptor->status != STATIC_STRINGS_STRING_STATUS_CONSTANT){
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
		if( *(string + length) == '\r' && length < STATIC_STRINGS_VERY_LONG_STRING_SIZE - 1){
			if(*(string + length + 1) == '\n'){
				length += 2;
				break;
			}
		}
		if( *(string + length) == '\0'){
			break;
		}
	}
	if(length >= STATIC_STRINGS_VERY_LONG_STRING_SIZE){
		static_strings_error_code = STATIC_STRINGS_ERROR_CODE_STRING_TOO_LONG;
		return 0;
	}
	else{
		return length;
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
		static_strings_error_code = STATIC_STRINGS_ERROR_CODE_STRING_TOO_LONG;
		return concatenated_string;
	}
	memcpy(concatenated_string->string,concatenate_at->string,concatenate_at->length);
	memcpy(concatenated_string->string + concatenate_at->length,concatenate->string,concatenate->length);
	concatenated_string->length = concatenated_string_length;
	return concatenated_string;
}

static_strings_string_descriptor *static_strings_concatenate_and_clean(static_strings_string_descriptor* concatenate_at,static_strings_string_descriptor* concatenate){
	static_strings_string_descriptor* concatenated_string = static_strings_concatenate(concatenate_at,concatenate);
	if(concatenated_string == NULL){
		return concatenated_string;
	}
	static_strings_deallocate(concatenate_at);
	return concatenated_string;
}

static_strings_string_descriptor *static_strings_concatenate_and_clean_both(static_strings_string_descriptor* concatenate_at,static_strings_string_descriptor* concatenate){
	static_strings_string_descriptor* concatenated_string = static_strings_concatenate(concatenate_at,concatenate);
	if(concatenated_string == NULL){
		return concatenated_string;
	}
	static_strings_deallocate(concatenate_at);
	static_strings_deallocate(concatenate);
	return concatenated_string;
}

static_strings_string_descriptor *static_strings_concatenate_all(uint16_t arguments_quantity,...){
	va_list arguments_list;
	int i;
	va_start(arguments_list, arguments_quantity);
	static_strings_string_descriptor *next_string_to_concatenate;
	static_strings_string_descriptor *concatenated_string = static_strings_allocate(0);
	concatenated_string->length = 0;
	for (i = 0; i < arguments_quantity;i++){
		next_string_to_concatenate = va_arg(arguments_list, static_strings_string_descriptor *);
		concatenated_string = static_strings_concatenate_and_clean(concatenated_string,next_string_to_concatenate);
	}
	va_end(arguments_list);
	return concatenated_string;
}

static_strings_string_descriptor *static_strings_concatenate_and_clean_all(uint16_t arguments_quantity,...){
	va_list arguments_list;
	int i;
	va_start(arguments_list, arguments_quantity);
	static_strings_string_descriptor *next_string_to_concatenate;
	static_strings_string_descriptor *concatenated_string = static_strings_allocate(0);
	concatenated_string->length = 0;
	for (i = 0; i < arguments_quantity;i++){
		next_string_to_concatenate = va_arg(arguments_list, static_strings_string_descriptor *);
		concatenated_string = static_strings_concatenate_and_clean(concatenated_string,next_string_to_concatenate);
		static_strings_deallocate(next_string_to_concatenate);
	}
	va_end(arguments_list);
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
	int i;
	for(i = 0;i < compare_string_one->length;i++){
		if(*(compare_string_one->string + i) != *(compare_string_two->string + i)){
			return 0;
		}
	}
	return 1;
}

static_strings_string_descriptor *static_strings_uint8_to_string(uint8_t uint8){
	uint8_t uint8_temp_string[50];
	sprintf((char *)uint8_temp_string,"%" PRIu8,uint8);
	uint16_t uint8_string_length = static_strings_strlen(uint8_temp_string);
	static_strings_string_descriptor *uint8_string = static_strings_allocate(uint8_string_length);
	if(uint8_string == NULL){
		return uint8_string;
	}
	memcpy(uint8_string->string,uint8_temp_string,uint8_string_length);
	uint8_string->length = uint8_string_length;
	return uint8_string;
}

static_strings_string_descriptor *static_strings_uint16_to_string(uint16_t uint16){
	uint8_t uint16_temp_string[50];
	sprintf((char *)uint16_temp_string,"%" PRIu16,uint16);
	uint16_t uint16_string_length = static_strings_strlen(uint16_temp_string);
	static_strings_string_descriptor *uint16_string = static_strings_allocate(uint16_string_length);
	if(uint16_string == NULL){
		return uint16_string;
	}
	memcpy(uint16_string->string,uint16_temp_string,uint16_string_length);
	uint16_string->length = uint16_string_length;
	return uint16_string;
}

static_strings_string_descriptor *static_strings_uint32_to_string(uint32_t uint32){
	uint8_t uint32_temp_string[50];
	sprintf((char *)uint32_temp_string,"%" PRIu32,uint32);
	uint16_t uint32_string_length = static_strings_strlen(uint32_temp_string);
	static_strings_string_descriptor *uint32_string = static_strings_allocate(uint32_string_length);
	if(uint32_string == NULL){
		return uint32_string;
	}
	memcpy(uint32_string->string,uint32_temp_string,uint32_string_length);
	uint32_string->length = uint32_string_length;
	return uint32_string;
}

static_strings_string_descriptor *static_strings_int8_to_string(int8_t int8){
	uint8_t int8_temp_string[50];
	sprintf((char *)int8_temp_string,"%" PRId8,int8);
	uint16_t int8_string_length = static_strings_strlen(int8_temp_string);
	static_strings_string_descriptor *int8_string = static_strings_allocate(int8_string_length);
	if(int8_string == NULL){
		return int8_string;
	}
	memcpy(int8_string->string,int8_temp_string,int8_string_length);
	int8_string->length = int8_string_length;
	return int8_string;
}

static_strings_string_descriptor *static_strings_int16_to_string(int16_t int16){
	uint8_t int16_temp_string[50];
	sprintf((char *)int16_temp_string,"%" PRId16,int16);
	int16_t int16_string_length = static_strings_strlen(int16_temp_string);
	static_strings_string_descriptor *int16_string = static_strings_allocate(int16_string_length);
	if(int16_string == NULL){
		return int16_string;
	}
	memcpy(int16_string->string,int16_temp_string,int16_string_length);
	int16_string->length = int16_string_length;
	return int16_string;
}

static_strings_string_descriptor *static_strings_int32_to_string(int32_t int32){
	uint8_t int32_temp_string[50];
	sprintf((char *)int32_temp_string,"%" PRId32,int32);
	int16_t int32_string_length = static_strings_strlen(int32_temp_string);
	static_strings_string_descriptor *int32_string = static_strings_allocate(int32_string_length);
	if(int32_string == NULL){
		return int32_string;
	}
	memcpy(int32_string->string,int32_temp_string,int32_string_length);
	int32_string->length = int32_string_length;
	return int32_string;
}

static_strings_string_descriptor *static_strings_float_to_string(float float_arg){
	uint8_t float_temp_string[50];
	sprintf((char *)float_temp_string,"%f",float_arg);
	int16_t float_string_length = static_strings_strlen(float_temp_string);
	static_strings_string_descriptor *float_string = static_strings_allocate(float_string_length);
	if(float_string == NULL){
		return float_string;
	}
	memcpy(float_string->string,float_temp_string,float_string_length);
	float_string->length = float_string_length;
	return float_string;
}

static_strings_string_descriptor *static_strings_double_to_string(double double_arg){
	uint8_t double_temp_string[50];
	sprintf((char *)double_temp_string,"%lf",double_arg);
	int16_t double_string_length = static_strings_strlen(double_temp_string);
	static_strings_string_descriptor *double_string = static_strings_allocate(double_string_length);
	if(double_string == NULL){
		return double_string;
	}
	memcpy(double_string->string,double_temp_string,double_string_length);
	double_string->length = double_string_length;
	return double_string;
}
