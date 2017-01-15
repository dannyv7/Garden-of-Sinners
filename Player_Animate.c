//Player_Animate.c
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "Player_AnimateBMP.h"
extern signed short PlayerXPos;
extern signed short PlayerYPos;
extern uint8_t AtkFlag;
extern uint8_t ArtsFlag;
extern uint8_t SpecFlag;

uint8_t AIdx1 = 0;
uint8_t i = 0;

//const unsigned short * attack[9] = {0, &SpellCardAnim[0], &ArtsArcanaAnim[0], 0, &SpecialAnim[0], 0 ,0 ,0 ,0};
struct attack {
	uint8_t XPos;
	int8_t YPos;
	uint8_t Dmg;
	uint8_t Status;
};
typedef struct attack ATyp;
//SpellCard
ATyp A1[5] = {
	{0, 0, 1, 0},
	{0, 0, 1, 0},
	{0, 0, 1, 0},
	{0, 0, 1, 0},
	{0, 0, 1, 0},
};
	
void SpellCardDraw (void){
	A1[AIdx1].XPos = PlayerXPos+5;				//Origin points
	A1[AIdx1].YPos = PlayerYPos - 25;
	DrawSprite(A1[AIdx1].XPos, A1[AIdx1].YPos, SpellCardAnim, 10, 15, 0);	//Draw to buffer
	A1[AIdx1].Status = 1;								//Set the status of current bullet to active
	AIdx1 = (AIdx1 +1)%17;							//Increment counter in circular manner
	AtkFlag = 0;												//Disable flag
}

void SpellCardMove (void){
	for(i = 0; i < 17; i++){						//Cycle through all active bullets and move them
		if(A1[i].Status == 1){
			A1[i].YPos += 2;
			DrawSprite(A1[AIdx1].XPos, A1[AIdx1].YPos, SpellCardAnim, 10, 15, 0);
		}
	}
}	

void SpellCardDelete (void){										//Disable and reset any bullets that are at the border of the screen
	for(i = 0; i < 17;i++){
		if((A1[i].YPos - 3) > 120){
			A1[i].YPos = 0;
			A1[i].Status = 0;
		}
	}
}
void SpellCard (void){
	DrawSprite(PlayerXPos, PlayerYPos-20, shot, 10, 15, 0);
	AtkFlag = 0;
	
}
void ArtsArcana (void){
	DrawSprite(PlayerXPos, PlayerYPos-25, blast, 25, 25, 0);
	ArtsFlag = 0;
}
void Special (void){
	DrawSprite(26, 98, clear, 75, 75, 0);
	SpecFlag = 0;
}