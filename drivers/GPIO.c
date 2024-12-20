#include "..\\./headers/GPIO.h"
#include "..\\./headers/tm4c123gh6pm.h"
#include "..\\./headers/TExaS.h"
#include "..\\./headers/timer.h"

volatile unsigned long delay;

void PortE_Init(void)
{
  SYSCTL_RCGC2_R |= (1 << 4);   	// 1) E clock
  delay = SYSCTL_RCGC2_R;         // delay
  GPIO_PORTE_LOCK_R = 0x4C4F434B; // 2) unlock PortE PE0
  GPIO_PORTE_CR_R = 0x3F;         // allow changes to PE5-0
  GPIO_PORTE_AMSEL_R = 0;      		// 3) disable analog function
  GPIO_PORTE_PCTL_R = 0; 					// 4) GPIO clear bit PCTL
  GPIO_PORTE_DIR_R = 0x07;        // 5) PE2,PE1,PE0 input, PE3,PE4,PE5 output
  GPIO_PORTE_AFSEL_R = 0;      		// 6) no alternate function
  GPIO_PORTE_PUR_R = (1 << 0) | (1 << 1) | (1 << 2);        // enable pullup resistors on PE2-PE0
  GPIO_PORTE_DEN_R = 0x3F;        // 7) enable digital pins PE5-PE0
  GPIO_PORTE_IS_R &= ~(1 << 0) | ~(1 << 1) | ~(1 << 2);       // 8) PE2-PE0 are edge-sensitive
  GPIO_PORTE_IBE_R &= ~(1 << 0) | ~(1 << 1) | ~(1 << 2);      // PE2-PE0 are not both edges
  GPIO_PORTE_IEV_R &= ~(1 << 0) | ~(1 << 1) | ~(1 << 2);      // PE2, PE0 are falling edge event
  GPIO_PORTE_ICR_R = 0x7;         // (e) Clear flag2-flag0
  GPIO_PORTE_IM_R |= 0x7;         // (f) Arm interrupt on PE2-PE0
  NVIC_PRI7_R = (NVIC_PRI7_R & 0xff00ffff) | 0x00A00000;
  NVIC_EN0_R = (1 << 4);
  EnableInterrupts();
}

//----------------------------------------------------------------------
