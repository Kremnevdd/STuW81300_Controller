/*
 * st_pll.h
 *
 * Created: 28.03.2023 16:59:09
 *  Author: KDD
 */ 


#ifndef ST_PLL_H_
#define ST_PLL_H_

#include "spi.h"
#include "main.h"
#include "avr/io.h"
#include "avr/interrupt.h"
#include "uart1.h"


void read_register(uint8_t address, uint8_t *storage);

#endif /* ST_PLL_H_ */