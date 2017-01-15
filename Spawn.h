/* Spawn_Init
-Initializes Timer2A
-Sets occurance every .1 seconds
-No inputs or outpus */
void Timer2A_Init(void);
/* Timer1A_Handler
-ISR for Timer2A
-Spawns enemies through time triggers */
void Timer2A_Handler(void);

