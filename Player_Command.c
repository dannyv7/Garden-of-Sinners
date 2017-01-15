//Player_Command.c

#include <stdint.h>
#include "tm4c123gh6pm.h"
/* Player_Init
-Initializes the pins for player inputting
- */
void Player_Init(void){
	uint32_t delay;
	SYSCTL_RCGCGPIO_R |= 0x10;				//Initialize System Clock for PortD
	delay = SYSCTL_RCGCGPIO_R	;		//Allow clock core to settle
	GPIO_PORTE_DIR_R &= ~0x0E;		//Set PD0-PD2 as inputs
	GPIO_PORTE_AFSEL_R &= ~ 0x0E;	//Disable alternate functions on PD0-PD2
	GPIO_PORTE_DEN_R |= 0x0E;		//Enable digital interfacing on PD0-PD2
}

/* Player_Attack
-Reads PortA for keys pressed
-Translates the read into a 4bit number
-Returns an index for its respective handler */
uint32_t Player_Attack(void){
	uint32_t read_key;				//Create dummy variable
	read_key = (GPIO_PORTE_DATA_R&0x0E);	//See what keys are pressed
	read_key >>= 1;
	return read_key;				//Return key combination to caller
}
