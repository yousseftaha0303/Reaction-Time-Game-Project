#include "../headers/timer.h"
#include "../headers/tm4c123gh6pm.h"
#include "../headers/GlobalConfig.h"
#include "../headers/Led.h"
#include "../headers/Nokia5110.h"

unsigned long TimerCountt;
unsigned long Semaphore;
short int OpenLed;

void Timer2_delay(unsigned long period){ 
  SYSCTL_RCGCTIMER_R |= (1 << 3);   	// 0) activate timer2
  TimerCountt = 0;
  Semaphore = 0;
  TIMER2_CTL_R &= ~(1 << 0);    			// 1) disable timer2A during setup
  TIMER2_CFG_R  = 0;    							// 2) configure for 32-bit mode
  TIMER2_TAMR_R = (1 << 1);   				// 3) configure for periodic mode, default down-count settings
  TIMER2_TAILR_R = period - 1;    		// 4) reload value
	
	
	TIMER2_ICR_R = (1 << 0);    				// 6) clear timer2A timeout flag
	TIMER2_IMR_R = (1 << 0);
	NVIC_EN0_R = (1 << 23);							// 9) enable IRQ 23 in NVIC
  TIMER2_CTL_R |= (1 << 0);    				// 10) enable timer2A
}

void Timer2_stop(){
	TIMER2_CTL_R &= ~(1 << 0);
}

/*
* TODO: UART writing to the computer scree
*/
void Timer2A_Handler(void)
{
	if(TIMER2_RIS_R & (1 << 4)){
		TIMER2_ICR_R 	|= (1 << 4);				// acknowledge the interrupt
		Clear_Buzzer();
		Nokia5110_Clear();
		Nokia5110_ClearBuffer();
		if(TIMER2_TAILR_R == (HoldDelay * CyclesPerSec)){
			OpenLed = Randomiz_Leds();
			switch(OpenLed){
				case 1:
					Nokia5110_OutString("Red");
					break;
				case 2:
					Nokia5110_OutString("Green");
					break;
				case 3:
					Nokia5110_OutString("Blue");
					break;
			}
			Timer2_delay(GameDiffTimes[GameDiff] * CyclesPerSec);
		}
		else{
			Clear_AllLeds();
			Nokia5110_OutString("Be Ready!");
			Timer2_delay(HoldDelay * CyclesPerSec);
		}
	}
}