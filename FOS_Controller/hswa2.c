/*
 * hswa2.c
 *
 * Created: 28.03.2023 12:51:03
 *  Author: KDD
 *	This is a driver for switch-mux chip HSWA2
 *
 */ 
#include "hswa2.h"

#define CONTROL_1 3 // Pin PE3 is first control pin
#define CONTROL_2 2 // Pin PE2 is second control pin

/*
OxOf - choose RF1 as input
0xf0 - choose RF2 as input
*/

int choose_freq_source(uint8_t choice){
	DDRE |= (1 << CONTROL_1)|(1 << CONTROL_2);
	if (choice == 0x0f){		//RF1 chosed as input(generator)
		
		PORTE &=~ (1 << CONTROL_1);
		PORTE |= (1 << CONTROL_2);	
	}
	if(choice == 0xf0){			//RF2 choosed as input(external)	
		
		PORTE &= ~(1 << CONTROL_2);
		PORTE |= (1 << CONTROL_1);
	}
	return 1;
	
}