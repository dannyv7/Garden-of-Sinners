//PlayerX.c
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ADC.h"




void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode
unsigned long position = 0;
extern signed long PlayerXMod;

/*PlayerX_Init
-Initializes TIMER0A
-Set Priority to 4
*/
void PlayerX_Init(void){
//enable timer
  SYSCTL_RCGCTIMER_R |= 0x01;   // 0) activate TIMER0
  TIMER0_CTL_R = 0x00000000;    // 1) disable TIMER0A during setup
  TIMER0_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER0_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER0_TAILR_R = 2666667-1;    // 4) reload value
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
	TIMER0_ICR_R = TIMER_ICR_TATOCINT;		//acknowledge timer0A timeout	
	if(ADC_In()<2000){
		PlayerXMod = -2;
	}
	else if(ADC_In()>3600){
		PlayerXMod = +2;
	}else{
		PlayerXMod = 0;
	}
}