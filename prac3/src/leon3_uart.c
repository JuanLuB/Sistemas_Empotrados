/*

 * leon3_uart.c
 *
 *  Created on: Feb 12, 2023
 *      Author: alex
 */



#include "leon3_uart.h"
//Estructura de datos que permite acceder a los registros de la //UART de LEON3
struct UART_regs
{

	/** \brief UART  Data Register */
	volatile uint32_t Data;    /* 0x80000100 */
	/** \brief UART  Status Register */
	volatile uint32_t Status;
	/** \brief UART  Control Register */
	volatile uint32_t Ctrl;
	/** \brief UART  Scaler Register */
	volatile uint32_t Scaler;  /* 0x8000010C */


};

//!  LEON3 UART A Transmit FIFO is FULL
#define LEON3_UART_TFF() (0x200) // 0010 0000 0000 pos= 9


//!  LEON3 UART A Transmit FIFO is EMPTY
#define LEON3_UART_TFE() (0x4) // 0100 pos=2

struct UART_regs * const pLEON3_UART_REGS= (struct UART_regs *)0x80000100;


#define leon3_UART_TF_IS_FULL() (pLEON3_UART_REGS->Status & LEON3_UART_TFF()) //MACRO

int8_t leon3_putchar(char c)

{
	uint32_t write_timeout=0;

	while(leon3_UART_TF_IS_FULL()&&(write_timeout < 0xAAAAA))
	{
			write_timeout++;
	}
		//Espera mientras la cola de transmisión esté llena

	if(write_timeout <  0xAAAAA){
			//COMPLETAR. Escribir el carácter en el registro Data
			pLEON3_UART_REGS->Data = c;
	}
	return (write_timeout == 0xAAAAA);
}
int8_t leon3_uart_tx_fifo_is_empty(){
			//completar
	return pLEON3_UART_REGS->Status & LEON3_UART_TFE();

}

