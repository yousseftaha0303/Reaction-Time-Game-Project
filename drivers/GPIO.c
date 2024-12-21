#include "..\\./headers/GPIO.h"
#include "..\\./headers/tm4c123gh6pm.h"
#include "..\\./headers/TExaS.h"
#include "..\\./headers/timer.h"
#include "..\\./headers/Led.h"
#include "..\\./headers/GlobalConfig.h"
#include "../headers/Nokia5110.h"

volatile unsigned long delay;

void PortB_Init(void)
{
  SYSCTL_RCGC2_R |= (1 << 1);   	// 1) B clock
  delay = SYSCTL_RCGC2_R;         // delay
  GPIO_PORTB_LOCK_R = 0x4C4F434B; // 2) unlock PortB PB0
  GPIO_PORTB_CR_R = 0x7F;         // allow changes to PB6-0
  GPIO_PORTB_AMSEL_R = 0;      		// 3) disable analog function
  GPIO_PORTB_PCTL_R = 0; 					// 4) GPIO clear bit PCTL
  GPIO_PORTB_DIR_R = 0x07;        // 5) PB2,PB1,PB0 input, PB3,PB4,PB5,PB6 output
  GPIO_PORTB_AFSEL_R = 0;      		// 6) no alternate function
  GPIO_PORTB_PUR_R = (1 << 0) | (1 << 1) | (1 << 2);        // enable pullup resistors on PB2-PB0
  GPIO_PORTB_DEN_R = 0x7F;        // 7) enable digital pins PB6-PB0
  GPIO_PORTB_IS_R &= ~(1 << 0) | ~(1 << 1) | ~(1 << 2);       // 8) PB2-PB0 are edge-sensitive
  GPIO_PORTB_IBE_R &= ~(1 << 0) | ~(1 << 1) | ~(1 << 2);      // PB2-PB0 are not both edges
  GPIO_PORTB_IEV_R &= ~(1 << 0) | ~(1 << 1) | ~(1 << 2);      // PB2, PB0 are falling edge event
  GPIO_PORTB_ICR_R = 0x7;         // (e) Clear flag2-flag0
  GPIO_PORTB_IM_R |= 0x7;         // (f) Arm interrupt on PB2-PB0
  NVIC_PRI7_R = (NVIC_PRI7_R & 0xff00ffff) | 0x00A00000;
  NVIC_EN0_R = (1 << 1);
  EnableInterrupts();
}

//----------------------------------------------------------------------
// 0 red , 1 green , 2 blue

void GPIOB_Handler(void){
	GPIO_PORTB_ICR_R = (1 << 0) | (1 << 1) | (1 << 2);
	if(GPIO_PORTB_RIS_R & (1<<0) && GPIO_PORTB_DATA_R & (1<<3)){
		attempt++;
		score++;
		Clear_RedLed();
		Nokia5110_Clear();
		Nokia5110_OutString("Pressed Red LED");
	}
	else if(GPIO_PORTB_RIS_R & (1<<1) && GPIO_PORTB_DATA_R & (1<<4)){
		attempt++;
		score++;
		Clear_GreenLed();
		Nokia5110_Clear();
		Nokia5110_OutString("Pressed Green LED");
	}
	else if(GPIO_PORTB_RIS_R & (1<<2) && GPIO_PORTB_DATA_R & (1<<5)){
		attempt++;
		score++;
		Clear_BlueLed();
		Nokia5110_Clear();
		Nokia5110_OutString("Pressed Blue LED");
	}
	else if(GPIO_PORTB_RIS_R & (1<<0) && GPIO_PORTB_RIS_R & (1<<1) && GPIO_PORTB_RIS_R & (1<<2) && ChkAllLeds()){
		Nokia5110_Clear();
		Nokia5110_OutString("Wait for the Leds");
	}
	else{
		attempt++;
		Clear_AllLeds();
		Set_Buzzer();
		Nokia5110_Clear();
		Nokia5110_OutString("Wrong Led Pressed!");
	}
}


void PortF_Init(void){ volatile unsigned long delay;
	// Choose Port F ( sixth bit : bit-5 )
	SYSCTL_RCGC2_R |= (1<<5);     		// 1) F clock
  delay = SYSCTL_RCGC2_R;           // delay   
  // Put Magic Number into GPIOLOCK to unlock and enable write access to GPIOCR 
	GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
	// Allow access to this pins as they unlocked
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0  
	// Analog not used
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog function
	// Set all pins as GPIO
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
	// Decide which input (0) and output (1)
	// PF4 and PF0 are input SW1 and SW2 respectively
	// PF3,PF2,PF1 are outputs to the LED
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 input, PF3,PF2,PF1 output 
	// GPIO workcase  
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) no alternate function
	// Enable Pull up
  GPIO_PORTF_PUR_R = 0x11;          // enable pullup resistors on PF4,PF0   
	// Enable Digital Pins
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital pins PF4-PF0
	GPIO_PORTF_DATA_R &= ~0xE;	
}





















