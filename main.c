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
#include "./headers/Led.h"
#include <stdint.h>

unsigned char c;
int result;

void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);
unsigned long SW1, SW2;
// do not edit this main
// your job is to implement the UART_OutUDec UART_OutDistance functions 
int main(void){
  TExaS_Init(); 
	UART_Init();
	Nokia5110_Init();
	Nokia5110_Clear();
	Nokia5110_ClearBuffer();
  // TExaS_Init initializes the real board grader for lab 4
  PortF_Init();
	PortB_Init();
	ADC_Init();
	start:
	UART_OutString("Current Difficulty Level = ");
	UART_OutChar(intToChar(ADC_GetDiff()));
	UART_OutString("\n\r");
	Timer2_delay(160000000);
  EnableInterrupts();  // The grader uses interrupts
  while(attempt < 10){
		WaitForInterrupt();
  }
	Timer2_stop();
	Clear_AllLeds();
	Nokia5110_Clear();
	Nokia5110_ClearBuffer();
	Nokia5110_OutString("Score: ");
	Nokia5110_OutUDec(score);
	UART_OutString("Game Over, You Scored: ");
	UART_OutChar(intToChar(score));
	UART_OutString("\n\r");
	UART_OutString("If you want to play again press SW3!\n\r");
	while(GPIO_PORTB_DATA_R & (1 << 0));
	score = 0;
	attempt = 0;
	goto start;
}
