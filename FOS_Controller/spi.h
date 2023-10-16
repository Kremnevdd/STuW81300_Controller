/*
 * spi.h
 *
 * Created: 28.03.2023 17:01:12
 *  Author: KDD
 *
 *	Header file for hardware SPI
 *
 */ 


#ifndef SPI_H_
#define SPI_H_
#include "avr/io.h"
#include "avr/interrupt.h"
#include "util/delay.h"



typedef struct{
	uint8_t *spiRecieveBuf;
	uint8_t *spiTransmitBuf;
	uint16_t transferSize;
	uint8_t	ByteCounter;
	volatile uint8_t spiDone;
		}SPI_TransferStruct;

void spi_system_Init(void);
void spi_Init(SPI_TransferStruct *spistruct);
void interrupt_spi_happend(SPI_TransferStruct *spistruct);
void spi_transmit(SPI_TransferStruct *spistruct,  uint8_t *RecieveBuf, uint8_t *TransmitBuf, uint8_t Size);

#endif /* SPI_H_ */