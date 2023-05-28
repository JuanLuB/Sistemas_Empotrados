#include "leon3_bprint.h"


int8_t leon3_print_string(char* str){
	int i = 0;

	// Mientras el valor de str no sea '\0' seguimos mostrando los caracteres
	while (str[i] != '\0'){
		leon3_putchar(str[i]);
		i++;
	}
	while(!leon3_uart_tx_fifo_is_empty())
		;

	return 0;
}



int8_t leon3_print_uint16(uint16_t i){
		int8_t error=0;
		int16_t first_digit=1; //Evita ceros a la izquierda
		uint16_t aux=10000; //Número auxiliar para extraer dígitos

		//Si el número es 0 transmitir un único dígito
		if(i==0){
			error=leon3_putchar('0');
		}else{
			//Si no es 0 transmitir dígito a dígito
			while(aux&&(!error)){
				uint16_t digit;
				digit=i/aux;//extrae el dígito más significativo
				i-=aux*digit; //número con el resto de dígitos
				aux=aux/10; //centenas->decenas->unidades

				//Si ya se ha transmitido el primer dígito
				//o el dígito extraído es !=0,
				//transmitir el caracter del dígito
				if((0==first_digit)||digit){
					error=leon3_putchar('0'+digit);
					first_digit=0; //ya se impri
				}
			}
		}
		//espera a que la fifo de transmisión se vacíe
		while(!leon3_uart_tx_fifo_is_empty())
			;
		return error;
}



int8_t leon3_print_uint8(uint8_t i){
	int8_t error=0;
	int8_t first_digit=1; //Evita ceros a la izquierda
	uint8_t aux=100; //Número auxiliar para extraer dígitos

	//Si el número es 0 transmitir un único dígito
	if(i==0){
		error=leon3_putchar('0');
	}else{
		//Si no es 0 transmitir dígito a dígito
		while(aux&&(!error)){
			uint8_t digit;
			digit=i/aux;//extrae el dígito más significativo
			i-=aux*digit; //número con el resto de dígitos
			aux=aux/10; //centenas->decenas->unidades

			//Si ya se ha transmitido el primer dígito
			//o el dígito extraído es !=0,
			//transmitir el caracter del dígito
			if((0==first_digit)||digit){
				error=leon3_putchar('0'+digit);
				first_digit=0; //ya se impri
			}
		}
	}
	//espera a que la fifo de transmisión se vacíe
	while(!leon3_uart_tx_fifo_is_empty())
		;
	return error;
}
