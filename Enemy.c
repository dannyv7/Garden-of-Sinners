//Enemy.c
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "random.h"
#include "EnemyBMP.h"
extern uint8_t E1Flag;
extern uint8_t E2Flag;
extern uint8_t E3Flag;
extern signed short PlayerXPos;
extern signed short PlayerYPos;
extern unsigned long PlayerScore;
extern uint8_t PlayerHP;
extern int8_t BossHP;
uint8_t Idx1 = 0;
uint8_t Idx2 = 0;
uint8_t Mov1 = 0;
uint8_t Del1 = 0;

struct bullet{
	uint8_t XPos;
	uint8_t YPos;
	uint8_t Status;
};
typedef struct bullet BTyp;
BTyp B1[2] = {
	{20,0,0},
	{78,0,0},
};
//Generate the structs for the three enemies
struct enemy {
	const unsigned short * Image;
	const unsigned short * Atk;
	uint8_t Damage;
	uint8_t HP;
	uint8_t Status;
	const uint8_t Points;
	uint8_t XPos;
	uint8_t YPos;
};
typedef struct enemy ETyp;

//Struct for grunt
ETyp E1[3]={
	{bmp_Enemy1, bmp_Enemy1Atk, 0, 1, 0, 100, 0, 25},
	{bmp_Enemy1, bmp_Enemy1Atk, 0, 1, 0, 100, 0, 25},
	{bmp_Enemy1, bmp_Enemy1Atk, 0, 1, 0, 100, 0, 25},
};

ETyp E2[2]={
	{bmp_Enemy2, bmp_Enemy1Atk, 0, 1, 0, 100, 0, 25},
	{bmp_Enemy2, bmp_Enemy1Atk, 0, 1, 0, 100, 0, 25},
};

ETyp E3[1]={
	{bmp_Enemy3, bmp_Enemy1Atk, 0, 1, 0, 100, 0, 25},
};
void SpawnEnemy1 (void){
	E1[Idx1].XPos = Random32()%128;
	if(E1[Idx1].XPos > 108){
		E1[Idx1].XPos = 108;
	}
	DrawSprite(E1[Idx1].XPos, 25, E1[Idx1].Image, 25, 25, 0);
	E1[Idx1].Status = 1;
	Idx1 = (Idx1+1)%3;
	E1Flag = 0;
	
}
void SpawnEnemy2 (void){
	E2[Idx2].XPos = Random32()%128;
	if(E2[Idx2].XPos > 100){
		E2[Idx2].XPos = 100;
	}
	DrawSprite(E2[Idx2].XPos, 25, E2[Idx2].Image, 25, 25, 0);
	E2[Idx2].Status = 1;
	Idx2 = (Idx2+1)%2;
	E2Flag = 0;
}
void SpawnEnemy3 (void){
	E3[0].XPos = Random32()%128;
	if(E3[0].XPos > 100){
		E3[0].XPos = 100;
	}
	DrawSprite(E3[0].XPos, 25, E3[0].Image, 25, 25, 0);
	E3[0].Status = 1;
	E3Flag = 0;
}

void MoveEnemy (void){
	for(Mov1 = 0; Mov1 < 3; Mov1++){
		if(E1[Mov1].Status == 1){
			E1[Mov1].YPos += 2;
			DrawSprite(E1[Mov1].XPos, E1[Mov1].YPos, E1[Idx1].Image, 25, 25, 0);
		}
	}
}
void MoveEnemy2 (void){
	for(Mov1 = 0; Mov1 < 2; Mov1++){
		if(E2[Mov1].Status == 1){
			E2[Mov1].YPos += 2;
			DrawSprite(E2[Mov1].XPos, E2[Mov1].YPos, E2[Idx2].Image, 25, 25, 0);
		}
	}
}

void MoveEnemy3 (void){
	if(E3[0].Status == 1){
		E3[0].YPos += 2;
		DrawSprite(E3[0].XPos, E3[0].YPos, E3[0].Image, 25, 25, 0);
	}
}

