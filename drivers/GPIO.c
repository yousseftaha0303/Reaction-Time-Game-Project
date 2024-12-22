#include "..\\./headers/GPIO.h"
#include "..\\./headers/tm4c123gh6pm.h"
#include "..\\./headers/TExaS.h"
#include "..\\./headers/timer.h"
#include "..\\./headers/Led.h"
#include "..\\./headers/GlobalConfig.h"
#include "../headers/Nokia5110.h"
#include "../headers/UART.h"

volatile unsigned long delay;
unsigned long FSW1, FSW2;

void PortB_Init(void)
{
  SYSCTL_RCGC2_R |= (1 << 1);   	// 1) B clock
  delay = SYSCTL_RCGC2_R;         // delay
  GPIO_PORTB_LOCK_R = 0x4C4F434B; // 2) unlock PortB PB0
  GPIO_PORTB_CR_R = 0x7F;         // allow changes to PB6-0
  GPIO_PORTB_AMSEL_R = 0;      		// 3) disable analog function
  GPIO_PORTB_PCTL_R = 0; 					// 4) GPIO clear bit PCTL
  GPIO_PORTB_DIR_R = 0x78;        // 5) PB2,PB1,PB0 input, PB3,PB4,PB5,PB6 output
  GPIO_PORTB_AFSEL_R = 0;      		// 6) no alternate function
  GPIO_PORTB_PUR_R = (1 << 0) | (1 << 1) | (1 << 2);        // enable pullup resistors on PB2-PB0
  GPIO_PORTB_DEN_R = 0x7F;        // 7) enable digital pins PB6-PB0
}

//----------------------------------------------------------------------
// 0 red , 1 green , 2 blue


/*void GPIOPortB_Handler(void){
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
}*/


void PortF_Init(void){  unsigned long volatile delay;
  SYSCTL_RCGC2_R |= 0x00000020; // (a) activate clock for port F
  delay = SYSCTL_RCGC2_R;
  GPIO_PORTF_LOCK_R = 0x4C4F434B; // unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x11;           // allow changes to PF4-0  0001 0001
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 input, PF3,PF2,PF1 output      
  GPIO_PORTF_AFSEL_R &= ~0x11;  //     disable alt funct 
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital pins PF4-PF0          
  GPIO_PORTF_PCTL_R &= ~0x000F000F; //  configure PF4 as GPIO
  GPIO_PORTF_AMSEL_R &= ~0x11;  //     disable analog functionality 
  GPIO_PORTF_PUR_R |= 0x11;     //     enable weak pull-up on PF4
  GPIO_PORTF_IS_R &= ~0x11;     // (d) PF4,PF0 is edge-sensitive
  GPIO_PORTF_IBE_R &= ~0x11;    //     PF4,PF0 is not both edges
  GPIO_PORTF_IEV_R &= ~0x11;    //     PF4,PF0 falling edge event
  GPIO_PORTF_ICR_R = 0x11;      // (e) clear flags 4
  GPIO_PORTF_IM_R |= 0x11;      // (f) arm interrupt on PF4,PF0
  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00400000; // (g) priority 2
  NVIC_EN0_R = 0x40000000;      // (h) enable interrupt 30 in NVIC
	EnableInterrupts();
}

void GPIOPortF_Handler(void){ // called on touch of either SW1 or SW2
  if(GPIO_PORTB_DATA_R & (1 << 3) && GPIO_PORTF_RIS_R & (1 << 0)){
		GPIO_PORTF_ICR_R |= (1 << 0);
		Clear_AllLeds();
		score++;
		Nokia5110_Clear();
		Nokia5110_ClearBuffer();
		Nokia5110_OutString("Scored");
		Set_Buzzer();
	}
	if(GPIO_PORTB_DATA_R & (1 << 4) && GPIO_PORTF_RIS_R & (1 << 4)){
		GPIO_PORTF_ICR_R |= (1 << 4);
		Clear_AllLeds();
		score++;
		Nokia5110_Clear();
		Nokia5110_ClearBuffer();
		Nokia5110_OutString("Scored");
		Set_Buzzer();
	}
}





















