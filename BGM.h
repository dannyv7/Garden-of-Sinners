/* BGM_Init
-Initializes Timer1A
-Sampling rate of song is at 11025 hz */


void BGM_Init(void);

/* Timer1A_Handler
-ISR for Timer1A
-Plays the song by calling DAC_Out */
void Timer1A_Handler(void);
