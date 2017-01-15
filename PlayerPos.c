//PlayerPos.c
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ADC.h"


extern signed short PlayerXMod;
extern signed short PlayerYMod;


/*PlayerX_Init
-Initializes TIMER0A
-Set Priority to 4
*/

void PlayerPos_Init(void){
//enable timer
  SYSCTL_RCGCTIMER_R |= 0x01;   // 0) activate TIMER0
  TIMER0_CTL_R = 0x00000000;    // 1) disable TIMER0A during setup
  TIMER0_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER0_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER0_TAILR_R = (80000000/30)-1;    // 4) reload value
  TIMER0_TAPR_R = 0;            // 5) bus clock resolution
  TIMER0_ICR_R = 0x00000001;    // 6) clear TIMER0A timeout flag
  TIMER0_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x80000000; // 8) priority 4
// interrupts enabled in the main program after all devices initialized
// vector number 35, interrupt number 19
  NVIC_EN0_R = 1<<19;           // 9) enable IRQ 19 in NVIC
  TIMER0_CTL_R = 0x00000001;    // 10) enable TIMER0A
}

/*Timer0A_Handler
-Reads the ADC
-Converts the ADC into an X position
-Returns X position to main
*/
void Timer0A_Handler(void){
	TIMER0_ICR_R = TIMER_ICR_TATOCINT;
	if((ADC0_RIS_R & 0x04)==0) {}   /// if ADC = 0, not Done
		////done
		 ADC0_ISC_R = 0x04;             // 4) acknowledge completion
	  PlayerXMod = ADC0_SSFIFO2_R&0xFFFF;  // 3A) read first result
	  PlayerYMod = ADC0_SSFIFO2_R&0xFFFF;  // 3B) read second result
		 ADC0_PSSI_R = 0x04;            // 1) initiate SS2
		//Determine X modifier
		if(PlayerXMod < 100){
			PlayerXMod = 4;
		}else if(PlayerXMod <3000){
			PlayerXMod = -4;
		}else{
			PlayerXMod = 0;
		}
		//Determine Y modifier
		if(PlayerYMod < 100){
			PlayerYMod = 4;
		}else if(PlayerYMod < 3100){
			PlayerYMod = -4;
		}else{
			PlayerYMod = 0;
		}
			
	}
