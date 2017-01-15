void Death(void) {
	for(Del1 = 0; Del1 < 3; Del1++){
		if(E1[Del1].Status == 1){
			if((E1[Del1].XPos == PlayerXPos) && (E1[Del1].YPos -5 == PlayerYPos + 25){
			DrawSprite(PlayerXPos, PlayerYPos, death, 25, 25, 0);
			}
			if((E1[Del1].XPos == PlayerXPos) && (E1[Del1].YPos + 25 == PlayerYPos - 5){
			DrawSprite(PlayerXPos, PlayerYPos, death, 25, 25, 0);
			}
			if((E1[Del1].YPos == PlayerYPos) && ((E1[Del1].XPos -5) == PlayerXPos + 25){
			DrawSprite(PlayerXPos, PlayerYPos, death, 25, 25, 0);
			}
			if((E1[Del1].YPos == PlayerYPos) && ((E1[Del1].XPos + 25) == PlayerXPos - 5){
			DrawSprite(PlayerXPos, PlayerYPos, death, 25, 25, 0);
			}
	for(Del1 = 0; Del1 < 2; Del1++){
		if(E2[Del1].Status == 1){
			if((E2[Del1].XPos == PlayerXPos) && (E2[Del1].YPos -5 == PlayerYPos + 25){
			DrawSprite(PlayerXPos, PlayerYPos, death, 25, 25, 0);
			}
			if((E2[Del1].XPos == PlayerXPos) && (E2[Del1].YPos + 25 == PlayerYPos - 5){
			DrawSprite(PlayerXPos, PlayerYPos, death, 25, 25, 0);
			}
			if((E2[Del1].YPos == PlayerYPos) && ((E2[Del1].XPos -5) == PlayerXPos + 25){
			DrawSprite(PlayerXPos, PlayerYPos, death, 25, 25, 0);
			}
			if((E2[Del1].YPos == PlayerYPos) && ((E2[Del1].XPos + 25) == PlayerXPos - 5){
			DrawSprite(PlayerXPos, PlayerYPos, death, 25, 25, 0);
			}
	if(E3[0].Status == 1){
		if((E3[0].XPos == PlayerXPos) && (E3[0].YPos -5 == PlayerYPos + 25){
			DrawSprite(PlayerXPos, PlayerYPos, death, 25, 25, 0);
			}
			if((E3[0].XPos == PlayerXPos) && (E3[0].YPos + 25 == PlayerYPos - 5){
			DrawSprite(PlayerXPos, PlayerYPos, death, 25, 25, 0);
			}
			if((E3[0].YPos == PlayerYPos) && ((E3[0].XPos -5) == PlayerXPos + 25){
			DrawSprite(PlayerXPos, PlayerYPos, death, 25, 25, 0);
			}
			if((E3[0].YPos == PlayerYPos) && ((E3[0].XPos + 25) == PlayerXPos - 5){
			DrawSprite(PlayerXPos, PlayerYPos, death, 25, 25, 0);
			}