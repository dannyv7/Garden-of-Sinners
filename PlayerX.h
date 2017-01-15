//PlayerX.h

/*PlayerX_Init
-Initializes TIMER0A
-Set Priority to 4
*/
void PlayerX_Init(void);

/*Timer0A_Handler
-Reads the ADC
-Converts the ADC into an X position
-Returns X position to main
*/
void Timer0A_Handler(void);

