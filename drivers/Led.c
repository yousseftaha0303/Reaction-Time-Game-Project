#include "../headers/Led.h"
#include "../headers/tm4c123gh6pm.h"
#include "../headers/UART.h"

static int ledSeed = 123456789;
int currentOpenLed = 0;

void Set_RedLed(void)
{
	GPIO_PORTB_DATA_R = (1 << 3);
}

void Set_GreenLed(void)
{
	GPIO_PORTB_DATA_R = (1 << 4);
}

void Set_BlueLed(void)
{
	GPIO_PORTB_DATA_R = (1 << 5);
}

void Set_AllLeds(void)
{
	GPIO_PORTB_DATA_R = (7 << 3);
}

void Set_Buzzer(void)
{
	GPIO_PORTB_DATA_R |= (1 << 6);
}

void Clear_RedLed(void)
{
	GPIO_PORTB_DATA_R &= ~(1 << 3);
}

void Clear_GreenLed(void)
{
	GPIO_PORTB_DATA_R &= ~(1 << 4);
}

void Clear_BlueLed(void)
{
	GPIO_PORTB_DATA_R &= ~(1 << 5);
}

void Clear_AllLeds(void)
{
	GPIO_PORTB_DATA_R &= !(7 << 3);
}

void Clear_Buzzer(void)
{
	GPIO_PORTB_DATA_R &= ~(1 << 6);
}


// TODO: Fix the random number generator
int RandomizeLeds(){
	// generate a random number between 1 and 3
	ledSeed ^= (ledSeed << 21);
	ledSeed ^= (ledSeed >> 30);
	ledSeed ^= (ledSeed << 4);
	currentOpenLed = (ledSeed % 2) + 1;
	if(currentOpenLed != 1 && currentOpenLed != 2 &&  currentOpenLed != 3)
		currentOpenLed = 2;
	// open the required LED
	Clear_AllLeds();
	switch(currentOpenLed){
		case 1:
			Set_RedLed();
			break;
		case 2:
			Set_GreenLed();
			break;
	}
	return currentOpenLed;
}


int ChkAllLeds(void){
	if(!(GPIO_PORTB_DATA_R & (1<<5)) && !(GPIO_PORTB_DATA_R & (1<<4)) && !(GPIO_PORTB_DATA_R & (1<<3)))
		return 1;
	return 0;
}