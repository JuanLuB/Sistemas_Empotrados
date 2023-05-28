#ifndef LEON3_BPRINT_H_
#define LEON3_BPRINT_H_

#include "leon3_types.h"
#include "leon3_uart.h"

//transmite a través del puerto serie la cadena de caracteres
//pasada por parámetro.

int8_t leon3_print_string(char* str); //ver **


//transmite a través del puerto serie el código ASCII de cada
//uno los dígitos del entero de 8 bits que se pasa como //parámetro. No transmite los ceros a la izquierda

int8_t leon3_print_uint8(uint8_t i); // ver ***


//transmite a través del puerto serie el código ASCII de cada //uno los dígitos del entero de 16 bits que se pasa como parámetro. No transmite los ceros a la izquierda
int8_t leon3_print_uint16(uint16_t i); // ver ****

#endif
