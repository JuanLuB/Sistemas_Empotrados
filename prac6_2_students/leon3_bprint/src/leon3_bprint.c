#include "../include/leon3_bprint.h"
#define LEON3_UART_TFF (0x400)

int8_t leon3_print_string(char* str)
{
	int i = 0;
		while((str[i] !=0)){
			leon3_putchar(str[i]);
			i++;
		}
		return 0;
}

int8_t leon3_print_uint8(uint8_t i)
{
	int8_t centenas, decenas, unidades;
	int8_t cent, dec, uni;

	centenas = i / 100;
		if (centenas == 0){
			decenas = i/10;
			cent=48+centenas;
			if (decenas==0){
				unidades = i;
				uni=48+unidades;
				leon3_putchar(uni);
			}
			else{
				dec=48+decenas;
				leon3_putchar(dec);
				unidades = i-decenas*10;
				uni = 48+unidades;
				leon3_putchar(uni);
			}
		}else{
			decenas = (i-centenas*100)/10;
			cent = centenas+48;
			dec=decenas+48;
			leon3_putchar(cent);
			leon3_putchar(dec);
			unidades = i-centenas*100-decenas*10;
			uni = 48+unidades;
		    leon3_putchar(unidades);

		}
		//leon3_putchar('\0');
		return 0;
}

int8_t leon3_print_uint32(uint32_t i){
	int8_t p1,p2,p3,p4;
	p1 = i/1000000000;
	p2 = (i-p1*1000000000)/1000000;
	p3 = (i-p2*1000000-p1*1000000000)/1000;
	p4 = i-p3*1000-p2*1000000-p1*1000000000;
	if(p1!=0){
		leon3_print_uint8(p1);
	}else if (p2!=0){
		leon3_print_uint8(p2);
	}else if (p3 != 0){
		leon3_print_uint8(p3);
	}
	leon3_print_uint8(p4);

	return 0;
}
