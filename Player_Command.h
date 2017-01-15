//Player_Command.c

/* Player_Init
-Initializes the pins for player inputting
- */
void Player_Init(void);

/* Player_Attack
-Reads PortA for keys pressed
-Translates the read into a 4bit number
-Returns an index for its respective handler */
uint32_t Player_Attack(void);


