/*
 * dat_31a.c
 *
 * Created: 28.03.2023 13:28:20
 * Author: KDD
 *
 *	This is solution for attenuator DAT_31A-SP+
 *	Im not sure, that this solution is compatible for other attenuators
 */ 

#include "dat_31a.h"

/*
Three pins of port F
*/
#define DATA 0 // Serial data pin is F0
#define CLOCK 1 // Serial data pin is F1
#define LE 2	// Serial data pin is F2

uint8_t set_attenuation(uint8_t attenuation){
	if ((attenuation>=0)&&(attenuation<32))
	{
		DDRF |= (1 << LE)|(1 << CLOCK)|(1 << DATA);
		PORTF &= !(1 << LE);
		for(int p = 5; p >= 0; p--){
			PORTF &= ~(1 << CLOCK);
			PORTF &= ~(1 << DATA);
			PORTF |= (attenuation >> p) & (1 << DATA);
			PORTF |= (1 << CLOCK);
		}
		PORTF &= ~(1 << CLOCK);
		PORTF &= ~(1 << DATA);	
		PORTF |= (1 << LE);
		PORTF &= !(1 << LE);
	
	return 0x11;
}else{
	return 0xFE;
}
	}



