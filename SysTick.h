//SysTick.c

/* SysTick_Init
-Initializes SysTick periodic interrupts
-Called once
-Sets rate to 30Hz */
void SysTick_Init(void);

/* SysTick_Handler
-Interrupt Service Routine
-Determines which action the player has chosen
-Activates animation and sound for corresponding actions */
void SysTick_Handler(void);

