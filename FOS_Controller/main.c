/*
 * FOS_Controller.c
 *
 * Created: 27.03.2023 3:16:07
 * Author : KDD
 */ 
#define PB0_LE PB0
#define PB1_CLK PB1
#define PB2_MOSI PB2
#include "main.h"
#include "util/delay.h"
#include "avr/io.h"

uint8_t error_buffer[1] = {0xFE};
uint8_t buffer[6] = {0x00,0x34,0x7f,0xC8,0,0};
UART_transferStruct uartStruct = {.done = 0};
uint8_t spiRxBuffer[4]= {0xd8,0xdd,0xAA,00};
uint8_t uBuffer[4]= {0xd8,0xdd,0xAA,00};
uint8_t spiTxBuffer[4] = {0x00,0xaf,0x0b,0x34};
uint8_t special_buffer[3] = {0x34, 0x34,0x55};
	
extern SPI_TransferStruct STransferStruct;

int main(void)
{
 		setRsToReciever();
		 DDRB |= (1<< PB5);
		uart1_config();
		spi_system_Init();
		spi_Init(&STransferStruct);
			PORTB |= (1<<PB5);
			int i = 0;

		while(1){
			switch(i){
				case 0 :
					uart_recieve(&uartStruct, buffer, 1);
					while(!uartStruct.done);
					if (buffer[0] == 0x57 ) // Write
					{
						uart_recieve(&uartStruct, buffer, 5);
						while(!uartStruct.done);
						i = 1;
					}
					if (buffer[0] == 0x52) // Read R= 0x52
					{
						i = 2;
					}
	 				if(buffer[0] == 0x33){
						i = 3;
					}
					if(buffer[0] == 0xAA){
						i = 4;
					}
					if(buffer[0] == 0xff){
						i = 5;
					}	
					if (buffer[0] == 0x12)
					{
						i = 6;
					}
									
					break;
				case 1 : 
							spiTxBuffer[0] = buffer[2];
							spiTxBuffer[1] = buffer[3];
							spiTxBuffer[2] = buffer[4];
							spiTxBuffer[3] = buffer[5];
							write_register(buffer[0], spiTxBuffer);	
							i = 0;
					break;
				
				case 2:
					uart_transmit(&uartStruct,buffer,5);
					while(!uartStruct.done);
					i = 0;
				break;
				case 3:
				uart_recieve(&uartStruct, buffer, 1);
				while(!uartStruct.done);
					if (buffer[0] == 0x01)
					{
						PORTB |= (1 << PB5);
					}
					else
					{
					PORTB &= ~(1 << PB5);
					}
					i = 0;
				break;
				case 4:
					uart_recieve(&uartStruct, buffer, 1);
					while(!uartStruct.done);
					if (set_attenuation( buffer[0]) ==  0x11)
					{
						uart_transmit(&uartStruct,buffer,1);
						while(!uartStruct.done);
					}
					else{
						uart_transmit(&uartStruct,error_buffer,1);
						while(!uartStruct.done);
					}
					i = 0;
				break;
				case 5:
					if (buffer[1] == 0x01)
					{
						PORTB |= (1 << PB4);
					}
					else
					{
						PORTB &= ~(1 << PB4);
					}
					i = 0; 
				break;	
				case 6:
				uart_recieve(&uartStruct, buffer, 1);
				while(!uartStruct.done);	
					choose_freq_source(buffer[0]);
					i = 0;
				break;	
			}
		}
		
}
	
	


	




			