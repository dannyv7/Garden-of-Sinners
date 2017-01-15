//SysTick.c

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Player_Command.h"
#include "DAC.h"
#include "Player_Animate.h"
#include "ST7735.h"

extern uint8_t AtkFlag;
uint8_t ctr;
//*sound[9] = {0, &SpellCardSound[0], &ArtsArcanaSound[0], 0, &SpecialSound[0], 0 , 0 ,0 ,0};


/* SysTick_Init
-Initializes SysTick periodic interrupts
-Called once
-Sets rate to 30Hz */
void SysTick_Init(void){
	NVIC_ST_CTRL_R = 0;				//Disables SysTick during initialization
	NVIC_ST_RELOAD_R = 16777215;//(80000000/15)-1;
	NVIC_ST_CURRENT_R = 0;			//Any writes to current clears it
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000;	//Priority 2
	//Enables SysTick with core clock and interrupts
	NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE+NVIC_ST_CTRL_CLK_SRC+NVIC_ST_CTRL_INTEN;
}

/* SysTick_Handler
-Interrupt Service Routine
-Determines which action the player has chosen
-Activates animation and sound for corresponding actions */
void SysTick_Handler(void){
	uint32_t select;
	ctr++;
	if (ctr == 4){
		select = Player_Attack();
		if(select == 1){
				AtkFlag = select;
		}
		ctr = 0;
	}
}

