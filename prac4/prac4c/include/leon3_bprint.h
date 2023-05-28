/*
 * leon3_bprint.h

 *
 *  Created on: Feb 14, 2023
 *      Author: alex
 */
#ifndef LEON3_BPRINT_H_
#define LEON3_BPRINT_H_

#include "leon3_types.h"
#include "leon3_uart.h"

//transmite a través del puerto serie la cadena de caracteres
//pasada por parámetro.

int8_t leon3_print_string(char* str);

//transmite a través del puerto serie el entero transformado en
//cadena de caracteres.

int8_t leon3_print_uint8(uint8_t i);
//transmite a través del puerto serie el código ASCII de cada
//uno los dígitos del entero de 16 bits que se pasa como parámetro. No transmite los ceros a la izquierda
int8_t leon3_print_uint16(uint16_t i);  // ver ****
#endif /* LEON3_BPRINT_H_ */
int8_t leon3_print_uint32( uint32_t i);
