/*
 * uart1.c
 *
 * Created: 03.04.2023 16:38:16
 *  Author: KDD
 */ 
#define  F_CPU 7372800UL
#include "uart1.h"


extern UART_transferStruct uartStruct;
int speed = 9600;
uint8_t RxOrTx;	

	
int uart1_config(){
	
	uint16_t ubrr = (F_CPU/(speed*16)) - 1;
	UBRR1H = 0;
	UBRR1L = 47;
	UCSR1B |= (1 << RXEN1)|(1 << TXEN1);
	UCSR1C |= (3 << UCSZ1);
}
void USART_sendChar(uint8_t character)
{
	setUARTToTransmitter();
	while (!( UCSR1A & (1 << UDRE1)));
	UDR1 = character;	
}

void uart_recieve(UART_transferStruct *fuart, uint8_t *pData, uint8_t Size){

		setRsToReciever();		 
		fuart -> transferSize = Size;
		fuart -> bufferPtr = pData;
		fuart -> RxBufferCounter = 0;
		fuart ->done = 0;
		UCSR1B |= (1 << 7); 
		sei();					
}

void uart_transmit(UART_transferStruct *fuart, uint8_t *tData, uint8_t Size){
	
	setUARTToTransmitter();		
	fuart -> transferSize = Size;
	fuart -> bufferPtr = tData;
	fuart -> RxBufferCounter = 0;
	fuart -> done = 0;
	UDR1 = *tData;
	fuart -> bufferPtr++;
	fuart -> RxBufferCounter++;
	UCSR1B |= (1 << 6);
	sei();				
}


void interrupt_uart_happend(UART_transferStruct *fuart){
	
	if(RxOrTx == 1){
		volatile  uint8_t  *pdata8bits;
		pdata8bits = (uint8_t*) fuart -> bufferPtr;
		*pdata8bits = UDR1;
		fuart->bufferPtr++;
		fuart -> RxBufferCounter++;
		if (fuart -> RxBufferCounter == fuart -> transferSize){
			fuart -> RxBufferCounter = 0;
			fuart -> done = 1;
			UCSR1B &=~ (1 << 7);
			PORTD |= (1 << PD7);		
	  	}
	}
	else{
		if (fuart -> RxBufferCounter != fuart -> transferSize)
		{
		volatile  uint8_t  *pdata8bits;
		pdata8bits = (uint8_t*) fuart -> bufferPtr;
		UDR1 = *pdata8bits;
		fuart->bufferPtr++;
		fuart -> RxBufferCounter++;
		}
		if (fuart -> RxBufferCounter == fuart -> transferSize){
			fuart -> RxBufferCounter = 0;
			fuart -> done = 1;
			UCSR1B &=~ (1 << 6);
		}
	}
	
	}
ISR(USART1_RX_vect){
	RxOrTx = 1;
	interrupt_uart_happend(&uartStruct);
}
ISR(USART1_TX_vect){
	RxOrTx = 0;
	interrupt_uart_happend(&uartStruct);
}
void setUARTToTransmitter(){
	DDRD |= (1 << 5);
	PORTD |= (1 << 5);
}
void setRsToReciever(){
	DDRD |= (1 << 5);
	PORTD &= ~(1 << 5);
}