void DeleteEnemy (void){
	for(Del1 = 0; Del1 < 3; Del1++){
		if(E1[Del1].YPos + 2 > 121){
			E1[Del1].YPos = 25;
			E1[Del1].Status = 0;
		}
	}
}
void DeleteEnemy2 (void){
	for(Del1 = 0; Del1 < 2; Del1++){
		if(E2[Del1].YPos + 2 > 121){
			E2[Del1].YPos = 25;
			E2[Del1].Status = 0;
		}
	}
}
void DeleteEnemy3 (void){
	if(E3[0].YPos + 2 > 121){
		E3[0].YPos = 25;
		E3[0].Status = 0;
	}
}
void HitDetection (void){
	for(Del1 = 0; Del1 < 3; Del1++){
		if(E1[Del1].Status == 1){
			if((E1[Del1].XPos < PlayerXPos + 28) && (E1[Del1].XPos > PlayerXPos - 10) && (E1[Del1].YPos < PlayerYPos)){
				DrawSprite(E1[Del1].XPos, E1[Del1].YPos, death, 25, 25, 0);
				E1[Del1].YPos = 25;
				E1[Del1].Status = 0;
				PlayerScore += 100;
			}
		}
	}
	for(Del1 = 0; Del1 < 2; Del1++){
		if(E2[Del1].Status == 1){
			if((E2[Del1].XPos < PlayerXPos + 35) && (E2[Del1].XPos > PlayerXPos - 10) && (E2[Del1].YPos < PlayerYPos)){
				E2[Del1].HP -=1;
				if(E2[Del1].HP == 0){
					DrawSprite(E2[Del1].XPos, E2[Del1].YPos, death, 25, 25, 0);
					E2[Del1].YPos = 25;
					E2[Del1].Status = 0;
					E2[Del1].HP = 2;
					PlayerScore += 200;
			}
		}
	}
}
	if(E3[0].Status == 1){
		if((E3[0].XPos < PlayerXPos + 28) && (E3[0].XPos > PlayerXPos - 10) && (E3[0].YPos < PlayerYPos)){
			E3[0].HP -=1;
			if(E3[0].HP == 0){
				DrawSprite(E3[0].XPos, E3[0].YPos, death, 25, 25, 0);
				E3[0].YPos = 25;
				E3[0].Status = 0;
				E3[0].HP = 3;
				PlayerScore += 300;
			}
		}
	}
}			

void HitDetection2(void){
	for(Del1 = 0; Del1 < 3; Del1++){
		if(E1[Del1].Status == 1){
			if((E1[Del1].XPos < PlayerXPos + 40) && (E1[Del1].XPos > PlayerXPos - 30) && (E1[Del1].YPos < PlayerYPos)){
				DrawSprite(E1[Del1].XPos, E1[Del1].YPos, death, 25, 25, 0);
				E1[Del1].YPos = 25;
				E1[Del1].Status = 0;
				PlayerScore += 100;
			}
		}
	}
	for(Del1 = 0; Del1 < 2; Del1++){
		if(E2[Del1].Status == 1){
			if((E2[Del1].XPos < PlayerXPos + 40) && (E2[Del1].XPos > PlayerXPos - 30) && (E2[Del1].YPos < PlayerYPos)){
				E2[Del1].HP -=1;
				if(E2[Del1].HP == 0){
					DrawSprite(E2[Del1].XPos, E2[Del1].YPos, death, 25, 25, 0);
					E2[Del1].YPos = 25;
					E2[Del1].Status = 0;
					E2[Del1].HP = 2;
					PlayerScore += 200;
			}
		}
	}
}
	if(E3[0].Status == 1){
		if((E3[0].XPos < PlayerXPos + 40) && (E3[0].XPos > PlayerXPos - 30) && (E3[0].YPos < PlayerYPos)){
			E3[0].HP -=1;
			if(E3[0].HP == 0){
				DrawSprite(E3[0].XPos, E3[0].YPos, death, 25, 25, 0);
				E3[0].YPos = 25;
				E3[0].Status = 0;
				E3[0].HP = 3;
				PlayerScore += 300;
			}
		}
	}
}

void ArmEnemies (void) {
	for(Del1 = 0; Del1 < 3; Del1++){
		if(E1[Del1].Status == 1){
			E1[Del1].Damage +=1;
		}
	}
	for(Del1 = 0; Del1 < 2; Del1++){
		if(E2[Del1].Status == 1){
			E2[Del1].Damage +=1;
		}
	}
	if(E3[0].Status == 1){
		E3[0].Damage+=1;
	}
}

