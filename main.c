// main.c
// Runs on LM4F120/TM4C123
// Test main for Lab 11
// January 15, 2016

// this connection occurs in the USB debugging cable
// U0Rx (PA0) connected to serial port on PC
// U0Tx (PA1) connected to serial port on PC
// Ground connected ground in the USB cable

#include "./headers/tm4c123gh6pm.h"
#include "./headers/UART.h"
#include "./headers/TExaS.h"
#include "./headers/Nokia5110.h"
#include "./headers/ADC.h"
#include "./headers/GlobalConfig.h"
#include "./headers/timer.h"
#include "./headers/GPIO.h"

unsigned long SW1;
unsigned char c;

void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);
// do not edit this main
// your job is to implement the UART_OutUDec UART_OutDistance functions 
int main(void){ unsigned long n;
  TExaS_Init();             // initialize grader, set system clock to 80 MHz
  UART_Init();              // initialize UART
	Nokia5110_Init();
	Nokia5110_Clear();
	Nokia5110_ClearBuffer();
	PortF_Init();
	PortB_Init();
	Timer2_delay(160000000);
  EnableInterrupts();       // needed for TExaS
	while(attempt < 10){
		WaitForInterrupt();
	}
	Nokia5110_Clear();
	Nokia5110_ClearBuffer();
	Nokia5110_OutString("Score: ");
	Nokia5110_OutUDec(score);
}
