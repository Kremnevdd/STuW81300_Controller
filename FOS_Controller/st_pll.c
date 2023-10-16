/*
 * st_pll.c
 *
 * Created: 28.03.2023 16:58:53
 *  Author: KDD
 *
 * This file configured only STuW81300TR control
 *
 *
 */ 

#include "st_pll.h"

SPI_TransferStruct STransferStruct= {.ByteCounter = 0};
uint8_t toTransmit[4];


void read_register(uint8_t address, uint8_t *storage){
	
	spi_Init(&STransferStruct);
	uint8_t toTransmit[4];
	toTransmit[0] = (address << 3) | 0x80;
	toTransmit[1] = 0xaa;
	toTransmit[2] = 0xAa;
	toTransmit[3] = 0xaa;
	spi_transmit(&STransferStruct,storage,toTransmit,3);
	while(STransferStruct.spiDone == 0);
	
} 
void write_register(uint8_t address, uint8_t *data){
	
	spi_Init(&STransferStruct);
	uint8_t storage[4];
	uint8_t dataPack[4];
	dataPack[0]= (address << 3)|*data;
	dataPack[1]= * (data + 1);
	dataPack[2]= * (data + 2);
	dataPack[3]= * (data + 3);
	spi_transmit(&STransferStruct,storage,dataPack,3);		/* Data in format as : 00000xxx; xxxxxxxx;xxxxxxxx;xxxxxxxx;*/
	while(STransferStruct.spiDone == 0);

	
}