void FireAway (void){
	for(Del1 = 0; Del1 < 3; Del1++){
		if(E1[Del1].Status == 1){
			if(E1[Del1].Damage == 12){
				DrawSprite(E1[Del1].XPos+10, E1[Del1].YPos+40, E1[Del1].Atk, 5, (121 - (E1[Del1].YPos+40)), 0);
				E1[Del1].Damage = 0;
				if(((PlayerXPos+12) > E1[Del1].XPos+5 && (PlayerXPos+12) < E1[Del1].XPos+20) && PlayerYPos > E1[Del1].YPos){
					PlayerHP -= 5;
				}
			}
		}
	}
	for(Del1 = 0; Del1 < 2; Del1++){
		if(E2[Del1].Status == 1){
			if(E2[Del1].Damage == 9){
				DrawSprite(E2[Del1].XPos+10, E2[Del1].YPos+40, E2[Del1].Atk, 5, (121 - (E2[Del1].YPos+40)), 0);
				E2[Del1].Damage = 0;
				if(((PlayerXPos+12) > E2[Del1].XPos+5 && (PlayerXPos+12) < E2[Del1].XPos+20) && PlayerYPos > E2[Del1].YPos){
					PlayerHP -= 10;
				}
			}
		}
	}
	if(E3[0].Status == 1){
		if(E3[0].Damage == 3){
			DrawSprite(E3[0].XPos+10, E3[0].YPos+40, E3[0].Atk, 5, (121 - (E3[0].YPos+40)), 0);
			E3[0].Damage = 0;
			if(((PlayerXPos+12) > E3[0].XPos+5 && (PlayerXPos+12) < E3[0].XPos+20) && PlayerYPos > E3[0].YPos){
					PlayerHP -= 15;
			}	
		}
	}
}
void BossDetection1(void){
	if(PlayerXPos > 39 && PlayerXPos < 89){
		BossHP -= 1;
	}
}
void BossDetection2(void){
		if(PlayerXPos > 24 && PlayerXPos <94){
			BossHP -=3;
		}
	}
void MeteorDraw(void){
	for(Del1 = 0; Del1 < 2; Del1++){
		DrawSprite(B1[Del1].XPos, B1[Del1].YPos, bmp_meteor, 30, 30, 0);
		B1[Del1].Status = 1;
	}
}
void MeteorMove(void){
	for(Del1 = 0; Del1 < 2; Del1++){
		if(B1[Del1].Status == 1){
			B1[Del1].YPos +=5;
			DrawSprite(B1[Del1].XPos, B1[Del1].YPos, bmp_meteor, 30, 30, 0);
			if(PlayerXPos >= B1[Del1].XPos && PlayerXPos <= (B1[Del1].XPos+28) && PlayerYPos <= (B1[Del1].YPos+30) && PlayerYPos && PlayerYPos >= B1[Del1].YPos){
				PlayerHP -= 10;
			}
		}
	}
}
void MeteorDelete(void){
		for(Del1 = 0; Del1 <2; Del1++){
			if((B1[Del1].YPos +1) >= 121){
				B1[Del1].YPos = 0;
				B1[Del1].Status = 0;
			}
		}
	}
	
void Destroy(void){
	for(Del1 = 0; Del1 < 3; Del1++){
		if(E1[Del1].Status == 1){
				DrawSprite(E1[Del1].XPos, E1[Del1].YPos, death, 25, 25, 0);
				E1[Del1].YPos = 25;
				E1[Del1].Status = 0;
				E1[Del1].HP = 1;
				PlayerScore += 100;
		}
	}
		for(Del1 = 0; Del1 < 2; Del1++){
		if(E2[Del1].Status == 1){
				DrawSprite(E2[Del1].XPos, E2[Del1].YPos, death, 25, 25, 0);
				E2[Del1].YPos = 25;
				E2[Del1].Status = 0;
				E2[Del1].HP = 2;
				PlayerScore += 200;
		}
	}
		for(Del1 = 0; Del1 < 1; Del1++){
			if(E3[Del1].Status == 1){
					DrawSprite(E3[Del1].XPos, E3[Del1].YPos, death, 25, 25, 0);
					E3[Del1].YPos = 25;
					E3[Del1].Status = 0;
					E3[Del1].HP = 3;
					PlayerScore += 300;
			}
		}	
	}