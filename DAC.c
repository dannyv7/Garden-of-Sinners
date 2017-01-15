#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "Random.h"
#include "TExaS.h"
#include "ADC.h"
#include "PlayerX.h"
// **************DAC_Init*********************
// Initialize 8-bit DAC, called once 
// Input: none
// Output: none
void DAC_Init(void){
	uint32_t delay;
	SYSCTL_RCGCGPIO_R |= 0x02;						//Initalize System Clock for PortB
	delay = SYSCTL_RCGC2_R;						//Wait for clock core to settle 
	GPIO_PORTB_DIR_R |= 0xFF;					//Set PB0-PB7 as outputs
	GPIO_PORTB_AFSEL_R &= ~ 0xFF;					//Disable alternate functions on PB0-PB7
	GPIO_PORTB_DEN_R |= 0xFF;					//Enable digital interfacing on PB0-PB7
}

// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Output: none
void DAC_Out(char data){
	GPIO_PORTB_DATA_R = data;
}
