/*
 * leon3_uart.c
 *
 *  Created on: Feb 18, 2022
 *      Author: alex
 */


#include "leon3_uart.h"

//Estructura de datos que permite acceder a los registros de la
//UART de LEON3

struct UART_regs
{
  /** \brief UART  Data Register */
  volatile uint32_t Data;     /* 0x80000100 */
  /** \brief UART  Status Register */
  volatile uint32_t Status;   /* 0x80000104 */
  /** \brief UART  Control Register */
  volatile uint32_t Ctrl;   /* 0x80000108 */
  /** \brief UART  Scaler Register */
  volatile uint32_t Scaler;   /* 0x8000010C */
  };

//!  LEON3 UART A Transmit FIFO is FULL
#define LEON3_UART_TFF (0x200)//Definir la mascara del bit que quiero comprobar(transmit fifo full)


//!  LEON3 UART A Transmit FIFO is EMPTY
#define LEON3_UART_TFE (0x4)//Definir la mascara del bit que quiero comprobar(transmit fifo emptyt)

//!  LEON3 UART A Receiver enable
#define LEON3_UART_RECEIVER_ENABLE (0x1)//Definir la mascara del bit que quiero modificar(Receiver_enable)

//!  LEON3 UART A Receiver interrupt enable
#define LEON3_UART_RECEIVER_INTERRUPT_ENABLE (0x4)//Definir la mascara del bit que quiero modificar(Receiver_interrupt_enable)

//!  LEON3 UART A LOOP_BACK
#define LEON3_UART_LOOP_BACK (0x80)//Definir la mascara del bit que quiero modificar(loop back)


struct UART_regs * const pLEON3_UART_REGS = (struct UART_regs *)0x80000100; //COMPLETADO

#define leon3_UART_TF_IS_FULL() (pLEON3_UART_REGS->Status & LEON3_UART_TFF)




int8_t leon3_putchar(char c)
{

  uint32_t write_timeout=0;

  while(leon3_UART_TF_IS_FULL()&&(write_timeout < 0xAAAAA))
  {
      write_timeout++;

  } //Espera mientras la cola de transmisión esté llena (el bit transmit fifo full esta a 1)


  if(write_timeout <  0xAAAAA){
    //COMPLETAR. Escribir el carácter en el registro Data
	  pLEON3_UART_REGS->Data = c;


  }
  return (write_timeout ==  0xAAAAA);
}

int8_t leon3_uart_tx_fifo_is_empty(){
    //COMPLETAR.
	int resultado;
	if(pLEON3_UART_REGS->Status & LEON3_UART_TFE){
		resultado = 1;
	}
	else{
		resultado = 0;
	}
	return resultado;

}



//Prac3b

char leon3_getchar(){
	return (uint8_t) pLEON3_UART_REGS ->Data;
}


// Pone a 1 el campo Receiver_enable del registro de control de la UART-A sin modificar el
// resto de campos de ese registro habilitando la recepción de datos a través de la UART.

void leon3_uart_ctrl_rx_enable(){
	pLEON3_UART_REGS ->Ctrl = pLEON3_UART_REGS ->Ctrl | LEON3_UART_RECEIVER_ENABLE;
}


// Pone a 1 el campo Receiver_interrupt_enable del registro de control de la UART-A sin modificar
// el resto de campos de ese registro habilitando las interrupciones tras la recepción de datos a través de la UART

void leon3_uart_ctrl_rx_irq_enable(){
	pLEON3_UART_REGS ->Ctrl = pLEON3_UART_REGS ->Ctrl | LEON3_UART_RECEIVER_INTERRUPT_ENABLE;
}


// Función que recibe como parámetro el valor que se quiere fijar en el campo loop_back del registro de control de la
// UART-A, de forma que si set_rxtxloop vale 1 se habilita el modo LOOP_BACK de la UART y si vale 0 se deshabilita.

void leon3_uart_ctrl_config_rxtx_loop (uint8_t set_rxtxloop){
	if (set_rxtxloop == 1){
		pLEON3_UART_REGS ->Ctrl = pLEON3_UART_REGS ->Ctrl | LEON3_UART_LOOP_BACK;
	}
	else{
		pLEON3_UART_REGS ->Ctrl = pLEON3_UART_REGS ->Ctrl & ~LEON3_UART_LOOP_BACK;
	}
}
