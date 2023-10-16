/*
 * uart1.h
 *
 * Created: 03.04.2023 16:38:34
 *  Author: KDD
 *
 *	Header file for UART module
 *
 */ 


#ifndef UART1_H_
#define UART1_H_
#include "avr/interrupt.h"
#include "avr/io.h"


typedef struct {
	uint8_t instanceNumber;
	uint8_t *bufferPtr;
	uint8_t transferSize;
	uint8_t	RxBufferCounter;
	volatile uint8_t done;
}UART_transferStruct;


int uart1_config();
void USART_sendChar(uint8_t character);
void interrupt_uart_happend(UART_transferStruct *fuart);
void uart_recieve(UART_transferStruct *fuart, uint8_t *pData, uint8_t Size);
void uart_transmit(UART_transferStruct *fuart, uint8_t *tData, uint8_t Size);

#endif /* UART1_H_ */