# Garden-of-Sinners
Bullet hell styled video game written for TI TM4C123 Launchpad in conjunction with Adafruit ST7735 LCD, 8-bit DAC, and joystick. One of my 
largest projects to date, this was created as an entry to the FA2015 University of Texas Introduction to Embedded Systems Video Game Design competition 
and took first place through peer nomination against ~ 36 others.  

General Gameplay Description:  
- Player controls a character that starts with 100 health points and attempts to shoot down enemies that spawn at certain intervals
- Player character can use a basic straight line gun attack, a wide blast shotgun, or a screen clearing bomb attack. 
- Killing enemies will increase the player's score
- Failing to move out the way of enemy attacks will incur a health point penalty depending on the strength of the enemy
- Player character will die when their health points drop to 0 or less; player may then respawn but lose half of their current score
- After a certain amount of time a boss fight will trigger - defeating the boss ends the mini game
  
Implementation of Game Mechanics:  
- System clock ran at 80MHz  
- Three tiers of enemies existed as well as a boss enemy, each spawning at different intervals controlled by Timer2A  
- No memory heap was used therefore only a set amount of enemies could exist at a time. Different enemy types were represented as different structs  
- Timer2A also controlled the rate at which enemies attacked and moved
- Enemy attacks were treated as structs as well, and moved accordingly to Timer2A
- All enemies and enemy attacks had hitboxes that determined whether the player's attacks hit them and whether they hit the player character or not using pixel math based on the (x, y) positions of the various game objects  
- All characters and their various attacks were represented with sprites which were output to the attached LCD at their appropriate pixel 
positions on the screen 

  
Graphics:  
- Output device used was the Adafruit ST7735R LCD
- Featured a software double buffering system to output entire frames at once to the LCD rather than individual objects at a time, ensuring a highly fluid display with the maximum frames per seconds allowed by the LCD  
- Double buffering was implemented by the usage of an array in RAM where bitmap values were written to for each game frame, then the entire array was written to the LCD (the default ST7735R.c driver was modified to 
accomadate this feature)  
- Due to double buffering, a smooth, rolling background was possible  
- Video game sprites were created by artists as .png files, then converted to .bmp files via Paint which were then converted into
their corressponding unsigned short arrays and placed into the Launchpad's ROM  
  
	
Controls:  
- Player character movement is dictated by the usage of a joystick which is treated as a two channel analog to digital converter in the software (assigned to PortE4 and PortE5 of the Launchpad)  
- The joystick adc sampling was done at 125K samples/second and was handled by the Timer0A interrupt service routine 
- The joystick used for my first deployment of the code was a SainSmart UNO 2560 R3 STM32 A072 (can be found here: https://www.amazon.com/gp/product/B00CO2N18A/ref=oh_aui_search_detailpage?ie=UTF8&psc=1)
- 3x basic switches/buttons - assigned to each of the player attacks (mapped to PortD0 - PortD2) and read via SysTick_Timer's ISR
  
Sound:  
- Loops a six second sample of Silent Ensemble from Touhou composed by ZUN
- Music was edited and trimmed to a 6s .wav file then ran through a MatLab conversion program to generate its corresponding values in a char array
- The background music was outputted to an 8-bit binary weighted DAC using multiple resistors in parallel and series at the correct tempo controlled by Timer1A's interrupt service routine  
  
Additional Credit:  
- ZUN - composer of BGM  
- Jennifer Icaro - artist for player related sprites and the background
- RPG Maker VX Ace - sprites for enemy related sprites
- Christopher Friesen - provided input on modification of ST7735R driver
- Shamma Kabir - assisted with hitpoint programming and minor graphic detail
- Jonathan Valvano & Ramesh Yerraballi - provided bmp and wav conversion code, facilitated the creation of the project in a contest environment, 
and most importantly taught the knowledge needed to create this project    
