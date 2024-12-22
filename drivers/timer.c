#include "../headers/timer.h"
#include "../headers/tm4c123gh6pm.h"
#include "../headers/GlobalConfig.h"
#include "../headers/Led.h"
#include "../headers/Nokia5110.h"
#include "../headers/UART.h"

unsigned long TimerCount;
unsigned long Semaphore;
short int OpenLed;

void Timer2_delay(unsigned long period){
  unsigned long volatile delay;
  SYSCTL_RCGCTIMER_R |= 0x04;   // 0) activate timer2
  delay = SYSCTL_RCGCTIMER_R;
  TimerCount = 0;
  TIMER2_CTL_R = 0x00000000;   // 1) disable timer2A
  TIMER2_CFG_R = 0x00000000;   // 2) 32-bit mode
  TIMER2_TAMR_R = 0x00000002;  // 3) periodic mode
  TIMER2_TAILR_R = period-1;   // 4) reload value
  TIMER2_TAPR_R = 0;           // 5) clock resolution
  TIMER2_ICR_R = 0x00000001;   // 6) clear timeout flag
  TIMER2_IMR_R = 0x00000001;   // 7) arm timeout
  NVIC_PRI5_R = (NVIC_PRI5_R & ~0x00E00000) | (1 << 21); // Set priority 1 for Timer2A
  NVIC_EN0_R = 1<<23;          // 9) enable IRQ 23 in
  TIMER2_CTL_R = 0x00000001;   // 10) enable timer2A
}

void Timer2_stop(){
	TIMER2_CTL_R &= ~(1 << 0);
}

void Timer2A_Handler(void)
{
	if(TIMER2_RIS_R & (1 << 0)){
		TIMER2_ICR_R 	|= (1 << 0);				// acknowledge the interrupt
		Clear_Buzzer();
		Nokia5110_Clear();
		Nokia5110_ClearBuffer();
		if(TIMER2_TAILR_R == (HoldDelay * CyclesPerSec)){
			Nokia5110_OutString("Attempt(s) Left: ");
			Nokia5110_OutUDec(10 - attempt);
			Nokia5110_OutString("\n\r");
			OpenLed = RandomizeLeds();
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