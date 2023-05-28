/*
 * bprint_swr.h
 *
 *  Created on: Apr 23, 2013
 *      Author: user
 */

#ifndef BPRINT_SWR_H_
#define BPRINT_SWR_H_


#include <public/basic_types.h>


#ifdef __cplusplus

extern "C" {

#endif

	int8_t print_uint32(uint32_t i);
	int8_t print_int32(uint32_t i);
	int8_t print_uint8(uint8_t i);
	int8_t print_string(const char* str);
	int8_t print_char(char a);



#ifdef __cplusplus

}

#endif



#endif /* BPRINT_SWR_H_ */
