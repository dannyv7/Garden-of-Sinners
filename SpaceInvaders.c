// SpaceInvaders.c
// Runs on LM4F120/TM4C123
// Jonathan Valvano and Daniel Valvano
// This is a starter project for the EE319K Lab 10

// Last Modified: 3/6/2015 
// http://www.spaceinvaders.de/
// sounds at http://www.classicgaming.cc/classics/spaceinvaders/sounds.php
// http://www.classicgaming.cc/classics/spaceinvaders/playguide.php
/* This example accompanies the books
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2014

   "Embedded Systems: Introduction to Arm Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2014

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
// ******* Possible Hardware I/O connections*******************
// Slide pot pin 1 connected to ground
// Slide pot pin 2 connected to PE2/AIN1
// Slide pot pin 3 connected to +3.3V 
// fire button connected to PE0
// special weapon fire button connected to PE1
// 8*R resistor DAC bit 0 on PB0 (least significant bit)
// 4*R resistor DAC bit 1 on PB1
// 2*R resistor DAC bit 2 on PB2
// 1*R resistor DAC bit 3 on PB3 (most significant bit)
// LED on PB4
// LED on PB5

// Backlight (pin 10) connected to +3.3 V
// MISO (pin 9) unconnected
// SCK (pin 8) connected to PA2 (SSI0Clk)
// MOSI (pin 7) connected to PA5 (SSI0Tx)
// TFT_CS (pin 6) connected to PA3 (SSI0Fss)
// CARD_CS (pin 5) unconnected
// Data/Command (pin 4) connected to PA6 (GPIO), high for data, low for command
// RESET (pin 3) connected to PA7 (GPIO)
// VCC (pin 2) connected to +3.3 V
// Gnd (pin 1) connected to ground

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "Random.h"
#include "TExaS.h"
#include "DAC.h"
#include "BGM.h"
#include "ADC.h"
#include "SysTick.h"
#include "Player_Command.h"
#include "PlayerPos.h"
#include "Enemy.h"
#include "Spawn.h"
#include "Player_Animate.h"
#include "SpaceInvadersBMP.h"
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Delay100ms(uint32_t count); // time delay in 0.1 seconds
//Global variable declarations
signed short PlayerXPos = 52;
signed short PlayerYPos = 120;
signed short PlayerXMod;
signed short PlayerYMod;
unsigned long PlayerScore;
uint8_t PlayerHP = 100;
uint8_t AtkFlag = 0;
uint8_t ArtsFlag = 0;
uint8_t SpecFlag = 0;
uint8_t E1Flag = 0;
uint8_t E2Flag = 0;
uint8_t E3Flag = 0;
uint8_t BossFlag = 0;
int8_t BossHP = 50;
uint8_t BossAtk1;
uint8_t BossAtk2;
uint8_t BossAtk3;
char HP[3] = {0x72, 0x80, 0x58};

// *************************** Images ***************************
// enemy ship that starts at the top of the screen (arms/mouth closed)
// width=16 x height=10


// *************************** Capture image dimensions out of BMP**********

int main(void){
	DisableInterrupts();
	TExaS_Init();                 // set system clock to 80 MHz
	Random_Init(1);
	ADC_Init89();
	PlayerPos_Init();
	Player_Init();
	DAC_Init();
	ST7735_InitR(INITR_REDTAB); // screen initialization
	BGM_Init();
	Timer2A_Init();
	//SysTick_Init();
		ST7735_FillScreen(0);
	while(Player_Attack() == 0){
		ST7735_DrawBitmap(0, 121, cover, 128, 121);
	}
	ST7735_FillScreen(0);
	EnableInterrupts();
	ST7735_SetRotation(0x00);
	while(BossFlag ==0){
		//X Position of player
		PlayerXPos += PlayerXMod;			//Set new X Position
		if(PlayerXPos > 108){							//Set X right bound
			PlayerXPos = 108;
		}
		if(PlayerXPos < -2){									//Set X left bound
			PlayerXPos = -2;
		}
		//Y Position of player
		PlayerYPos += PlayerYMod;			//Set new Y Position
		if(PlayerYPos < 30){								//Set Y top bound
			PlayerYPos = 30;
		}
		if(PlayerYPos > 121){							//Set Y bottom bound
			PlayerYPos = 121;
		}
		//Generate virtual image
		DrawVirtualBg();
		//Spawn Tier 3 Enemy if 1.5 seconds elapse
		if(E1Flag != 0){
			SpawnEnemy1();
		}
		//Spawn Tier 2 Enemy if 4 seconds elapse
		if(E2Flag != 0){
			SpawnEnemy2();
		}
		//Spawn Tier 1 Enemy if 9 seconds elapse
		if(E3Flag != 0){
			SpawnEnemy3();
		}
		//Remove all enemies that are past the screen
		DeleteEnemy();
		DeleteEnemy2();
		DeleteEnemy3();
		//Change the movement of enemies
		MoveEnemy();
		MoveEnemy2();
		MoveEnemy3();
		//Character Actions
		DrawSprite(PlayerXPos, PlayerYPos, char1, 25, 25,0);
		if(AtkFlag == 1){			//Generate a new bullet if flag set by button press//SpellCardDraw();
			if(Player_Attack() == 1){
				SpellCard();
				HitDetection();
			}
		}
		if(ArtsFlag == 1){
			if(Player_Attack() == 2){
				ArtsArcana();
				HitDetection2();
			}
		}
		if(SpecFlag == 1){
			if(Player_Attack() == 4){
				Special();
				Destroy();
			}
		}
		ArmEnemies();
		FireAway();
		
		//Don't let your dreams be dreams
		DrawBg();		
		ST7735_SetCursor(5, 14);
		ST7735_OutUDec(PlayerScore); 
		ST7735_SetCursor(5, 13);
		ST7735_OutUDec(PlayerHP);
		if(PlayerHP > 100 | PlayerHP <1){
			Delay100ms(10);
			while(Player_Attack() == 0){
				ST7735_DrawBitmap(0, 121, rip, 128, 121);
			}
			PlayerScore /= 2;
			PlayerHP = 100;
		}
		
	}
	//Boss Summon Sequence
	PlayerXPos = 52;
	PlayerYPos = 120;
	DrawVirtualBg();
	DrawSprite(PlayerXPos, PlayerYPos, char1, 25, 25, 0);
	DrawSprite(39, 50, summon2, 50, 50, 0);
	DrawBg();
	Delay100ms(1);
	DrawVirtualBg();
	DrawSprite(PlayerXPos, PlayerYPos, char1, 25, 25, 0);
	DrawSprite(39, 50, summon2, 50, 50, 0);
	DrawBg();
	Delay100ms(1);
	DrawVirtualBg();
	DrawSprite(PlayerXPos, PlayerYPos, char1, 25, 25, 0);
	DrawSprite(39, 50, summon3, 50, 50, 0);
	DrawBg();
	Delay100ms(1);
	DrawVirtualBg();
	DrawSprite(PlayerXPos, PlayerYPos, char1, 25, 25, 0);
	DrawSprite(39, 50, summon4, 50, 50, 0);
	DrawBg();
	Delay100ms(1);
	DrawVirtualBg();
	DrawSprite(PlayerXPos, PlayerYPos, char1, 25, 25, 0);
	DrawSprite(39, 55, boss, 50, 50, 0);
	DrawBg();
	//Boss Fight
	while(BossHP > 0){
			//Position of player
		PlayerXPos += PlayerXMod;			//Set new X Position
		if(PlayerXPos > 108){							//Set X right bound
			PlayerXPos = 108;
		}
		if(PlayerXPos < -2){									//Set X left bound
			PlayerXPos = -2;
		}
		//Y Position of player
		PlayerYPos += PlayerYMod;			//Set new Y Position
		if(PlayerYPos < 80){								//Set Y top bound
			PlayerYPos = 80;
		}
		if(PlayerYPos > 121){							//Set Y bottom bound
			PlayerYPos = 121;
		}
		//Generate virtual image
		DrawVirtualBg();
		//Draw Boss
		DrawSprite(39, 55, boss, 50, 50, 0);
		//Player Stuff
		DrawSprite(PlayerXPos, PlayerYPos, char1, 25, 25,0);
		//Boss stuff
		if(BossAtk1 == 1){
			DrawSprite(0, 121, triplet2, 10, 121, 0);
			DrawSprite(118, 121, triplet2, 10, 121, 0);
			DrawSprite(59, 115, triplet, 10, 66, 0);
			if((PlayerXPos >=59 && PlayerXPos <69) || (PlayerXPos <= 59 && PlayerXPos > 47)){
				PlayerHP -= 5;
			}
			if(PlayerXPos >=0 && PlayerXPos <10) {
				PlayerHP -= 5;
			}
			if(PlayerXPos <= 128 && PlayerXPos>= 98){
				PlayerHP -=5;
			}
		BossAtk1 = 0;
		}
		if(BossAtk2 == 1){
			DrawSprite(29, 121, triplet2, 10, 121, 0);
			DrawSprite(88, 121, triplet2, 10, 121, 0);
			if((PlayerXPos >=29 && PlayerXPos <39) || (PlayerXPos <= 29 && PlayerXPos > 17)){
				PlayerHP -= 5;
			}
			if((PlayerXPos >=88 && PlayerXPos <98) || (PlayerXPos <= 88 && PlayerXPos > 76)){
				PlayerHP -= 5;
			}
			BossAtk2 = 0;
		}	
		if(BossAtk3 ==1){
			MeteorDraw();
			BossAtk3 = 0;
		}
		MeteorMove();
		MeteorDelete();
		//Player Attack
		if(AtkFlag == 1){			//Generate a new bullet if flag set by button press//SpellCardDraw();
			if(Player_Attack() == 1){
				SpellCard();
				BossDetection1();
			}
		}
		if(ArtsFlag == 1){
			if(Player_Attack() == 2){
				ArtsArcana();
				BossDetection2();
			}
		}
		if(SpecFlag == 1){
			if(Player_Attack() == 4){
				Special();
				BossHP -= 10;
			}
		}
		//Don't let your dreams be dreams
		DrawBg();		
		ST7735_SetCursor(5, 14);
		ST7735_OutUDec(PlayerScore); 
		ST7735_SetCursor(5, 13);
		ST7735_OutUDec(PlayerHP);
		ST7735_SetCursor(5, 15);
		ST7735_OutUDec(BossHP);
		if(PlayerHP > 100 | PlayerHP <1){
			Delay100ms(10);
			while(Player_Attack() == 0){
				ST7735_DrawBitmap(0, 121, rip, 128, 121);
			}
			PlayerScore /= 2;
			PlayerHP = 100;
		}
				
	}	
	ST7735_FillScreen(0);
	ST7735_DrawBitmap(0, 121, victory, 128, 121);
	ST7735_SetCursor(5, 14);
	ST7735_OutUDec(PlayerScore); 
}
// You can use this timer only if you learn how it works
void Delay100ms(uint32_t count){uint32_t volatile time;
  while(count>0){
    time = 727240;  // 0.1sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}
