#include "..\\./headers/GPIO.h"
#include "..\\./headers/tm4c123gh6pm.h"
#include "..\\./headers/TExaS.h"
#include "..\\./headers/timer.h"
#include "..\\./headers/Led.h"
#include "..\\./headers/GlobalConfig.h"

volatile unsigned long delay;

void PortB_Init(void)
{
  SYSCTL_RCGC2_R |= (1 << 1);   	// 1) B clock
  delay = SYSCTL_RCGC2_R;         // delay
  GPIO_PORTE_LOCK_R = 0x4C4F434B; // 2) unlock PortB PB0
  GPIO_PORTE_CR_R = 0x7F;         // allow changes to PB6-0
  GPIO_PORTE_AMSEL_R = 0;      		// 3) disable analog function
  GPIO_PORTE_PCTL_R = 0; 					// 4) GPIO clear bit PCTL
  GPIO_PORTE_DIR_R = 0x07;        // 5) PB2,PB1,PB0 input, PB3,PB4,PB5,PB6 output
  GPIO_PORTE_AFSEL_R = 0;      		// 6) no alternate function
  GPIO_PORTE_PUR_R = (1 << 0) | (1 << 1) | (1 << 2);        // enable pullup resistors on PB2-PB0
  GPIO_PORTE_DEN_R = 0x7F;        // 7) enable digital pins PB6-PB0
  GPIO_PORTE_IS_R &= ~(1 << 0) | ~(1 << 1) | ~(1 << 2);       // 8) PB2-PB0 are edge-sensitive
  GPIO_PORTE_IBE_R &= ~(1 << 0) | ~(1 << 1) | ~(1 << 2);      // PB2-PB0 are not both edges
  GPIO_PORTE_IEV_R &= ~(1 << 0) | ~(1 << 1) | ~(1 << 2);      // PB2, PB0 are falling edge event
  GPIO_PORTE_ICR_R = 0x7;         // (e) Clear flag2-flag0
  GPIO_PORTE_IM_R |= 0x7;         // (f) Arm interrupt on PB2-PB0
  NVIC_PRI7_R = (NVIC_PRI7_R & 0xff00ffff) | 0x00A00000;
  NVIC_EN0_R = (1 << 1);
  EnableInterrupts();
}

//----------------------------------------------------------------------
// 0 red , 1 green , 2 blue

/*
*	TODO: Write to the Nokia5110 (Pressed [Color])
*/
void GPIOB_Handler(void){
	GPIO_PORTB_ICR_R = (1 << 0) | (1 << 1) | (1 << 2);
	if(GPIO_PORTB_RIS_R & (1<<0) && GPIO_PORTB_DATA_R & (1<<3)){
		score++;
		Clear_RedLed();
	}
	else if(GPIO_PORTB_RIS_R & (1<<1) && GPIO_PORTB_DATA_R & (1<<4)){
		score++;
		Clear_GreenLed();
	}
	else if(GPIO_PORTB_RIS_R & (1<<2) && GPIO_PORTB_DATA_R & (1<<5)){
		score++;
		Clear_BlueLed();
	}
	else{
		Clear_AllLeds();
		Set_Buzzer();
	}
}
























