/*
 * bprint.c
 *
 *  Created on: Apr 23, 2013
 *      Author: user
 */

#include <leon3_types.h>
#include <leon3_bprint.h>
#include <leon3_uart.h>

	int8_t print_uint32(uint32_t i){
		return leon3_print_uint32(i);
	}


	int8_t print_uint8(uint8_t i){
		return leon3_print_uint8(i);
	}

	int8_t print_string(const char* str){
		return leon3_print_string(str);
	}

	int8_t print_char(char c){
		return leon3_putchar(c);
	}
