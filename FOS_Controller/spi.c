/*
 * spi.c
 *
 * Created: 28.03.2023 17:01:21
 *  Author: KDD
 * SPI interface for STuW180TR
 *
 * 
 */ 
#include "spi.h"
#define SS PB0 // The chip select pin is PB0
extern SPI_TransferStruct STransferStruct;


void spi_system_Init(void){				// Hardware initialization of SPI
	
	DDRB |= (1 << 1)|(1 << 2)|(1 << 0);
	PORTB |= (1 << 0)|(1 << 3)|(1 << SS);
    SPCR |= (1 << 7)|(1 << 6)|(1 << 4)|(1<<3)|(1 << 2)|(1<<1)|(1 << 0); // Module enable, interrupt enable, M/S select, polarity, phase
	SPSR |= (1 << 3); 	
}
void spi_Init(SPI_TransferStruct *spistruct){		//Software initialization of SPI
	
	spistruct -> ByteCounter = 0;
	spistruct -> spiRecieveBuf = 0;
	spistruct -> spiTransmitBuf = 0;
	spistruct -> transferSize = 0;
	spistruct -> spiDone = 0;
}


void spi_transmit(SPI_TransferStruct *spistruct,  uint8_t *RecieveBuf, uint8_t *TransmitBuf, uint8_t Size){	// Realization of transmit process
		
		if (spistruct -> ByteCounter == 0){
			spistruct -> spiRecieveBuf = RecieveBuf ;
			spistruct -> spiTransmitBuf = TransmitBuf;
			spistruct -> transferSize = Size;
			uint8_t  *pData;
			pData = (uint8_t *)spistruct -> spiTransmitBuf;	
			PORTB &= ~(1<<SS); 
			SPDR = *pData;
			spistruct -> spiTransmitBuf++;
		}
}

void interrupt_spi_happend(SPI_TransferStruct *spistruct){
	
	volatile *pDataRx;
	volatile *pDataTx;
	pDataRx = (uint8_t *)spistruct -> spiRecieveBuf;
	pDataTx = (uint8_t *)spistruct -> spiTransmitBuf;
	*pDataRx = SPDR;
	if (spistruct ->ByteCounter == spistruct->transferSize){
		 spistruct -> spiDone = 1;
		 spistruct -> ByteCounter = 0;
		 PORTB |= (1 << SS);
		 PORTD |= (1 << PD7); 
	 } 
	if( spistruct -> spiDone == 0){
		spistruct -> ByteCounter++;
		spistruct -> spiRecieveBuf++;
		SPDR = *pDataTx;
		spistruct -> spiTransmitBuf++;	
	}
}

ISR(SPI_STC_vect){
	interrupt_spi_happend(&STransferStruct);
}