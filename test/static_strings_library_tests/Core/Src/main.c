/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */
	static_strings_init();
	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_USART1_UART_Init();
	/* USER CODE BEGIN 2 */

	//test 1

	uint8_t very_long_string[700];
	uint16_t i;
	for(i = 0; i < 699; i++){
		very_long_string[i] = 'a';
	}
	very_long_string[699] = '\0';
	static_strings_string_descriptor *very_long_string_descriptor = static_strings_save(very_long_string);
	char length[6];
	sprintf(length,"%04d",very_long_string_descriptor->length);
	length[4] = '\r';
	length[5] = '\n';
	HAL_UART_Transmit(&huart1,(uint8_t *)length,6,HAL_MAX_DELAY);
	char type[3];
	type[0] = very_long_string_descriptor->type + 48;
	type[1] = '\r';
	type[2] = '\n';
	HAL_UART_Transmit(&huart1,(uint8_t *)type,3,HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart1,(uint8_t *)very_long_string_descriptor->string,very_long_string_descriptor->length,HAL_MAX_DELAY);

	static_strings_deallocate(very_long_string_descriptor);

	uint8_t test_very_short_strings[10][50] = {"rapmr\r\n","ejkxjde7wp\r\n","rmp642c8un8bcjj\r\n","5ynn4y8caurm3trzwq4j\r\n","hwcqtzcn4gc8avg4d4zi7nr9f\r\n","tgt62yw9jnugwbg3pgzax73z6uix7g\r\n","bwn8czmxkhexdiw77v4gk4xu2yqtqibv2jn\r\n","eykku6i7j36kewjbwvpd5x9viggdhreqe9amk7ub\r\n","mpjkqkrn22q4xzvpt897fwjjurgtj3vczmmhy64d8qgww\r\n","wgxfec343aaku5axbjt5w2e5cz63r9bbydqun88ukj9iwint\r\n"};
	uint8_t test_short_strings[6][100] = {"b6cwufw3yyfz4kdxmpmjbt8p5kq43m8hynkanabtjrgrc4iitx8tvdbkgima\r\n","j85npdf3rjtf8egmja2cxuqgu6z4h38ikaue7evfqytbuw5b95pjmqvnhejmjkc8c\r\n","bduzvngtikgxbm2wc4wrwq75ti4c5cvavcna7k4cur4mi56gegbfnc5jd6i484efri9ddh\r\n","44upv7qtmzngmbp7gdbfnumhx82iwpz8vtp9dd7vyq4yn56jqfj7g5pd44gxg9t5tw466u6gbum\r\n","5gpxtjyj79j438uif2ukmyj67v5hebnh45tpaxa9cc92t28nwct2hghqb7kf96vrzz9dqj6hcfqtjfyi\r\n","e7gbz5rqwhmr3bq6jfuav9hgya8fthpi4jn6yiwgd5hmv9mjke8r8eva7dbzyr2pn9wavx386u6dnj6zdkerc\r\n"};
	uint8_t test_medium_strings[2][200] = {"27wnc489rtjak6963r7c8mw4zmm7nxkhneu9wbg6nemurramx4yx6zipi2kmjh3n9hr6aci9dcku5w87ez8fkr5fnuzdk8q74ekkwgfnm3kq7dk82d24vujdpupp83rbfw5bnci7h5zx6iuzadukvc\r\n","ieckbpek2tuq837haz8cy78dpki9eav589t2bx5ffkx44kcj9tw5hwqyfqwgi5mjrww2i39jg9hz7djdddyp3b6uyy69cniwzeu8y4kgv2xmkji97dpxcfhr\r\n"};
	uint8_t test_long_string[500] = "2j97e72cutbnqwcc4rg6rvqniyravzyqj4k7ee44pwvwmi2kvdk3vmmbr7396q7uajqmukehfn7qhr9pj4k974wbiw6dxr9ckmmj4bnkd5ndxn6ia27rjyyhdnrgk2kgdrqfhkeq8jwdz9rgd6wyw52yqxz5v873j7q9gc3bwfmiv6deutkj7fvvg8m877tgtnq5a5ueqd589prwfk5ex7bjixicnhb3x9n9m5vqtpbtgzx4vvbc9jcqrpfbgxjpvawrkeyjkk7aifkfr6xjerkxz7bk6cekpqttf72788m23qaz7xncba4g8dvayzwqqyev6ie3dgyfyew2rew6nba9nte3p5\r\n";
	uint8_t test_very_long_string[1000] = "3ghgwfrwyrzzdhr2929pnvm7ht4bgvq6bii7cz7ajp98475pgbwt3tww7prn86y7e6gdhvda923y4wzu5xwex9a8ntjf243h94z848k9fhym39qrt8ypp9rcge8drmxfeb9bn5mryc738w2mdk8weyxnti2zy9a7j3w7947qhce3bvv5d8yjxxt7ncik4muju5zcqzab5vf2wvz49w3j8v23u3grci33hdxvniy7h2p2r4b4xig3j5nfnn6m2qvmw5b5hzii32mrh7ebr2tuaqgdxn8xbecjpnvpv7timpd7cpqyubdjczaftwrrum8bdtfqzp4wr8him9n3g4nc347f264jhzb7w6bmyh9gj3zwrau6czz67ybq2cdh6p7cdbyvk88u5rfh9xi3u6fgbzfnu9b9qv6kd4mxhc6t758tad8n4i396qw2v3r2th3dag8d7h837ibpdx8v8njvkg7dh9j5rqmnvktcegmtxaprhxky8f6ppwcgeei29a6z3inht7kzm9x62muqc6cijrzfqm3yvukurwge4mi5fnzb5gqbz279kbpzy484ndrc2vrczwa2zmvjvdad39vjtwqp\r\n";

	static_strings_string_descriptor *string_descriptor;

	//test 2

	string_descriptor = static_strings_save(test_very_long_string);
	sprintf(length,"%04d",string_descriptor->length);
	length[4] = '\r';
	HAL_UART_Transmit(&huart1,(uint8_t *)length,6,HAL_MAX_DELAY);
	type[0] = string_descriptor->type + 48;
	HAL_UART_Transmit(&huart1,(uint8_t *)type,3,HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart1,(uint8_t *)string_descriptor->string,string_descriptor->length,HAL_MAX_DELAY);

	//test 3

	string_descriptor = static_strings_save(test_long_string);
	sprintf(length,"%04d",string_descriptor->length);
	length[4] = '\r';
	HAL_UART_Transmit(&huart1,(uint8_t *)length,6,HAL_MAX_DELAY);
	type[0] = string_descriptor->type + 48;
	HAL_UART_Transmit(&huart1,(uint8_t *)type,3,HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart1,(uint8_t *)string_descriptor->string,string_descriptor->length,HAL_MAX_DELAY);

	//test 4,5

	for(i = 0; i < 2; i++){
		string_descriptor = static_strings_save(test_medium_strings[i]);
		sprintf(length,"%04d",string_descriptor->length);
		length[4] = '\r';
		HAL_UART_Transmit(&huart1,(uint8_t *)length,6,HAL_MAX_DELAY);
		type[0] = string_descriptor->type + 48;
		HAL_UART_Transmit(&huart1,(uint8_t *)type,3,HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart1,(uint8_t *)string_descriptor->string,string_descriptor->length,HAL_MAX_DELAY);
	}

	//test 6-11

	for(i = 0; i < 6; i++){
		string_descriptor = static_strings_save(test_short_strings[i]);
		sprintf(length,"%04d",string_descriptor->length);
		length[4] = '\r';
		HAL_UART_Transmit(&huart1,(uint8_t *)length,6,HAL_MAX_DELAY);
		type[0] = string_descriptor->type + 48;
		HAL_UART_Transmit(&huart1,(uint8_t *)type,3,HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart1,(uint8_t *)string_descriptor->string,string_descriptor->length,HAL_MAX_DELAY);
	}

	//test 12-21

	static_strings_string_descriptor *string_descriptor_deallocate = NULL;
	for(i = 0; i < 10; i++){
		string_descriptor = static_strings_save(test_very_short_strings[i]);
		if(i == 6){
			string_descriptor_deallocate = string_descriptor;
		}
		sprintf(length,"%04d",string_descriptor->length);
		length[4] = '\r';
		HAL_UART_Transmit(&huart1,(uint8_t *)length,6,HAL_MAX_DELAY);
		type[0] = string_descriptor->type + 48;
		HAL_UART_Transmit(&huart1,(uint8_t *)type,3,HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart1,(uint8_t *)string_descriptor->string,string_descriptor->length,HAL_MAX_DELAY);
	}

	//test 22

	static_strings_deallocate(string_descriptor_deallocate);
	uint8_t test_short_string[50] = "reallocate_test\r\n";
	string_descriptor = static_strings_save(test_short_string);
	sprintf(length,"%04d",string_descriptor->length);
	length[4] = '\r';
	HAL_UART_Transmit(&huart1,(uint8_t *)length,6,HAL_MAX_DELAY);
	type[0] = string_descriptor->type + 48;
	HAL_UART_Transmit(&huart1,(uint8_t *)type,3,HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart1,(uint8_t *)string_descriptor->string,string_descriptor->length,HAL_MAX_DELAY);

	//test 23

	uint8_t pointer[12];
	sprintf((char *)pointer,"%10p",string_descriptor_deallocate);
	pointer[10] = '\r';
	pointer[11] = '\n';
	HAL_UART_Transmit(&huart1,pointer,12,HAL_MAX_DELAY);

	sprintf((char *)pointer,"%10p",string_descriptor);
	pointer[10] = '\r';
	pointer[11] = '\n';
	HAL_UART_Transmit(&huart1,pointer,12,HAL_MAX_DELAY);

	uint8_t error_code_char;

	//test 24

	string_descriptor = static_strings_save((uint8_t *)"useless_string");
	while(string_descriptor != NULL){
		string_descriptor = static_strings_save((uint8_t *)"useless_string");
	}

	uint8_t no_memory_string[800];
	for(i = 0; i < 798; i++){
		no_memory_string[i] = 'a';
	}
	no_memory_string[798] = '\r';
	no_memory_string[799] = '\n';
	string_descriptor = static_strings_save(no_memory_string);
	if(string_descriptor == NULL){
		error_code_char = static_strings_error_code + 48;
	}
	else{
		error_code_char = '3';
	}
	HAL_UART_Transmit(&huart1,&error_code_char,1,HAL_MAX_DELAY);

	static_strings_init();

	//test 25

	uint8_t unallocable_invalid_string[STATIC_STRINGS_VERY_LONG_STRING_SIZE + 100];
	for(i = 0; i < STATIC_STRINGS_VERY_LONG_STRING_SIZE + 100; i++){
		unallocable_invalid_string[i] = 'a';
	}
	unallocable_invalid_string[STATIC_STRINGS_VERY_LONG_STRING_SIZE + 100 - 2] = '\r';
	unallocable_invalid_string[STATIC_STRINGS_VERY_LONG_STRING_SIZE + 100 - 1] = '\n';
	string_descriptor = static_strings_save(unallocable_invalid_string);
	if(string_descriptor == NULL){
		error_code_char = static_strings_error_code + 48;
	}
	else{
		error_code_char = '4';
	}
	HAL_UART_Transmit(&huart1,&error_code_char,1,HAL_MAX_DELAY);

	//test 26 deprecated

	uint8_t no_line_end_invalid_string[800];
	for(i = 0; i < 800; i++){
		no_line_end_invalid_string[i] = 'a';
	}
	string_descriptor = static_strings_save(no_line_end_invalid_string);
	if(string_descriptor == NULL){
		error_code_char = static_strings_error_code + 48;
	}
	else{
		error_code_char = '5';
	}
	HAL_UART_Transmit(&huart1,&error_code_char,1,HAL_MAX_DELAY);

	//test 27 deprecated

	string_descriptor = static_strings_allocate(1200);
	if(string_descriptor == NULL){
		error_code_char = static_strings_error_code + 48;
	}
	else{
		error_code_char = '6';
	}
	HAL_UART_Transmit(&huart1,&error_code_char,1,HAL_MAX_DELAY);

	//test 28

	uint8_t custom[10] = "123,56,89\0";
	static_strings_string_descriptor custom_string_descriptor;
	string_descriptor = &custom_string_descriptor;
	static_strings_create_custom_string(string_descriptor,custom);
	HAL_UART_Transmit(&huart1,string_descriptor->string,string_descriptor->length,HAL_MAX_DELAY);

	// test 29

	if(static_strings_is_line(string_descriptor)){
		HAL_UART_Transmit(&huart1,(uint8_t *)"1\r\n",3,HAL_MAX_DELAY);
	}
	else{
		HAL_UART_Transmit(&huart1,(uint8_t *)"0\r\n",3,HAL_MAX_DELAY);
	}

	// test 30

	uint8_t custom_line[10] = "123,56,8\r\n";
	static_strings_create_custom_string(string_descriptor,custom_line);

	if(static_strings_is_line(string_descriptor)){
		HAL_UART_Transmit(&huart1,(uint8_t *)"1\r\n",3,HAL_MAX_DELAY);
	}
	else{
		HAL_UART_Transmit(&huart1,(uint8_t *)"0\r\n",3,HAL_MAX_DELAY);
	}

	// reset all descriptors
	static_strings_init();

	// test 31-33

	static_strings_string_descriptor *token;
	static_strings_string_splitter_set_parameters(string_descriptor,',');
	while(static_strings_string_splitter_get_next_token(&token)){
		HAL_UART_Transmit(&huart1,token->string,token->length,HAL_MAX_DELAY);
		static_strings_deallocate(token);
	}

	// test 34

	int next_token_result = static_strings_string_splitter_get_next_token(&token);
	if(next_token_result){
		HAL_UART_Transmit(&huart1,(uint8_t *)"1\r\n",3,HAL_MAX_DELAY);
	}
	else{
		HAL_UART_Transmit(&huart1,(uint8_t *)"0\r\n",3,HAL_MAX_DELAY);
	}

	// test 35

	static_strings_create_custom_string(string_descriptor,custom);
	static_strings_string_descriptor *substring = static_strings_substring(string_descriptor,2,8);
	if(substring != NULL){
		HAL_UART_Transmit(&huart1,substring->string,substring->length,HAL_MAX_DELAY);
		static_strings_deallocate(substring);
	}

	// test 36

	substring = static_strings_substring(string_descriptor,0,string_descriptor->length);
	if(substring != NULL){
		HAL_UART_Transmit(&huart1,substring->string,substring->length,HAL_MAX_DELAY);
		static_strings_deallocate(substring);
	}

	// test 37

	substring = static_strings_substring(string_descriptor,0,12);
	if (substring != NULL) {
		HAL_UART_Transmit(&huart1,(uint8_t *)"1\r\n",3,HAL_MAX_DELAY);
		static_strings_deallocate(substring);
	}
	else{
		HAL_UART_Transmit(&huart1,(uint8_t *)"0\r\n",3,HAL_MAX_DELAY);
	}

	// test 38

	substring = static_strings_substring(string_descriptor,-2,5);
	if (substring != NULL){
		HAL_UART_Transmit(&huart1,(uint8_t *)"1\r\n",3,HAL_MAX_DELAY);
		static_strings_deallocate(substring);
	}
	else{
		HAL_UART_Transmit(&huart1,(uint8_t *)"0\r\n",3,HAL_MAX_DELAY);
	}

	// test 39

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
		static_strings_deallocate(concatenated);
	}

	// test 40

	if(static_strings_contains_string(concatenated,&concatenate_at)){
		HAL_UART_Transmit(&huart1,(uint8_t *)"1\r\n",3,HAL_MAX_DELAY);
	}
	else{
		HAL_UART_Transmit(&huart1,(uint8_t *)"0\r\n",3,HAL_MAX_DELAY);
	}

	// test 41

	if(static_strings_contains_string(concatenated,&concatenate)){
		HAL_UART_Transmit(&huart1,(uint8_t *)"1\r\n",3,HAL_MAX_DELAY);
	}
	else{
		HAL_UART_Transmit(&huart1,(uint8_t *)"0\r\n",3,HAL_MAX_DELAY);
	}

	// test 42

	uint8_t non_contained_memory[] = "Hill\0";
	static_strings_string_descriptor non_contained;
	static_strings_create_custom_string(&non_contained,non_contained_memory);
	if(static_strings_contains_string(concatenated,&non_contained)){
		HAL_UART_Transmit(&huart1,(uint8_t *)"1\r\n",3,HAL_MAX_DELAY);
	}
	else{
		HAL_UART_Transmit(&huart1,(uint8_t *)"0\r\n",3,HAL_MAX_DELAY);
	}

	// test 43

	if(static_strings_contains_char(concatenated,'W')){
		HAL_UART_Transmit(&huart1,(uint8_t *)"1\r\n",3,HAL_MAX_DELAY);
	}
	else{
		HAL_UART_Transmit(&huart1,(uint8_t *)"0\r\n",3,HAL_MAX_DELAY);
	}

	// test 44

	if(static_strings_contains_char(concatenated,'e')){
		HAL_UART_Transmit(&huart1,(uint8_t *)"1\r\n",3,HAL_MAX_DELAY);
	}
	else{
		HAL_UART_Transmit(&huart1,(uint8_t *)"0\r\n",3,HAL_MAX_DELAY);
	}

	// test 45

	if(static_strings_contains_char(concatenated,'m')){
		HAL_UART_Transmit(&huart1,(uint8_t *)"1\r\n",3,HAL_MAX_DELAY);
	}
	else{
		HAL_UART_Transmit(&huart1,(uint8_t *)"0\r\n",3,HAL_MAX_DELAY);
	}

	// test 46

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

	// test 47

	if(static_strings_compare(&equal_a,&non_equal)){
		HAL_UART_Transmit(&huart1,(uint8_t *)"1\r\n",3,HAL_MAX_DELAY);
	}
	else{
		HAL_UART_Transmit(&huart1,(uint8_t *)"0\r\n",3,HAL_MAX_DELAY);
	}

	// test 48

	static_strings_string_descriptor *var_string;
	uint8_t uint8 = 200;
	var_string = static_strings_uint8_to_string(uint8);
	if(var_string != NULL){
		HAL_UART_Transmit(&huart1,var_string->string,var_string->length,HAL_MAX_DELAY);
		static_strings_deallocate(var_string);
	}

	// test 49

	uint16_t uint16 = 64200;
	var_string = static_strings_uint16_to_string(uint16);
	if(var_string != NULL){
		HAL_UART_Transmit(&huart1,var_string->string,var_string->length,HAL_MAX_DELAY);
		static_strings_deallocate(var_string);
	}

	// test 50

	uint32_t uint32 = 1000064200;
	var_string = static_strings_uint32_to_string(uint32);
	if(var_string != NULL){
		HAL_UART_Transmit(&huart1,var_string->string,var_string->length,HAL_MAX_DELAY);
		static_strings_deallocate(var_string);
	}

	// test 51

	int8_t int8 = 100;
	var_string = static_strings_int8_to_string(int8);
	if(var_string != NULL){
		HAL_UART_Transmit(&huart1,var_string->string,var_string->length,HAL_MAX_DELAY);
		static_strings_deallocate(var_string);
	}

	// test 52

	int16_t int16 = -32100;
	var_string = static_strings_int16_to_string(int16);
	if(var_string != NULL){
		HAL_UART_Transmit(&huart1,var_string->string,var_string->length,HAL_MAX_DELAY);
		static_strings_deallocate(var_string);
	}

	// test 53

	int32_t int32 = 500032100;
	var_string = static_strings_uint32_to_string(int32);
	if(var_string != NULL){
		HAL_UART_Transmit(&huart1,var_string->string,var_string->length,HAL_MAX_DELAY);
		static_strings_deallocate(var_string);
	}

	// test 54

	float float_number = 19.60232;
	var_string = static_strings_float_to_string(float_number);
	if(var_string != NULL){
		HAL_UART_Transmit(&huart1,var_string->string,var_string->length,HAL_MAX_DELAY);
		static_strings_deallocate(var_string);
	}

	// test 55

	double double_number = -1924.2342;
	var_string = static_strings_double_to_string(double_number);
	if(var_string != NULL){
		HAL_UART_Transmit(&huart1,var_string->string,var_string->length,HAL_MAX_DELAY);
		static_strings_deallocate(var_string);
	}

	// test 56

	static_strings_string_descriptor *copy_test_source_string = static_strings_save((uint8_t *)"I am a copy test\r\n");
	if(copy_test_source_string != NULL){
		static_strings_string_descriptor *copy_test_target_string = static_strings_allocate(100);
		if(static_strings_copy(copy_test_target_string,copy_test_source_string,0) != NULL){
			HAL_UART_Transmit(&huart1,copy_test_target_string->string,copy_test_target_string->length,HAL_MAX_DELAY);
			static_strings_deallocate(copy_test_source_string);
			static_strings_deallocate(copy_test_target_string);
		}
		else{
			HAL_UART_Transmit(&huart1,(uint8_t *)"error2\r\n",8,HAL_MAX_DELAY);
			HAL_UART_Transmit(&huart1,(uint8_t *)&static_strings_error_code,1,HAL_MAX_DELAY);
		}
	}
	else{
		HAL_UART_Transmit(&huart1,(uint8_t *)"error1\r\n",8,HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart1,(uint8_t *)&static_strings_error_code,1,HAL_MAX_DELAY);
	}

	// test 57

	static_strings_string_descriptor *clone_test_source_string = static_strings_save((uint8_t *)"I am a clone test\r\n");
	if(copy_test_source_string != NULL){
		static_strings_string_descriptor *clone_test_target_string = static_strings_clone(clone_test_source_string);
		if(clone_test_target_string != NULL){
			HAL_UART_Transmit(&huart1,clone_test_target_string->string,clone_test_target_string->length,HAL_MAX_DELAY);
			static_strings_deallocate(clone_test_source_string);
			static_strings_deallocate(clone_test_target_string);
		}
		else{
			HAL_UART_Transmit(&huart1,(uint8_t *)"error2\r\n",8,HAL_MAX_DELAY);
			HAL_UART_Transmit(&huart1,(uint8_t *)&static_strings_error_code,1,HAL_MAX_DELAY);
		}
	}
	else{
		HAL_UART_Transmit(&huart1,(uint8_t *)"error1\r\n",8,HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart1,(uint8_t *)&static_strings_error_code,1,HAL_MAX_DELAY);
	}

	// test 58

	static_strings_string_descriptor *move_test_source_string = static_strings_save((uint8_t *)"I am a move test\r\n");
	if(copy_test_source_string != NULL){
		static_strings_string_descriptor *move_test_target_string = static_strings_allocate(100);
		*move_test_target_string->string = '.';
		if(static_strings_move(move_test_target_string,move_test_source_string,1) != NULL){
			if(move_test_source_string->status == STATIC_STRINGS_STRING_STATUS_DEALLOCATED){
				HAL_UART_Transmit(&huart1,move_test_target_string->string,move_test_target_string->length,HAL_MAX_DELAY);
			}
			else{
				HAL_UART_Transmit(&huart1,(uint8_t *)"error3\r\n",8,HAL_MAX_DELAY);
			}
			static_strings_deallocate(move_test_source_string);
		}
		else{
			HAL_UART_Transmit(&huart1,(uint8_t *)"error2\r\n",8,HAL_MAX_DELAY);
			HAL_UART_Transmit(&huart1,(uint8_t *)&static_strings_error_code,1,HAL_MAX_DELAY);
		}
	}
	else{
		HAL_UART_Transmit(&huart1,(uint8_t *)"error1\r\n",8,HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart1,(uint8_t *)&static_strings_error_code,1,HAL_MAX_DELAY);
	}

	// test 59

	static_strings_string_descriptor *concatenate_and_clean_concatenate_at_test = static_strings_save((uint8_t *)"I am a ");
	static_strings_string_descriptor *concatenate_and_clean_concatenate_test = static_strings_save((uint8_t *)"concatenate test\r\n");
	if(concatenate_and_clean_concatenate_at_test != NULL && concatenate_and_clean_concatenate_test != NULL){
		static_strings_string_descriptor *concatenated_string = static_strings_concatenate_and_clean(concatenate_and_clean_concatenate_at_test,concatenate_and_clean_concatenate_test);
		if(concatenated_string != NULL){
			if(concatenate_and_clean_concatenate_at_test->status == STATIC_STRINGS_STRING_STATUS_DEALLOCATED){
				HAL_UART_Transmit(&huart1,concatenated_string->string,concatenated_string->length,HAL_MAX_DELAY);
			}
			else{
				HAL_UART_Transmit(&huart1,(uint8_t *)"error3\r\n",8,HAL_MAX_DELAY);
			}
			static_strings_deallocate(concatenate_and_clean_concatenate_at_test);
			static_strings_deallocate(concatenate_and_clean_concatenate_test);
			static_strings_deallocate(concatenated_string);
		}
		else{
			HAL_UART_Transmit(&huart1,(uint8_t *)"error2\r\n",8,HAL_MAX_DELAY);
			HAL_UART_Transmit(&huart1,(uint8_t *)&static_strings_error_code,1,HAL_MAX_DELAY);
		}
	}
	else{
		HAL_UART_Transmit(&huart1,(uint8_t *)"error1\r\n",8,HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart1,(uint8_t *)&static_strings_error_code,1,HAL_MAX_DELAY);
	}

	// test 60

	static_strings_string_descriptor *concatenate_all_test_one = static_strings_save((uint8_t *)"I am a ");
	static_strings_string_descriptor *concatenate_all_test_two = static_strings_save((uint8_t *)"concatenate all ");
	static_strings_string_descriptor *concatenate_all_test_three = static_strings_save((uint8_t *)"test\r\n");
	if(concatenate_all_test_one != NULL && concatenate_all_test_two != NULL && concatenate_all_test_three != NULL){
		static_strings_string_descriptor *concatenated_string = static_strings_concatenate_all(3,concatenate_all_test_one,concatenate_all_test_two,concatenate_all_test_three);
		if(concatenated_string != NULL){
			HAL_UART_Transmit(&huart1,concatenated_string->string,concatenated_string->length,HAL_MAX_DELAY);
			static_strings_deallocate(concatenate_all_test_one);
			static_strings_deallocate(concatenate_all_test_two);
			static_strings_deallocate(concatenate_all_test_three);
			static_strings_deallocate(concatenated_string);
		}
		else{
			HAL_UART_Transmit(&huart1,(uint8_t *)"error2\r\n",8,HAL_MAX_DELAY);
			HAL_UART_Transmit(&huart1,(uint8_t *)&static_strings_error_code,1,HAL_MAX_DELAY);
		}
	}
	else{
		HAL_UART_Transmit(&huart1,(uint8_t *)"error1\r\n",8,HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart1,(uint8_t *)&static_strings_error_code,1,HAL_MAX_DELAY);
	}

	// test 61

	concatenate_and_clean_concatenate_at_test = static_strings_save((uint8_t *)"I am a ");
	concatenate_and_clean_concatenate_test = static_strings_save((uint8_t *)"concatenate test\r\n");
	if(concatenate_and_clean_concatenate_at_test != NULL && concatenate_and_clean_concatenate_test != NULL){
		static_strings_string_descriptor *concatenated_string = static_strings_concatenate_and_clean_both(concatenate_and_clean_concatenate_at_test,concatenate_and_clean_concatenate_test);
		if(concatenated_string != NULL){
			if(concatenate_and_clean_concatenate_at_test->status == STATIC_STRINGS_STRING_STATUS_DEALLOCATED){
				if(concatenate_and_clean_concatenate_test->status == STATIC_STRINGS_STRING_STATUS_DEALLOCATED){
					HAL_UART_Transmit(&huart1,concatenated_string->string,concatenated_string->length,HAL_MAX_DELAY);
				}
				else{
					HAL_UART_Transmit(&huart1,(uint8_t *)"error4\r\n",8,HAL_MAX_DELAY);
				}
			}
			else{
				HAL_UART_Transmit(&huart1,(uint8_t *)"error3\r\n",8,HAL_MAX_DELAY);
			}
			static_strings_deallocate(concatenate_and_clean_concatenate_at_test);
			static_strings_deallocate(concatenate_and_clean_concatenate_test);
			static_strings_deallocate(concatenated_string);
		}
		else{
			HAL_UART_Transmit(&huart1,(uint8_t *)"error2\r\n",8,HAL_MAX_DELAY);
			HAL_UART_Transmit(&huart1,(uint8_t *)&static_strings_error_code,1,HAL_MAX_DELAY);
		}
	}
	else{
		HAL_UART_Transmit(&huart1,(uint8_t *)"error1\r\n",8,HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart1,(uint8_t *)&static_strings_error_code,1,HAL_MAX_DELAY);
	}
	// test 62

	concatenate_all_test_one = static_strings_save((uint8_t *)"I am a ");
	concatenate_all_test_two = static_strings_save((uint8_t *)"concatenate all ");
	concatenate_all_test_three = static_strings_save((uint8_t *)"test\r\n");
	if(concatenate_all_test_one != NULL && concatenate_all_test_two != NULL && concatenate_all_test_three != NULL){
		static_strings_string_descriptor *concatenated_string = static_strings_concatenate_and_clean_all(3,concatenate_all_test_one,concatenate_all_test_two,concatenate_all_test_three);
		if(concatenated_string != NULL){
			if(concatenate_all_test_one->status == STATIC_STRINGS_STRING_STATUS_DEALLOCATED){
				if(concatenate_all_test_two->status == STATIC_STRINGS_STRING_STATUS_ALLOCATED){
					if(concatenate_all_test_three->status == STATIC_STRINGS_STRING_STATUS_DEALLOCATED){
						HAL_UART_Transmit(&huart1,concatenated_string->string,concatenated_string->length,HAL_MAX_DELAY);
					}
					else{
						HAL_UART_Transmit(&huart1,(uint8_t *)"error5\r\n",8,HAL_MAX_DELAY);
					}
				}
				else{
					HAL_UART_Transmit(&huart1,(uint8_t *)"error4\r\n",8,HAL_MAX_DELAY);
				}
			}
			else{
				HAL_UART_Transmit(&huart1,(uint8_t *)"error3\r\n",8,HAL_MAX_DELAY);
			}
			static_strings_deallocate(concatenate_all_test_one);
			static_strings_deallocate(concatenate_all_test_two);
			static_strings_deallocate(concatenate_all_test_three);
			static_strings_deallocate(concatenated_string);
		}
		else{
			HAL_UART_Transmit(&huart1,(uint8_t *)"error2\r\n",8,HAL_MAX_DELAY);
			HAL_UART_Transmit(&huart1,(uint8_t *)&static_strings_error_code,1,HAL_MAX_DELAY);
		}
	}
	else{
		HAL_UART_Transmit(&huart1,(uint8_t *)"error1\r\n",8,HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart1,(uint8_t *)&static_strings_error_code,1,HAL_MAX_DELAY);
	}

	// test 63

	HAL_UART_Transmit(&huart1,static_strings_new_line->string,static_strings_new_line->length,HAL_MAX_DELAY);

	// test 64

	static_strings_string_descriptor *empty = static_strings_allocate(0);
	if(empty == NULL)
		HAL_UART_Transmit(&huart1,(uint8_t *)"error1\r\n",8,HAL_MAX_DELAY);
	else if(!static_strings_compare(static_strings_empty,empty))
		HAL_UART_Transmit(&huart1,(uint8_t *)"error2\r\n",8,HAL_MAX_DELAY);
	else
		HAL_UART_Transmit(&huart1,(uint8_t *)"success\r\n",9,HAL_MAX_DELAY);
	static_strings_deallocate(empty);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void)
{

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART1_Init 2 */

	/* USER CODE END USART1_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
