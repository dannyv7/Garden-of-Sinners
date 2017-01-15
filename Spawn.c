//Spawn.c
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Player_Command.h"
extern uint8_t E1Flag;
extern uint8_t E2Flag;
extern uint8_t E3Flag;
extern uint8_t AtkFlag;
extern uint8_t ArtsFlag;
extern uint8_t SpecFlag;
extern uint8_t BossFlag;
extern uint8_t BossAtk1;
extern uint8_t BossAtk2;
extern uint8_t BossAtk3;
uint8_t E1Ctr = 0;
uint8_t E2Ctr = 0;
uint8_t E3Ctr = 0;
uint8_t E4Ctr = 0;
uint8_t E5Ctr = 0;
uint8_t E6Ctr = 0;
uint8_t B1Ctr = 0;
uint8_t B2Ctr = 0;
uint8_t B3Ctr = 0;
unsigned short BossCtr=0;

/* Timer2A_Init
-Initializes Timer2A
-Sets occurance every .1 seconds
-No inputs or outpus */
void Timer2A_Init(void){  
	SYSCTL_RCGCTIMER_R |= 0x04;   // 0) activate TIMER2
	TIMER2_CTL_R = 0x00000000;    // 1) disable TIMER2A during setup
	TIMER2_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
	TIMER2_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
	TIMER2_TAILR_R = 8000000-1;    // 4) reload value
	TIMER2_TAPR_R = 0;            // 5) bus clock resolution
	TIMER2_ICR_R = 0x00000001;    // 6) clear TIMER2A timeout flag
	TIMER2_IMR_R = 0x00000001;    // 7) arm timeout interrupt
	// interrupts enabled in the main program after all devices initialized
	// vector number 37, interrupt number 21
	NVIC_EN0_R = 1<<23;           // 9) enable IRQ 21 in NVIC
	TIMER2_CTL_R = 0x00000001;    // 10) enable TIMER2A
}
/* Timer1A_Handler
-ISR for Timer2A
-Spawns enemies through time triggers */
void Timer2A_Handler(void){
	TIMER2_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER1A timeout
	E1Ctr++;
	E2Ctr++;
	E3Ctr++;
	E4Ctr++;
	E5Ctr++;
	E6Ctr++;
	B1Ctr++;
	B2Ctr++;
	B3Ctr++;
	BossCtr++;
	if(E1Ctr == 15){				//Every 1.5 seconds spawn tier 3 enemy
		E1Flag = 1;
		E1Ctr = 0;
	}
	if(E2Ctr == 40){				//Every 4 seconds spawn tier 2 enemy
		E2Flag = 1;
		E2Ctr = 0;
	}
	if(E3Ctr == 70){			//Every 7 seconds spawn tier 1 enemy 
		E3Flag = 1;
		E3Ctr = 0;
	}
	if(E4Ctr == 3){
		AtkFlag = 1;
		E4Ctr = 0;
	}
	if(E5Ctr == 30){
		ArtsFlag = 1;
		E5Ctr = 0;
	}
	if(E6Ctr == 200){
		SpecFlag = 1;
		E6Ctr = 0;
	}
	if(BossCtr==1350){
		BossFlag = 1;
	}
	if(B1Ctr==15){
		BossAtk1 = 1;
		B1Ctr = 0;
	}
	if(B2Ctr == 25){
		BossAtk2 = 1;
		B2Ctr = 0;
	}
	if(B3Ctr == 70){
		BossAtk3 = 1;
		B3Ctr = 0;
	}
}
